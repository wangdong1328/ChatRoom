#pragma once

#include <QLabel>
#include <QWidget>

class IconWithRedPoint final : public QWidget
{
    Q_OBJECT
public:
    explicit IconWithRedPoint(const QSize& size, const QPixmap& pixmap = QPixmap(),
                              QWidget* parent = nullptr);
    /**
     * @brief 设置是否为消息未读状态
     * @param bUnRead
     */
    void SetUnRead(bool bUnRead);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent* event) override;

signals:

private:
    // 图标Label
    QLabel* m_pIconLabel { nullptr };
    // 消息是否未读
    bool m_bUnRead { false };
};
