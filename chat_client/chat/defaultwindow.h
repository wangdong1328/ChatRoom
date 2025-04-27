#pragma once

#include <QLabel>
#include <QWidget>

class DefaultWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DefaultWindow(QWidget* parent = nullptr);

signals:

private:
    QLabel* m_pDefaultIcon { nullptr };

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;
};
