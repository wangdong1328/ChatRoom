#pragma once

#include "iconwithredpoint.h"
#include "normaltitlebar.h"
#include <QWidget>
#include <QLabel>
#include <QEvent>

class ApplicationTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationTitleBar(QWidget* parent = nullptr);

signals:
    // 显示系统通知信号
    void ShowSystemNotificationSignal();
    // 显示下拉列表信号
    void ShowPullDownListSignal();
    // 显示搜索信号
    void ShowSearchSignal();

private:
    // 窗口图标
    QLabel* m_pIconLabel { nullptr };
    // 窗口标题
    QLabel* m_pTitleLabel { nullptr };
    // 搜索
    QLabel* m_pSearchLabel { nullptr };
    // 带红点的图标
    IconWithRedPoint* m_pIconWithRedPoint { nullptr };
    // 下拉框
    QLabel* m_pPullDownListLabel { nullptr };

    // 最小/最大和关闭按钮
    NormalTitleBar* m_pNormalTitleBar { nullptr };

    // QObject interface
public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
};
