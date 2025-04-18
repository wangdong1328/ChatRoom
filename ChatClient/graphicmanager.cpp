#include "graphicmanager.h"

GraphicManager& GraphicManager::GetInstance()
{
    static GraphicManager instance;
    return instance;
}

void GraphicManager::Init()
{
    m_pLoginDialog = new LoginDialog();
    m_pRegisterDialog = new RegisterDialog();

    InitSignalSlot();

    // 显示登录界面
    m_pLoginDialog->OnShowSlot();
}

void GraphicManager::InitSignalSlot()
{
    connect(m_pLoginDialog, &LoginDialog::RigisterClickSignal, this, [&]() {
        m_pLoginDialog->OnHideSlot();
        m_pRegisterDialog->OnShowSlot();
    });

    connect(m_pRegisterDialog, &RegisterDialog::LoginClickSignal, this, [&]() {
        m_pRegisterDialog->OnHideSlot();
        m_pLoginDialog->OnShowSlot();
    });
}
