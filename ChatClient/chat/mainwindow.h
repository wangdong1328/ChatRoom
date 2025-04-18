/**
 * @file    : mainwindow.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   : 聊天室主页面
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

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    // QWidget interface
protected:
    /**
     * @brief paintEvent 绘制界面
     *
     * @param event
     */
    virtual void paintEvent(QPaintEvent* event) override;
};
