#include "applicationfeaturebar.h"

#include <QPainter>

ApplicationFeatureBar::ApplicationFeatureBar(QWidget* parent) : QWidget { parent }
{
    this->setFixedWidth(60);

    this->m_pMainVBoxLayout = new QVBoxLayout(this);
    this->m_pMainVBoxLayout->setContentsMargins(0, 11, 0, 11);
    this->m_pMainVBoxLayout->setSpacing(10);
    this->setLayout(this->m_pMainVBoxLayout);

    this->IncreaseFeature(QString(":/res/ico/message_unselected.png"),
                          QString(":/res/ico/message_selected.png"), "消息");
    this->IncreaseFeature(QString(":/res/ico/friend_unselected.png"),
                          QString(":/res/ico/friend_selected.png"), QString("好友"));
    this->IncreaseFeature(QString(":/res/ico/account_unselect.png"), QString(":/res/ico/account_select.png"),
                          QString("账户"));

    this->m_pMainVBoxLayout->addStretch();
}

void ApplicationFeatureBar::IncreaseFeature(const QString& strUnSelectIcon, const QString& strSelectIcon,
                                            const QString& strButtonText)
{
    FeatureButton* pFeatureButton =
        new FeatureButton(strUnSelectIcon, strSelectIcon, strButtonText, this->m_usItemIndex, this);

    this->m_pMainVBoxLayout->addWidget(pFeatureButton, 0, Qt::AlignCenter);
    connect(pFeatureButton, &FeatureButton::clicked, this,
            &ApplicationFeatureBar::OnFeatureButtonClickedSlot);
    this->m_usItemIndex++;
}

void ApplicationFeatureBar::OnFeatureButtonClickedSlot(const unsigned short usItemIndex)
{
    emit ItemChangedSignal(usItemIndex);

    for (int iIndex = 0; iIndex < this->m_pMainVBoxLayout->count(); iIndex++)
    {
        QLayoutItem* pItem = m_pMainVBoxLayout->itemAt(iIndex);

        FeatureButton* pFeatureButton = static_cast<FeatureButton*>(pItem->widget());
        if (pFeatureButton)
        {
            if (pFeatureButton->GetCurrentIndex() != usItemIndex)
            {
                pFeatureButton->SetUnSelected();
            }
        }
    }
}

FeatureButton::FeatureButton(const QString& strNormalIcon, const QString& strSelectIcon,
                             const QString& strButtonText, const unsigned short usButtonIndex,
                             QWidget* parent)
{
    this->m_usButtonIndex = usButtonIndex;

    if (0 == this->m_usButtonIndex)
    {
        this->m_bIsPressed = true;
    }

    this->setFixedSize(parent->width() - 20, parent->width() - 20);
    this->setCursor(Qt::PointingHandCursor);
    this->m_pixNormalPixmap.load(strNormalIcon);
    this->m_pixSelectedPixmap.load(strSelectIcon);
    this->setToolTip(strButtonText);
}

void FeatureButton::SetUnSelected()
{
    this->m_bIsPressed = false;
    update();
}

void FeatureButton::SetSelected()
{
    this->m_bIsPressed = true;
    update();
}

void FeatureButton::mousePressEvent(QMouseEvent* event)
{
    if (!this->m_bIsPressed)
    {
        this->m_bIsPressed = true;
        this->update();
        emit this->clicked(this->m_usButtonIndex);
    }
}
void FeatureButton::enterEvent(QEnterEvent* event)
{
    this->m_bIsHover = true;
    update();
}

void FeatureButton::leaveEvent(QEvent* event)
{
    this->m_bIsHover = false;
    update();
}

void FeatureButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                           QPainter::SmoothPixmapTransform);

    if (this->m_bIsPressed)
    {
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::gray);
        painter.drawRoundedRect(QRect(this->rect()), 15, 15);

        painter.restore();

        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::NoBrush);

        painter.drawPixmap(
            QRect(this->rect().center().x() - (18 / 2), this->rect().center().y() - (18 / 2), 18, 18),
            this->m_pixSelectedPixmap.scaled(QSize(25, 25), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        painter.restore();
    }
    else if (this->m_bIsHover)
    {
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 0, 0, 20));
        painter.drawRoundedRect(QRect(this->rect()), 15, 15);

        painter.restore();

        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::NoBrush);

        painter.drawPixmap(
            QRect(this->rect().center().x() - (18 / 2), this->rect().center().y() - (18 / 2), 18, 18),
            this->m_pixSelectedPixmap.scaled(QSize(25, 25), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        painter.restore();
    }
    else
    {
        painter.save();
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::NoBrush);

        painter.drawPixmap(
            QRect(this->rect().center().x() - (18 / 2), this->rect().center().y() - (18 / 2), 18, 18),
            this->m_pixNormalPixmap.scaled(QSize(25, 25), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

        painter.restore();
    }
}
