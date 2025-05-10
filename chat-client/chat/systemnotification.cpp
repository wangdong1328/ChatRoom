#include "systemnotification.h"

#include <QVBoxLayout>

SystemNotification::SystemNotification(QWidget* parent) : QWidget { parent }
{
    this->setFixedSize(200, parent->height() - 30);

    QVBoxLayout* pMainVBoxLayout = new QVBoxLayout(this);
    pMainVBoxLayout->setContentsMargins(9, 0, 9, 9);
    this->setLayout(pMainVBoxLayout);

    this->m_pNormalTitleBar = new NormalTitleBar(this, true);

    QPalette pale;

    QFont font;
    font.setPixelSize(11);
    this->m_pUserNotification = new QLabel("好友通知", this);
    this->m_pUserNotification->setFont(font);
    this->m_pUserNotification->adjustSize();
    pale.setColor(QPalette::Window, Qt::transparent);

    this->m_pUserNotificationList = new QListWidget(this);
    this->m_pUserNotificationList->setPalette(pale);
    this->m_pUserNotificationList->setFrameShape(QFrame::NoFrame);

    this->m_pSystemNotification = new QLabel("系统通知", this);
    this->m_pSystemNotification->setFont(font);
    this->m_pSystemNotification->adjustSize();

    this->m_pSystemNotificationList = new QListWidget(this);
    this->m_pSystemNotificationList->setFrameShape(QFrame::NoFrame);
    this->m_pSystemNotificationList->setPalette(pale);

    pMainVBoxLayout->addWidget(this->m_pNormalTitleBar);
    pMainVBoxLayout->addSpacing(5);
    pMainVBoxLayout->addWidget(this->m_pUserNotification, 0, Qt::AlignLeft);
    pMainVBoxLayout->addWidget(this->m_pUserNotificationList);
    pMainVBoxLayout->addWidget(this->m_pSystemNotification);
    pMainVBoxLayout->addWidget(this->m_pSystemNotificationList);

    this->m_pShadowEffect = new QGraphicsDropShadowEffect(this);
    this->m_pShadowEffect->setOffset(0, 0);
    this->m_pShadowEffect->setBlurRadius(8);
    this->m_pShadowEffect->setColor(Qt::gray);
    this->setGraphicsEffect(this->m_pShadowEffect);
}
