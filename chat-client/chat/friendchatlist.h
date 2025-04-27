#pragma once

#include "global.h"
#include <QListWidgetItem>
#include <QWidget>
#include <QLabel>

class FriendChatList : public QWidget
{
    Q_OBJECT
public:
    explicit FriendChatList(QWidget* parent = nullptr);

    /**
     * @brief 增加列表项
     * @param pItem
     */
    void IncreaseChatItem(QListWidgetItem* pItem);

    /**
     * @brief IsExistFriendChatItem
     * @param strAccount
     * @return 账户是否存在
     */
    int IsExistFriendChatItem(const QString& strAccount);

    /**
     * @brief SetItemSelected
     * @param strAccount
     */
    void SetItemSelected(const QString& strAccount);

    /**
     * @brief SetItemData
     * @param index
     * @param stUserData
     */
    void SetItemData(const int index, const SUserData& stUserData);

    /**
     * @brief GetItemData
     * @param index
     * @return
     */
    SUserData GetItemData(const int index) const;

signals:
    void ItemClickedSignal(const SUserData& stUserData);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    // 消息标题
    QLabel* m_pTitleLabel { nullptr };
    // 编辑消息
    QLabel* m_pEditLabel { nullptr };
    // 存储消息列表
    QListWidget* m_pChatListWidget { nullptr };
};

class ListWidgetItem : public QListWidgetItem
{
public:
    explicit ListWidgetItem(QWidget* parent = nullptr);

    // QListWidgetItem interface
public:
    virtual bool operator<(const QListWidgetItem& other) const override;
};
