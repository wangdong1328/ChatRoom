#pragma once

#include "global.h"
#include "imagecontainer.h"
#include <QLabel>
#include <QTextEdit>
#include <QWidget>

class Bubble final : public QWidget
{
    Q_OBJECT
public:
    explicit Bubble(const SUserData& stUserData, QWidget* parent = nullptr);

private:
    bool ParseJsonContent(const QString& strOrigin, SFileInfo& sFileInfo);

private:
    // 消息内容
    QLabel* m_pMessageContent;
    // 照片
    ImageContainer* m_pImageContainer { nullptr };
    // 文件图标
    QLabel* m_pFileIcon { nullptr };
    // 文件名称
    QLabel* m_pFileName { nullptr };
    // 文件大小
    QLabel* m_pFileSize { nullptr };
};

class MessageItemWidget final : public QWidget
{
    Q_OBJECT
public:
    explicit MessageItemWidget(const SUserData& stUserData, QWidget* parent = nullptr);

signals:

private:
    // 用户头像
    QLabel* m_pUserHead { nullptr };
    // 用户名称
    QLabel* m_pUserName { nullptr };
    // 时间
    QLabel* m_pSendTime { nullptr };
    // 冒泡窗口
    Bubble* m_pBubbleWidget { nullptr };
};
