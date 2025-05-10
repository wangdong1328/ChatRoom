#include "chatpage.h"

#include <QHBoxLayout>
#include <QPainter>

ChatPage::ChatPage(QWidget* parent) : QWidget { parent }
{
    qRegisterMetaType<SMessageInfo>("SMessageInfo");
    qRegisterMetaType<SUserData>("SUserData");

    QHBoxLayout* pMainLayout = new QHBoxLayout(this);
    pMainLayout->setContentsMargins(9, 0, 9, 0);
    this->setLayout(pMainLayout);

    this->m_pFriendChatList = new FriendChatList(this);
    this->m_pDefaultWindow = new DefaultWindow(this);

    this->m_pStackLayout = new QStackedLayout;
    m_pStackLayout->addWidget(this->m_pDefaultWindow);

    pMainLayout->addWidget(this->m_pFriendChatList);
    pMainLayout->addLayout(this->m_pStackLayout);

    InitSignalSlot();

    SUserData stUserData;
    stUserData.strUserName = "小猫喝水";
    stUserData.strUserAccount = "1000";
    stUserData.stMessageInfo.strContent = "别喝水了，快去钓鱼吧";
    CreateChatWindow(stUserData);
}

void ChatPage::CreateChatWindow(SUserData& stUserData)
{
    // 判断是否已存在此聊天窗口
    int iIndex = this->m_pFriendChatList->IsExistFriendChatItem(stUserData.strUserAccount);

    ChatWindow* pChatWindow = nullptr;
    if (iIndex != -1)
    {
        this->m_pFriendChatList->SetItemData(iIndex, stUserData);

        for (int i = 1; i < this->m_pStackLayout->count(); i++)
        {
            pChatWindow = qobject_cast<ChatWindow*>(this->m_pStackLayout->widget(i));
            if (pChatWindow)
            {
                if (pChatWindow->CurrentUserData().strUserAccount == stUserData.strUserAccount)
                {
                    // 给聊天页面增加消息
                    pChatWindow->IncreaseMessageItem(stUserData);
                    break;
                }
            }
        }
    }
    else
    {
        stUserData.iIndex = this->m_pStackLayout->count();

        pChatWindow = new ChatWindow(stUserData, this);
        ListWidgetItem* pItem = new ListWidgetItem();

        stUserData.bIsUnread = true;
        stUserData.iUnReadMessageNums++;

        pItem->setData(Qt::UserRole, QVariant::fromValue(stUserData));

        this->m_mapUserAndChatWindow.insert(pItem, pChatWindow);
        this->m_pFriendChatList->IncreaseChatItem(pItem);

        // 聊天页面添加消息
        pChatWindow->IncreaseMessageItem(stUserData);

        this->m_pStackLayout->addWidget(pChatWindow);
    }
}

void ChatPage::InitSignalSlot()
{
    connect(this->m_pFriendChatList, &FriendChatList::ItemClickedSignal, this,
            [&](const SUserData& stUserData) {
                this->m_pStackLayout->setCurrentIndex(stUserData.iIndex);
            });
}
