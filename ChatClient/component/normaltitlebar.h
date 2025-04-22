/**
 * @file    : normaltitlebar.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   : 带关闭按钮的标题栏
 * @version : 0.1
 * @date    : 2025-04-18
 *
 * @copyright Copyright (c) 2025
 *
 **********************************************************
 *
 * @Attention   :
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version   <th>Author       <th>Description
 * <tr><td>2025-04-18 <td>1.0       <td>wangdong     <td>创建初始版本
 * </table>
 *
 */
#pragma once

#include <QWidget>
#include <QLabel>
#include <QEvent>

class NormalTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit NormalTitleBar(QWidget* parent = nullptr, bool bIsDialog = false);

    // QObject interface
public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    // 关闭按钮
    QLabel* m_pCloseWindowLabel { nullptr };
    // 最小按钮
    QLabel* m_pMinWindowLabel { nullptr };
    // 最大按钮
    QLabel* m_pMaxWinodowLabel { nullptr };
    // 父窗口
    QWidget* m_pParentWidget { nullptr };
    // 是否为对话窗
    bool m_bIsDialog { false };
};
