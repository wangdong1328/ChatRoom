/**
 * @file    : logindialog.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   : 登录对话窗口
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

#include "baselogindialog.h"

class LoginDialog final : public BaseLoginDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);

    // QObject interface
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    void OnLoginButtonClick();

signals:
    // 注册按钮点击
    void RegisterClickSignal();
};
