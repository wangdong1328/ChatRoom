#include "passwordcomponent.h"

PasswordComponent::PasswordComponent(const QString& strIconPath, QWidget* parent) :
    LineEditComponent(strIconPath, "输入密码", parent)
{
    this->m_pRightIconLabel = new QLabel(this);
    this->m_pRightIconLabel->setFixedSize(19, 19);
    this->m_pRightIconLabel->setScaledContents(true);

    // 添加进布局
    m_pMainHBoxLayout->addWidget(m_pRightIconLabel);
    // 安装事件过滤
    this->m_pRightIconLabel->installEventFilter(this);

    m_pixmapVisible.load(":/res/ico/MajesticonsEyeOn.png");
    m_pixmapVisible = m_pixmapVisible.scaled(QSize(this->m_pRightIconLabel->size()), Qt::IgnoreAspectRatio,
                                             Qt::SmoothTransformation);

    m_pixmapInVisible.load(":/res/ico/MajesticonsEyeOff.png");
    m_pixmapInVisible = m_pixmapInVisible.scaled(QSize(this->m_pRightIconLabel->size()),
                                                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    this->m_pRightIconLabel->setPixmap(m_pixmapInVisible);

    // 设置LineEdit为密码格式
    m_pLineEdit->setEchoMode(QLineEdit::Password);
    // 设置图标不可见
    this->m_pRightIconLabel->setVisible(false);

    connect(m_pLineEdit, &QLineEdit::textChanged, this, [&]() {
        if (m_pLineEdit->text().isEmpty())
        {
            this->m_pRightIconLabel->setVisible(false);
        }
        else
        {
            this->m_pRightIconLabel->setVisible(true);
        }
    });
}

bool PasswordComponent::eventFilter(QObject* watched, QEvent* event)
{
    if ((this->m_pRightIconLabel == watched) && this->m_pRightIconLabel->isVisible())
    {
        if (QEvent::MouseButtonPress == event->type())
        {
            this->m_pRightIconLabel->setPixmap(m_pixmapVisible);
            m_pLineEdit->setEchoMode(QLineEdit::Normal);
            return true;
        }
        else if (QEvent::MouseButtonRelease == event->type())
        {
            this->m_pRightIconLabel->setPixmap(m_pixmapInVisible);
            m_pLineEdit->setEchoMode(QLineEdit::Password);
            return true;
        }
    }

    return LineEditComponent::eventFilter(watched, event);
}
