#pragma once

#include "global.h"
#include "imagecontainer.h"
#include <QLabel>
#include <QWidget>

class Bubble : public QWidget
{
    Q_OBJECT
public:
    explicit Bubble(const SUserData& stUserData, QWidget* parent = nullptr);

private:
    bool ParseJsonContent(const QString& strOrigin, SFileInfo& sFileInfo);

private:
    // 消息内容
    QLabel* m_pMessageContent { nullptr };
    // 照片
    ImageContainer* m_pImageContainer { nullptr };
    // 文件图标
    QLabel* m_pFileIcon { nullptr };
    // 文件名称
    QLabel* m_pFileName { nullptr };
    // 文件大小
    QLabel* m_pFileSize { nullptr };

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

class MessageItemWidget : public QWidget
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
