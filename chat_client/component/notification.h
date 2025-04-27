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
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void showEvent(QShowEvent* event) override;

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
