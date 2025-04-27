#include "defaultwindow.h"

#include <QHBoxLayout>
#include <QPainter>

DefaultWindow::DefaultWindow(QWidget* parent) : QWidget { parent }
{
    QHBoxLayout* main_lay = new QHBoxLayout(this);
    this->setLayout(main_lay);

    this->m_pDefaultIcon = new QLabel(this);
    this->m_pDefaultIcon->setFixedSize(80, 80);
    this->m_pDefaultIcon->setScaledContents(true);
    QPixmap pixmap(":/res/ico/TablerBrandUnity_empty.png");
    pixmap =
        pixmap.scaled(QSize(this->m_pDefaultIcon->size()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->m_pDefaultIcon->setPixmap(pixmap);

    main_lay->addWidget(this->m_pDefaultIcon, 0, Qt::AlignCenter);
}

void DefaultWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(QColor(0, 0, 0, 20));
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(QPoint(this->rect().topLeft()), QPoint(this->rect().bottomLeft()));
    painter.restore();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::transparent);
    painter.drawRoundedRect(this->rect(), 15, 15);
    painter.restore();
}
