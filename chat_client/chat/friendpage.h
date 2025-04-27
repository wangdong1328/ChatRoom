#pragma once

#include <QWidget>

class FriendPage : public QWidget
{
    Q_OBJECT
public:
    explicit FriendPage(QWidget* parent = nullptr);

signals:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent* event) override;
};
