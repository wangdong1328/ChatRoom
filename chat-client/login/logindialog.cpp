#include "logindialog.h"
#include "notification.h"

LoginDialog::LoginDialog(QWidget* parent) : BaseLoginDialog(parent) {}

bool LoginDialog::eventFilter(QObject* watched, QEvent* event)
{
    if ((this->m_pLoginButton == watched) && (QEvent::MouseButtonPress == event->type()))
    {
        qDebug() << m_pAccountLineEdit->GetText() << ":" << m_pPasswordLineEdit->GetText();

        Notification* pNotification = new Notification("密码长度不能小于6位!", this);
        pNotification->show();

        // 处理登录按钮
        return true;
    }
    else if ((this->m_pRegisterButton == watched) && (QEvent::MouseButtonPress == event->type()))
    {
        // 处理注册按钮
        emit RegisterClickSignal();
        return true;
    }

    return FramelessWindowForDialog::eventFilter(watched, event);
}

void LoginDialog::OnLoginButtonClick() {}
