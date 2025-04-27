#pragma once

#include "iconwithredpoint.h"
#include "normaltitlebar.h"
#include <QWidget>
#include <QLabel>

class ApplicationTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationTitleBar(QWidget* parent = nullptr);

signals:

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
};
