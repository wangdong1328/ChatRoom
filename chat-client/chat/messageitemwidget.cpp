#include "messageitemwidget.h"

#include <QDateTime>
#include <QHBoxLayout>
#include <QPainter>
#include <QFontMetrics>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScrollBar>

Bubble::Bubble(const SUserData& stUserData, QWidget* parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    QFont font = this->font();

    this->m_pMessageContent = new QLabel(this);
    this->m_pMessageContent->setFont(font);
    this->m_pMessageContent->setStyleSheet(" QLabel {"
                                           " border: none;"
                                           " background: transparent;"
                                           " outline: none;"
                                           " color: black;"
                                           "}");
    this->m_pMessageContent->adjustSize();

    switch (stUserData.stMessageInfo.eType)
    {
        case EMessageType::TEXT :
            {
                font.setPixelSize(13);

                QHBoxLayout* pMainLayout = new QHBoxLayout(this);
                pMainLayout->setContentsMargins(0, 2, 2, 2);
                this->setLayout(pMainLayout);

                this->m_pMessageContent->setText(stUserData.stMessageInfo.strContent);
                pMainLayout->addWidget(this->m_pMessageContent, 0, Qt::AlignCenter);
            }
            break;
        case EMessageType::FILE :
            {
                SFileInfo info;

                QPixmap pixmap;

                QHBoxLayout* pMainHBoxLayout = new QHBoxLayout(this);
                pMainHBoxLayout->setContentsMargins(0, 0, 0, 0);
                this->setLayout(pMainHBoxLayout);

                if (ParseJsonContent(stUserData.stMessageInfo.strContent, info))
                {
                    // 解析文件内容和文件名称成功
                    switch (info.eFileType)
                    {
                        case EFileType::PICTURE :
                            {
                                this->m_pImageContainer = new ImageContainer(info.strContent, this);
                                pMainHBoxLayout->addWidget(this->m_pImageContainer);
                            }
                            break;
                        case EFileType::EXE :
                            pixmap.load(":/res/ico/exe.png");
                            break;
                        case EFileType::MUSIC :
                            pixmap.load(":/res/ico/mp3.png");
                            break;
                        case EFileType::NORMAL_FILE :
                            pixmap.load(":/res/ico/file.png");
                            break;
                        default :
                            break;
                    }

                    // 文件图标
                    this->m_pFileIcon = new QLabel(this);
                    this->m_pFileIcon->setFixedSize(40, 40);
                    this->m_pFileIcon->setScaledContents(true);
                    this->m_pFileIcon->setPixmap(pixmap.scaled(
                        QSize(this->m_pFileIcon->size()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

                    // 文件名称
                    this->m_pFileName = new QLabel(info.strFileName, this);
                    // this->m_pFileName->setPalette(pale);
                    this->m_pFileName->adjustSize();

                    // 文件大小
                    this->m_pFileSize = new QLabel(QString::number(info.uiFileSize), this);
                    // this->m_pFileSize->setPalette(pale);
                    this->m_pFileSize->adjustSize();

                    QHBoxLayout* pNameHBoxLayout = new QHBoxLayout();
                    pNameHBoxLayout->addWidget(this->m_pFileName);

                    QHBoxLayout* pSizeAndStateHBoxLayout = new QHBoxLayout();
                    pSizeAndStateHBoxLayout->addWidget(this->m_pFileSize);

                    QVBoxLayout* pVBoxLayout = new QVBoxLayout();
                    pVBoxLayout->addLayout(pNameHBoxLayout);
                    pVBoxLayout->addLayout(pSizeAndStateHBoxLayout);

                    pMainHBoxLayout->addWidget(this->m_pFileIcon);
                    pMainHBoxLayout->addLayout(pVBoxLayout);
                    // this->adjustSize();
                }
            }
            break;
        default :
            break;
    }
}

bool Bubble::ParseJsonContent(const QString& strOriginHson, SFileInfo& stFileInfo)
{
    bool bRet = false;
    QJsonParseError jsonError;
    QJsonDocument doucment =
        QJsonDocument::fromJson(strOriginHson.toUtf8(), &jsonError);   // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {   // 解析未发生错误
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("name"))
            {
                QJsonValue value = object.value("name");
                if (value.toVariant().isValid())
                {
                    stFileInfo.strFileName = value.toVariant().toString();
                }
            }

            if (object.contains("content"))
            {
                QJsonValue value = object.value("content");
                if (value.toVariant().isValid())
                {
                    stFileInfo.strContent = value.toVariant().toString();
                }
            }

            if (object.contains("type"))
            {
                QJsonValue value = object.value("type");
                if (value.toVariant().isValid())
                {
                    stFileInfo.eFileType = static_cast<EFileType>(value.toVariant().toUInt());
                }
            }

            if (object.contains("size"))
            {
                QJsonValue value = object.value("size");
                if (value.toVariant().isValid())
                {
                    stFileInfo.uiFileSize = value.toVariant().toUInt();
                }
            }

            bRet = true;
        }
    }

    return bRet;
}

MessageItemWidget::MessageItemWidget(const SUserData& stUserData, QWidget* parent)
{
    QHBoxLayout* pMainHBoxLayout = new QHBoxLayout(this);
    pMainHBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(pMainHBoxLayout);

    // 用户头像
    this->m_pUserHead = new QLabel(this);
    this->m_pUserHead->setFixedSize(36, 36);
    this->m_pUserHead->setScaledContents(true);
    this->m_pUserHead->setPixmap(stUserData.pixUserHead.scaled(
        stUserData.pixUserHead.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // 用户名称
    this->m_pUserName = new QLabel(stUserData.strUserName, this);
    this->m_pUserName->setStyleSheet("QLabel { color : rgb(18,150,219); font-size: 11pt;}");
    this->m_pUserName->adjustSize();

    // 发送时间
    this->m_pSendTime = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"), this);
    this->m_pSendTime->setStyleSheet("QLabel { color : gray; font-size: 9pt;}");
    this->m_pSendTime->adjustSize();

    // 消息内容
    this->m_pBubbleWidget = new Bubble(stUserData, this);

    if (Qt::AlignRight == stUserData.alignment)
    {
        // 水平布局
        QHBoxLayout* pHeadHBoxLayout = new QHBoxLayout;
        pHeadHBoxLayout->setContentsMargins(0, 0, 0, 0);

        // 垂直布局
        QVBoxLayout* pContentVBoxLayout = new QVBoxLayout;
        pContentVBoxLayout->setContentsMargins(0, 0, 0, 0);

        QHBoxLayout* pMessageHBoxLayout = new QHBoxLayout;
        pMessageHBoxLayout->setContentsMargins(0, 0, 0, 0);

        pHeadHBoxLayout->addStretch();
        pHeadHBoxLayout->addWidget(this->m_pSendTime);
        pHeadHBoxLayout->addSpacing(2);
        pHeadHBoxLayout->addWidget(this->m_pUserName);

        pMessageHBoxLayout->addStretch();
        pMessageHBoxLayout->addWidget(this->m_pBubbleWidget);

        pContentVBoxLayout->addLayout(pHeadHBoxLayout);
        pContentVBoxLayout->addLayout(pMessageHBoxLayout);

        pMainHBoxLayout->addLayout(pContentVBoxLayout);
        pMainHBoxLayout->addSpacing(3);
        pMainHBoxLayout->addWidget(this->m_pUserHead, 0, Qt::AlignTop);
    }
    else
    {
        // 水平布局
        QHBoxLayout* pHeadHBoxLayout = new QHBoxLayout;
        pHeadHBoxLayout->setContentsMargins(0, 0, 0, 0);

        // 垂直布局
        QVBoxLayout* pContentVBoxLayout = new QVBoxLayout;
        pContentVBoxLayout->setContentsMargins(0, 0, 0, 0);

        QHBoxLayout* pMessageHBoxLayout = new QHBoxLayout;
        pMessageHBoxLayout->setContentsMargins(0, 0, 0, 0);

        pHeadHBoxLayout->addWidget(this->m_pUserName);
        pHeadHBoxLayout->addSpacing(2);
        pHeadHBoxLayout->addWidget(this->m_pSendTime);
        pHeadHBoxLayout->addStretch();

        pMessageHBoxLayout->addWidget(this->m_pBubbleWidget);
        pMessageHBoxLayout->addStretch();

        pContentVBoxLayout->addLayout(pHeadHBoxLayout);
        pContentVBoxLayout->addLayout(pMessageHBoxLayout);

        pMainHBoxLayout->addWidget(this->m_pUserHead, 0, Qt::AlignTop);
        pMainHBoxLayout->addSpacing(3);
        pMainHBoxLayout->addLayout(pContentVBoxLayout);
    }
    this->adjustSize();
}
