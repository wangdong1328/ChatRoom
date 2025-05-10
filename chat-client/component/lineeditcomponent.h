/**
 * @file    : lineeditcomponent.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   : LineEdit 组件
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

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

class LineEditComponent : public QWidget
{
    Q_OBJECT
public:
    explicit LineEditComponent(const QString& strIconPath, const QString& setPlaceholderText = "",
                               QWidget* parent = nullptr);

    /**
     * @brief  获取输入的文本
     * @return 输入的文本
     */
    QString GetText() const;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;

signals:

protected:
    // 水平布局
    QHBoxLayout* m_pMainHBoxLayout { nullptr };
    // 输入控件
    QLineEdit* m_pLineEdit { nullptr };
    // LineEdit左侧图标
    QLabel* m_pLeftIcon { nullptr };
};
