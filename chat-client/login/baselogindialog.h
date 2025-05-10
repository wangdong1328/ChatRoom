/**
 * @file    : basedialog.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   : 基础登录窗口
 * @version : 0.1
 * @date    : 2025-04-16
 *
 * @copyright Copyright (c) 2025
 *
 **********************************************************
 *
 * @Attention   :
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version   <th>Author       <th>Description
 * <tr><td>2025-04-16 <td>1.0       <td>wangdong     <td>创建初始版本
 * </table>
 *
 */
#pragma once

#include "framelesswindow.h"
#include "ButtonComponent.h"
#include "lineeditcomponent.h"
#include "normaltitlebar.h"

class BaseLoginDialog : public FramelessWindowForDialog
{
    Q_OBJECT

public:
    explicit BaseLoginDialog(QWidget* parent = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    // 显示窗口
    void OnShowSlot() { show(); }
    // 隐藏窗口
    void OnHideSlot() { hide(); }

signals:
    void ShowSignal();
    void HideSignal();

protected:
    // 账户组件
    LineEditComponent* m_pAccountLineEdit { nullptr };
    // 密码组件
    LineEditComponent* m_pPasswordLineEdit { nullptr };
    // 密码组件
    ButtonComponent* m_pLoginButton { nullptr };
    // 注册账户
    QLabel* m_pRegisterButton { nullptr };
    // 标题栏
    NormalTitleBar* m_pNormalTitleBar { nullptr };
    // 垂直布局
    QVBoxLayout* m_pMainVBoxLayout { nullptr };
    // 内容布局
    QVBoxLayout* m_pContentVBoxLayout { nullptr };
};
