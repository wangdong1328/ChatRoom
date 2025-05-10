#pragma once

#include "normaltitlebar.h"
#include <QGraphicsDropShadowEffect>
#include <QListWidget>
#include <QWidget>

class SystemNotification final : public QWidget
{
    Q_OBJECT
public:
    explicit SystemNotification(QWidget* parent = nullptr);

signals:

private:
    // 阴影效果
    QGraphicsDropShadowEffect* m_pShadowEffect { nullptr };
    // 标题栏
    NormalTitleBar* m_pNormalTitleBar { nullptr };
    // 通知
    QLabel* m_pUserNotification { nullptr };
    // 列表窗口
    QListWidget* m_pUserNotificationList { nullptr };
    // 系统通知
    QLabel* m_pSystemNotification { nullptr };
    // 系统通知列表
    QListWidget* m_pSystemNotificationList { nullptr };
};
