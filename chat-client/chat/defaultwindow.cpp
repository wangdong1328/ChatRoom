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
