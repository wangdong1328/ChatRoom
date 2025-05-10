#pragma once

#include <QLabel>
#include <QWidget>

class DefaultWindow final : public QWidget
{
    Q_OBJECT
public:
    explicit DefaultWindow(QWidget* parent = nullptr);

signals:

private:
    QLabel* m_pDefaultIcon { nullptr };
};
