#pragma once

#include <QGraphicsDropShadowEffect>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>

class Notification : public QWidget
{
    Q_OBJECT
public:
    explicit Notification(const QString& strText, QWidget* parent, unsigned int uiTime = 3000);

    // QWidget interface
protected:
    /**
     * @brief : 绘制界面
     * @param : event, 绘制事件
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief : 显示界面
     * @param : event, 显示事件
     */
    void showEvent(QShowEvent* event) override;

private:
    void Init();

    /**
     * @brief 设置文本
     * @param strText
     */
    void SetText(const QString& strText);

private:
    // 窗口阴影效果
    QGraphicsDropShadowEffect* m_pShadowEffect { nullptr };
    // 文本
    QLabel* m_pTextLabel { nullptr };
    // 动画类
    QPropertyAnimation* m_pPropertyAnimation { nullptr };
    // 显示时间
    unsigned int m_uiShowTime { 3000 };
};
