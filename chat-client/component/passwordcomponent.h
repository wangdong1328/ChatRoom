/**
 * @file    : passwordcomponent.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   : 密码组件
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

#include "lineeditcomponent.h"

#include <QEvent>

class PasswordComponent : public LineEditComponent
{
public:
    explicit PasswordComponent(const QString& strIconPath, QWidget* parent = nullptr);

    // QObject interface
public:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
    // LineEdit右侧图标
    QLabel* m_pRightIconLabel { nullptr };
    // 密码可见按钮
    QPixmap m_pixmapVisible;
    // 密码不可见按钮
    QPixmap m_pixmapInVisible;
};
