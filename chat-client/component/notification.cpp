#include "notification.h"

#include <QPainter>
#include <QTimer>

Notification::Notification(const QString& strText, QWidget* parent, unsigned int uiTime /*= 3000*/) :
    QWidget(parent)
{
    // 设置窗口关闭时删除
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    Init();
    SetText(strText);
}

void Notification::SetText(const QString& strText)
{
    this->m_pTextLabel->setText(strText);
    this->m_pTextLabel->adjustSize();
    this->setFixedSize(this->m_pTextLabel->width() + 20, this->m_pTextLabel->height() + 10);
    this->m_pTextLabel->setGeometry(
        QRect(QPoint(this->rect().center().x() - (this->m_pTextLabel->width() / 2),
                     this->rect().center().y() - (this->m_pTextLabel->height() / 2)),
              QSize(this->m_pTextLabel->size())));
}

void Notification::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(this->rect(), 10, 10);

    QWidget::paintEvent(event);
}

void Notification::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);

    // 设置动画的起始和结束位置

    if (const QWidget* pParentWidget = qobject_cast<QWidget*>(this->parent()))
    {
        this->m_pPropertyAnimation->setDirection(QPropertyAnimation::Forward);
        this->m_pPropertyAnimation->setStartValue(
            QRect(QPoint(pParentWidget->rect().center().x() - (this->width() / 2),
                         pParentWidget->rect().top() - (this->height())),
                  QSize(this->size())));

        this->m_pPropertyAnimation->setEndValue(
            QRect(QPoint(pParentWidget->rect().center().x() - (this->width() / 2),
                         pParentWidget->rect().top() + 20),
                  QSize(this->size())));

        this->m_pPropertyAnimation->stop();
        this->m_pPropertyAnimation->start();
    }
}

void Notification::Init()
{
    this->m_pTextLabel = new QLabel(this);

    this->m_pShadowEffect = new QGraphicsDropShadowEffect(this);
    this->m_pShadowEffect->setBlurRadius(10);
    this->m_pShadowEffect->setOffset(0, 0);
    this->m_pShadowEffect->setColor(Qt::gray);
    this->setGraphicsEffect(this->m_pShadowEffect);

    if (this->parent())
    {
        // 设置动画
        m_pPropertyAnimation = new QPropertyAnimation(this, "geometry");
        m_pPropertyAnimation->setDuration(500);
        m_pPropertyAnimation->setEasingCurve(QEasingCurve::InOutQuad);

        connect(m_pPropertyAnimation, &QPropertyAnimation::finished, this, [=]() {
            if (QPropertyAnimation::Backward != this->m_pPropertyAnimation->direction())
            {
                QTimer::singleShot(m_uiShowTime, this, [=]() {
                    // 睡眠1秒后需要执行的代码
                    this->m_pPropertyAnimation->setDirection(QPropertyAnimation::Backward);
                    this->m_pPropertyAnimation->start();
                });
            }
            else
            {
                // 关闭窗口
                this->close();
            }
        });
    }
}
