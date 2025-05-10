#pragma once

#include "global.h"
#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>
#include <QWidget>

class ChatTitle final : public QWidget
{
public:
    explicit ChatTitle(const QString& strUserName, const QPixmap& pixUserHead, QWidget* parent);
    ~ChatTitle();

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    // 用户图像
    QLabel* m_pUserHead { nullptr };
    // 用户名
    QLabel* m_pUserName { nullptr };
};

class SendMessageButton final : public QWidget
{
public:
    explicit SendMessageButton(QWidget* parent = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;
};

class ChatMessageEdit final : public QWidget
{
    Q_OBJECT
public:
    explicit ChatMessageEdit(QWidget* parent = nullptr);

    // QObject interface
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

    // QWidget interface
    void paintEvent(QPaintEvent* event) override;

private:
    /**
     * @brief 发送消息
     */
    void SendMessage();

    /**
     * @brief 发送文件消息
     * @param strFilePath
     */
    void SendFileMessage(const QString& strFilePath);

signals:
    void SendMessageSignal(SMessageInfo stMessageInfo);
    // 清理聊天历史信号
    void SendClearChatHistorySignal();

private:
    // 文本框
    QTextEdit* m_pMessageEdit { nullptr };
    // 发送消息按钮
    SendMessageButton* m_pSendButton { nullptr };
    // 发送文件
    QLabel* m_pFileButton { nullptr };
    // 表情按钮
    QLabel* m_pEmojiButton { nullptr };
    // 表情按钮
    QLabel* m_pClearButton { nullptr };
};

class ChatWindow final : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWindow(SUserData& stUserData, QWidget* parent = nullptr);

    /**
     * @brief 获取当前用户数据
     *
     * @return
     */
    SUserData CurrentUserData() const { return m_stUserData; }

    /**
     * @brief 增加消息项
     *
     * @param stUserData
     */
    void IncreaseMessageItem(const SUserData& stUserData);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;

signals:

private:
    // 用户数据
    SUserData m_stUserData;
    // 聊天标题
    ChatTitle* m_pChatTitle { nullptr };
    // 聊天内容列表
    QListWidget* m_pChatList { nullptr };
    // 聊天消息编辑
    ChatMessageEdit* m_pMessageEdit { nullptr };
};
