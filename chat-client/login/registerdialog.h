/**
 * @file    : registerdialog.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   :
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

#include "baselogindialog.h"

class RegisterDialog final : public BaseLoginDialog
{
    Q_OBJECT
public:
    explicit RegisterDialog(QWidget* parent = nullptr);

    // QObject interface
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    void OnRegisterButtonClick();

signals:
    void LoginClickSignal();

private:
    // 重复密码组件
    LineEditComponent* m_pRePasswordLineEdit { nullptr };
};
