#pragma once

#include "chatwindow.h"
#include "defaultwindow.h"
#include "friendchatlist.h"
#include <QStackedLayout>
#include <QWidget>
#include <QMap>

class ChatPage : public QWidget
{
    Q_OBJECT
public:
    explicit ChatPage(QWidget* parent = nullptr);

    /**
     * @brief 创建聊天窗口
     * @param stUserData
     */
    void CreateChatWindow(SUserData& stUserData);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    void InitSignalSlot();

signals:

private:
    // 好友消息列表
    FriendChatList* m_pFriendChatList { nullptr };
    // 存储聊天窗口
    QStackedLayout* m_pStackLayout { nullptr };
    // 默认聊天页面
    DefaultWindow* m_pDefaultWindow { nullptr };
    // 用户数据和聊天窗口
    QMap<QListWidgetItem*, ChatWindow*> m_mapUserAndChatWindow;
};
