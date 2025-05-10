#include "applicationtitlebar.h"

#include <QHBoxLayout>

ApplicationTitleBar::ApplicationTitleBar(QWidget* parent) : QWidget { parent }
{
    QHBoxLayout* pMainLayout = new QHBoxLayout(this);
    pMainLayout->setContentsMargins(16, 0, 9, 0);
    this->setLayout(pMainLayout);

    // 窗口图标设置
    this->m_pIconLabel = new QLabel(this);
    this->m_pIconLabel->setFixedSize(25, 25);
    this->m_pIconLabel->setScaledContents(true);
    QPixmap pixmap(":/res/ico/chat.png");
    pixmap = pixmap.scaled(QSize(this->m_pIconLabel->width(), this->m_pIconLabel->height()),
                           Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->m_pIconLabel->setPixmap(pixmap);

    // 窗口标题
    QFont font;
    font.setPixelSize(16);
    QPalette pale;
    pale.setColor(QPalette::WindowText, Qt::black);
    this->m_pTitleLabel = new QLabel(this);
    this->m_pTitleLabel->setText("聊天客户端");
    this->m_pTitleLabel->setAlignment(Qt::AlignCenter);
    this->m_pTitleLabel->setPalette(pale);
    this->m_pTitleLabel->setFont(font);
    this->m_pTitleLabel->adjustSize();

    // 搜索
    this->m_pSearchLabel = new QLabel(this);
    this->m_pSearchLabel->setCursor(Qt::PointingHandCursor);
    this->m_pSearchLabel->setFixedSize(18, 18);
    this->m_pSearchLabel->setScaledContents(true);
    pixmap.load(":/res/ico/RiSearchLine.png");
    this->m_pSearchLabel->setPixmap(pixmap);
    this->m_pSearchLabel->installEventFilter(this);
    this->m_pSearchLabel->setToolTip(QString("搜索"));

    // 通知
    pixmap.load(":/res/ico/RiNotification3Line.png");
    this->m_pIconWithRedPoint = new IconWithRedPoint(QSize(28, 28), pixmap, this);
    this->m_pIconWithRedPoint->SetUnRead(true);
    this->m_pIconWithRedPoint->setToolTip(QString("通知"));
    this->m_pIconWithRedPoint->installEventFilter(this);

    // 下拉框
    this->m_pPullDownListLabel = new QLabel(this);
    this->m_pPullDownListLabel->setCursor(Qt::PointingHandCursor);
    this->m_pPullDownListLabel->setFixedSize(18, 18);
    this->m_pPullDownListLabel->setScaledContents(true);
    pixmap.load(":/res/ico/IconamoonArrowDown2Bold.png");
    this->m_pPullDownListLabel->setPixmap(pixmap);
    this->m_pPullDownListLabel->setToolTip(QString("其他功能"));
    this->m_pPullDownListLabel->installEventFilter(this);

    // 标题栏
    this->m_pNormalTitleBar = new NormalTitleBar(parent);
    this->m_pNormalTitleBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    pMainLayout->addWidget(m_pIconLabel);
    pMainLayout->addSpacing(10);
    pMainLayout->addWidget(m_pTitleLabel);
    pMainLayout->addStretch();

    pMainLayout->addWidget(m_pIconWithRedPoint);
    pMainLayout->addSpacing(10);
    pMainLayout->addWidget(m_pSearchLabel);
    pMainLayout->addSpacing(10);
    pMainLayout->addWidget(m_pPullDownListLabel);
    pMainLayout->addSpacing(20);
    pMainLayout->addWidget(m_pNormalTitleBar);
}

bool ApplicationTitleBar::eventFilter(QObject* watched, QEvent* event)
{
    if (QEvent::MouseButtonPress == event->type())
    {
        if (this->m_pSearchLabel == watched)
        {
            emit ShowSearchSignal();
            return true;
        }

        if (this->m_pIconWithRedPoint == watched)
        {
            emit ShowSystemNotificationSignal();
            return true;
        }

        if (this->m_pPullDownListLabel == watched)
        {
            emit ShowPullDownListSignal();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}
