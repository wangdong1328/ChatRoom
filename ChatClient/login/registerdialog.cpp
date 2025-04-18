#include "registerdialog.h"
#include "passwordcomponent.h"

RegisterDialog::RegisterDialog(QWidget* parent) : BaseLoginDialog { parent }
{
    m_pRePassworddLineEdit = new PasswordComponent(":/res/ico/MajesticonsLock.png", this);

    m_pContentVBoxLayout->insertSpacing(3, 10);
    m_pContentVBoxLayout->insertWidget(4, m_pRePassworddLineEdit);

    m_pRegisterButton->setText("登录账户");

    m_pLoginButton->SetButtonText("注 册");
}

bool RegisterDialog::eventFilter(QObject* watched, QEvent* event)
{
    if ((this->m_pLoginButton == watched) && (QEvent::MouseButtonPress == event->type()))
    {
        qDebug() << m_pAccountLineEdit->GetText() << ":" << m_pPasswordLineEdit->GetText();
        // 处理登录按钮
        return true;
    }
    else if ((this->m_pRegisterButton == watched) && (QEvent::MouseButtonPress == event->type()))
    {
        // 处理注册按钮
        emit LoginClickSignal();
        return true;
    }

    return BaseLoginDialog::eventFilter(watched, event);
}
