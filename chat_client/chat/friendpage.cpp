#include "friendpage.h"

#include <QPainter>

FriendPage::FriendPage(QWidget* parent) {}

void FriendPage::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::transparent);
    painter.drawRoundedRect(this->rect(), 15, 15);
}
