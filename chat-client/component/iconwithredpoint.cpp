#include "iconwithredpoint.h"

#include <QPainter>

IconWithRedPoint::IconWithRedPoint(const QSize& size, const QPixmap& pixmap, QWidget* parent)
{
    this->setFixedSize(size);
    this->m_pIconLabel = new QLabel(this);
    this->m_pIconLabel->setFixedSize(18, 18);
    this->m_pIconLabel->setScaledContents(true);
    this->m_pIconLabel->setPixmap(pixmap);
    this->m_pIconLabel->setGeometry(
        QRect(QPoint(this->rect().center().x() - (this->m_pIconLabel->width() / 2),
                     this->rect().center().y() - (this->m_pIconLabel->height() / 2)),
              QSize(this->m_pIconLabel->size())));
}

void IconWithRedPoint::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if (this->m_bUnRead)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
        painter.drawEllipse(QRect(QPoint(this->rect().right() - 10, this->rect().top() + 1), QSize(6, 6)));
    }
}
