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

#include "applicationfeaturebar.h"
#include "applicationtitlebar.h"
#include "chatpage.h"
#include "framelesswindow.h"

#include <QStackedLayout>

class MainWindow : public FramelessWindow
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

private:
    // 标题栏
    ApplicationTitleBar* m_pApplicationTitleBar { nullptr };
    // 应用菜单栏
    ApplicationFeatureBar* m_pApplicationFeatureBar { nullptr };
    // 栈布局
    QStackedLayout* m_pStackedLayout { nullptr };
    // 聊天页面
    ChatPage* m_pChatPage { nullptr };
};
