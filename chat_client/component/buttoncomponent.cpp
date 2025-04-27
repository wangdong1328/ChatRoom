#include "buttoncomponent.h"
#include <QHBoxLayout>
#include <QPainter>

ButtonComponent::ButtonComponent(const QString& strButtonText, QWidget* parent) : QWidget(parent)
{
    this->setFixedHeight(40);

    QHBoxLayout* pMainHLayout = new QHBoxLayout(this);
    this->setLayout(pMainHLayout);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    m_pButtonText = new QLabel(strButtonText, this);
    m_pButtonText->setPalette(palette);

    // 根据内容自动调整控件的大小
    m_pButtonText->adjustSize();
    pMainHLayout->addWidget(m_pButtonText, 0, Qt::AlignCenter);

    this->setCursor(Qt::PointingHandCursor);
}

void ButtonComponent::SetButtonText(const QString& strButtonText)
{
    m_pButtonText->setText(strButtonText);
}

void ButtonComponent::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // 设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0x0099ff));

    // 绘制圆角矩形
    painter.drawRoundedRect(this->rect(), 10, 10);
}
