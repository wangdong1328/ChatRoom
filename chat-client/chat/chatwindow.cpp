#include "chatwindow.h"

#include "messageitemwidget.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QPainter>

ChatTitle::ChatTitle(const QString& strUserName, const QPixmap& pixUserHead, QWidget* parent)
{
    QHBoxLayout* pMainHBoxLayout = new QHBoxLayout(this);
    this->setLayout(pMainHBoxLayout);

    this->m_pUserHead = new QLabel(this);
    this->m_pUserHead->setFixedSize(40, 40);
    this->m_pUserHead->setScaledContents(true);
    this->m_pUserHead->setPixmap(pixUserHead.scaled(QSize(this->m_pUserHead->size()), Qt::IgnoreAspectRatio,
                                                    Qt::SmoothTransformation));

    this->m_pUserName = new QLabel(strUserName, this);
    this->m_pUserName->adjustSize();
    this->m_pUserName->setStyleSheet("QLabel { color : black; }");

    pMainHBoxLayout->addWidget(this->m_pUserHead);
    pMainHBoxLayout->addSpacing(10);
    pMainHBoxLayout->addWidget(this->m_pUserName);
    pMainHBoxLayout->addStretch();
}

ChatTitle::~ChatTitle() {}

void ChatTitle::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(QColor(0, 0, 0, 20));
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(QPoint(this->rect().bottomLeft()), QPoint(this->rect().bottomRight()));
    painter.restore();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::transparent);
    painter.drawRoundedRect(this->rect(), 10, 10);
    painter.restore();

    QWidget::paintEvent(event);
}

ChatMessageEdit::ChatMessageEdit(QWidget* parent)
{
    this->setFixedHeight(130);

    QVBoxLayout* pMainVBoxLayout = new QVBoxLayout(this);
    pMainVBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(pMainVBoxLayout);

    QFont font;
    font.setPixelSize(13);
    this->m_pMessageEdit = new QTextEdit(this);
    this->m_pMessageEdit->setFont(font);
    this->m_pMessageEdit->setFrameShape(QFrame::NoFrame);
    this->m_pMessageEdit->setPlaceholderText("Enter Something...");
    this->m_pMessageEdit->installEventFilter(this);

    QPalette palette = this->m_pMessageEdit->palette();
    palette.setColor(QPalette::Text, QColor(Qt::black));
    this->m_pMessageEdit->setPalette(palette);

    QHBoxLayout* pToolHBoxLayout = new QHBoxLayout;

    // 文件
    this->m_pFileButton = new QLabel(this);
    this->m_pFileButton->setFixedSize(23, 23);
    this->m_pFileButton->setScaledContents(true);

    QPixmap pixmap(":/res/ico/file_unsel.png");
    this->m_pFileButton->setPixmap(pixmap);
    this->m_pFileButton->setCursor(Qt::PointingHandCursor);
    this->m_pFileButton->setAttribute(Qt::WA_Hover);
    this->m_pFileButton->installEventFilter(this);

    // 表情
    this->m_pEmojiButton = new QLabel(this);
    this->m_pEmojiButton->setFixedSize(25, 25);
    this->m_pEmojiButton->setScaledContents(true);

    pixmap.load(":/res/ico/emoji_unsel.png");
    this->m_pEmojiButton->setPixmap(pixmap);
    this->m_pEmojiButton->setCursor(Qt::PointingHandCursor);
    this->m_pEmojiButton->setAttribute(Qt::WA_Hover);
    this->m_pEmojiButton->installEventFilter(this);

    // 清空
    this->m_pClearButton = new QLabel(this);
    this->m_pClearButton->setFixedSize(20, 20);
    this->m_pClearButton->setScaledContents(true);

    pixmap.load(":/res/ico/clear_unselect.png");
    this->m_pClearButton->setPixmap(pixmap);
    this->m_pClearButton->setCursor(Qt::PointingHandCursor);
    this->m_pClearButton->setAttribute(Qt::WA_Hover);
    this->m_pClearButton->installEventFilter(this);

    pToolHBoxLayout->setSpacing(15);
    pToolHBoxLayout->addWidget(this->m_pFileButton);
    pToolHBoxLayout->addWidget(this->m_pEmojiButton);
    pToolHBoxLayout->addWidget(this->m_pClearButton);
    pToolHBoxLayout->addStretch();

    QHBoxLayout* m_pSendHBoxLayout = new QHBoxLayout;
    this->m_pSendButton = new SendMessageButton(this);
    this->m_pSendButton->installEventFilter(this);

    m_pSendHBoxLayout->addStretch();
    m_pSendHBoxLayout->addWidget(this->m_pSendButton);

    pMainVBoxLayout->addSpacing(5);
    pMainVBoxLayout->addLayout(pToolHBoxLayout);
    pMainVBoxLayout->addWidget(this->m_pMessageEdit);
    pMainVBoxLayout->addLayout(m_pSendHBoxLayout);
}

void ChatMessageEdit::SendMessage()
{
    QString strMessage = this->m_pMessageEdit->toPlainText();
    if (!strMessage.isEmpty())
    {
        // 发送消息
        this->m_pMessageEdit->clear();

        // 构建消息结构
        SMessageInfo stMessageInfo;
        stMessageInfo.eType = EMessageType::TEXT;
        stMessageInfo.strContent = strMessage;
        emit SendMessageSignal(stMessageInfo);
    }
}

void ChatMessageEdit::SendFileMessage(const QString& strFilePath)
{
    if (!strFilePath.isEmpty())
    {
        QFileInfo fileInfo(strFilePath);

        // 构建 JSON 对象
        QJsonObject jsonObj;

        jsonObj.insert("name", fileInfo.fileName());
        jsonObj.insert("type", static_cast<unsigned short>(EFileType::NORMAL_FILE));
        jsonObj.insert("size", fileInfo.size());
        jsonObj.insert("content", strFilePath);

        // 构建 JSON 文档
        QJsonDocument document;
        document.setObject(jsonObj);
        QByteArray baContent = document.toJson(QJsonDocument::Compact);

        // 构建消息结构
        SMessageInfo stMessageInfo;
        stMessageInfo.eType = EMessageType::FILE;
        stMessageInfo.strContent = baContent;
        emit SendMessageSignal(stMessageInfo);
    }
}

bool ChatMessageEdit::eventFilter(QObject* watched, QEvent* event)
{
    // 文本框
    if ((watched == this->m_pMessageEdit) && (QEvent::KeyPress == event->type()))
    {
        QKeyEvent* pKey = reinterpret_cast<QKeyEvent*>(event);
        if (pKey->key() == Qt::Key_Return)
        {
            SendMessage();
            return true;
        }
    }
    // 发送按钮
    else if ((watched == this->m_pSendButton) && (QEvent::MouseButtonPress == event->type()))
    {
        SendMessage();
        return true;
    }
    else if (watched == this->m_pEmojiButton)   // 表情
    {
        if (QEvent::HoverEnter == event->type())
        {
            QPixmap pixmap;
            pixmap.load(":/res/ico/emoji_sel.png");
            this->m_pEmojiButton->setPixmap(pixmap);
            return true;
        }

        if (QEvent::HoverLeave == event->type())
        {
            QPixmap pixmap;
            pixmap.load(":/res/ico/emoji_unsel.png");
            this->m_pEmojiButton->setPixmap(pixmap);
            return true;
        }
    }
    else if (watched == this->m_pFileButton)   // 发送文件
    {
        if (QEvent::HoverEnter == event->type())
        {
            QPixmap pixmap;
            pixmap.load(":/res/ico/file_sel.png");
            this->m_pFileButton->setPixmap(pixmap);
            return true;
        }
        else if (QEvent::HoverLeave == event->type())
        {
            QPixmap pixmap;
            pixmap.load(":/res/ico/file_unsel.png");
            this->m_pFileButton->setPixmap(pixmap);
            return true;
        }
        else if (QEvent::MouseButtonPress == event->type())
        {
            QString strFilePath = QFileDialog::getOpenFileName(this, "选择文件", "/");
            if (!strFilePath.isEmpty())
            {
                SendFileMessage(strFilePath);
            }
            return true;
        }
    }
    else if (watched == this->m_pClearButton)   // 清理
    {
        if (QEvent::HoverEnter == event->type())
        {
            QPixmap pixmap;
            pixmap.load(":/res/ico/clear_select.png");
            this->m_pClearButton->setPixmap(pixmap);
            return true;
        }
        else if (QEvent::HoverLeave == event->type())
        {
            QPixmap pixmap;
            pixmap.load(":/res/ico/clear_unselect.png");
            this->m_pClearButton->setPixmap(pixmap);
            return true;
        }
        else if (QEvent::MouseButtonPress == event->type())
        {
            emit SendClearChatHistorySignal();
        }
    }

    return QWidget::eventFilter(watched, event);
}

void ChatMessageEdit::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QColor(0, 0, 0, 50));
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(QPoint(this->rect().topLeft()), QPoint(this->rect().topRight()));
    QWidget::paintEvent(event);
}

SendMessageButton::SendMessageButton(QWidget* parent)
{
    this->setFixedSize(60, 30);
    this->setCursor(Qt::PointingHandCursor);
}

void SendMessageButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(106, 76, 255));
    painter.drawRoundedRect(this->rect(), 10, 10);
    painter.restore();

    QFont font;
    font.setBold(true);
    painter.save();
    painter.setPen(Qt::white);
    painter.setFont(font);
    painter.setBrush(Qt::NoBrush);
    painter.drawText(this->rect(), Qt::AlignCenter, QString("发送"));
    painter.restore();
}

ChatWindow::ChatWindow(SUserData& stUserData, QWidget* parent) : QWidget { parent }, m_stUserData(stUserData)
{
    QHBoxLayout* pMainLayout = new QHBoxLayout(this);
    pMainLayout->setContentsMargins(9, 0, 9, 9);
    this->setLayout(pMainLayout);

    QVBoxLayout* pContentVBoxLayout = new QVBoxLayout();

    // 标题
    this->m_pChatTitle = new ChatTitle(m_stUserData.strUserName, m_stUserData.pixUserHead, this);

    // 聊天内容
    this->m_pChatList = new QListWidget(this);
    this->m_pChatList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->m_pChatList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QStringList qss;
    qss.append("QListWidget::item:hover{background:transparent}");
    qss.append("QListWidget{background-color:transparent}");
    this->m_pChatList->setStyleSheet(qss.join(""));
    this->m_pChatList->setSpacing(5);
    this->m_pChatList->setFrameShape(QFrame::NoFrame);

    // 编辑消息窗口
    this->m_pMessageEdit = new ChatMessageEdit(this);

    pContentVBoxLayout->addWidget(this->m_pChatTitle);
    pContentVBoxLayout->addWidget(this->m_pChatList);
    pContentVBoxLayout->addWidget(this->m_pMessageEdit);

    pMainLayout->addLayout(pContentVBoxLayout);

    connect(this->m_pMessageEdit, &ChatMessageEdit::SendMessageSignal, this, [&](SMessageInfo stMessageInfo) {
        m_stUserData.stMessageInfo = stMessageInfo;
        IncreaseMessageItem(m_stUserData);
    });

    connect(this->m_pMessageEdit, &ChatMessageEdit::SendClearChatHistorySignal, this, [&]() {
        this->m_pChatList->clear();
    });
}

void ChatWindow::IncreaseMessageItem(const SUserData& stUserData)
{
    SUserData stTempUserData = stUserData;
    if (m_stUserData.strUserAccount == stUserData.strUserAccount)
    {
        stTempUserData.alignment = Qt::AlignRight;
    }

    QListWidgetItem* item = new QListWidgetItem(this->m_pChatList);
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);

    MessageItemWidget* itemWidget = new MessageItemWidget(stTempUserData, this);
    item->setSizeHint(itemWidget->size());
    item->setData(Qt::UserRole, QVariant::fromValue(stTempUserData));
    this->m_pChatList->addItem(item);
    this->m_pChatList->setItemWidget(item, itemWidget);
    this->m_pChatList->scrollToBottom();
}

void ChatWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(QColor(0, 0, 0, 20));
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(QPoint(this->rect().topLeft()), QPoint(this->rect().bottomLeft()));
    painter.restore();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::transparent);
    painter.drawRoundedRect(this->rect(), 15, 15);
    painter.restore();
}
