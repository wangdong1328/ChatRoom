/**
 * @file    : buttoncomponent.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   : 按钮组件
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

#include <QLabel>
#include <QWidget>

class ButtonComponent : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonComponent(const QString& strButtonText, QWidget* parent = nullptr);

    /**
     * @brief 设置按钮文本
     * @param strButtonText
     */
    void SetButtonText(const QString& strButtonText);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QLabel* m_pButtonText { nullptr };
};
