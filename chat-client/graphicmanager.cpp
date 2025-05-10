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
    m_pMainWindow = new MainWindow();

    InitSignalSlot();

    m_pMainWindow->show();
}

void GraphicManager::InitSignalSlot()
{
    connect(m_pLoginDialog, &LoginDialog::RegisterClickSignal, this, [&]()
    {
        m_pLoginDialog->OnHideSlot();
        m_pRegisterDialog->OnShowSlot();
    });

    connect(m_pRegisterDialog, &RegisterDialog::LoginClickSignal, this, [&]() {
        m_pRegisterDialog->OnHideSlot();
        m_pLoginDialog->OnShowSlot();
    });
}
