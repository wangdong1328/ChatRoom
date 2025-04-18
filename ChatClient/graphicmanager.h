/**
 * @file    : graphicmanager.h
 * @author  : wangdong (wangdong1328@163.com)
 * @brief   : 图形管理类
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
#include <QObject>
#include "logindialog.h"
#include "registerdialog.h"

class GraphicManager : public QObject
{
    Q_OBJECT
public:
    // 删除拷贝构造函数和赋值函数
    GraphicManager(const GraphicManager&) = delete;
    GraphicManager& operator=(const GraphicManager&) = delete;

    /**
     * @brief GetInstance
     * @return
     */
    static GraphicManager& GetInstance();

    /**
     * @brief Init
     */
    void Init();

private:
    GraphicManager() = default;

    /**
     * @brief 初始化信号和槽
     */
    void InitSignalSlot();

private:
    // 登录对话窗
    LoginDialog* m_pLoginDialog { nullptr };
    // 注册对话窗
    RegisterDialog* m_pRegisterDialog { nullptr };
};
