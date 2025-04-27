#pragma once

#include <QVBoxLayout>
#include <QWidget>

class ApplicationFeatureBar : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationFeatureBar(QWidget* parent = nullptr);

    /**
     * @brief IncreaseFeature
     * @param strSelectIcon
     * @param strUnSelectIcon
     * @param strButtonText
     */
    void IncreaseFeature(const QString& strUnSelectIcon, const QString& strSelectIcon,
                         const QString& strButtonText);

signals:
    void ItemChangedSignal(const unsigned short usItemIndex);

private slots:
    void OnFeatureButtonClickedSlot(const unsigned short usItemIndex);

private:
    // 垂直布局
    QVBoxLayout* m_pMainVBoxLayout { nullptr };
    // 项下标
    unsigned short m_usItemIndex { 0 };
};

class FeatureButton : public QWidget
{
    Q_OBJECT
public:
    FeatureButton(const QString& strNormalIcon, const QString& strSelectIcon, const QString& strButtonText,
                  const unsigned short usIndex, QWidget* parent = nullptr);

    /**
     * @brief 获取当前按钮的下标
     * @return
     */
    unsigned short GetCurrentIndex() const { return this->m_usButtonIndex; };

    /**
     * @brief SetUnSelected: 设置未选
     */
    void SetUnSelected();

    /**
     * @brief SetSelected: 设置已选
     */
    void SetSelected();

    // QWidget interface
protected:
    virtual void enterEvent(QEnterEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;

signals:
    void clicked(const unsigned short unButtonIndex);

private:
    QString strIconText;
    QPixmap m_pixSelectedPixmap;
    QPixmap m_pixNormalPixmap;

    bool m_bIsPressed { false };
    unsigned short m_usButtonIndex { 0 };
    bool m_bIsHover { false };
};
