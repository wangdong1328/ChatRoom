#include "friendchatdelegate.h"
#include "global.h"

#include <QLabel>
#include <QPainter>

FriendChatDelegate::FriendChatDelegate(QObject* parent) : QStyledItemDelegate { parent } {}

void FriendChatDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                               const QModelIndex& index) const
{
    if (!index.isValid()) return;

    SUserData stUserData = index.data(Qt::UserRole).value<SUserData>();

    if (stUserData.pixUserHead.isNull() || stUserData.strUserName.isEmpty()) return;

    QStyleOptionViewItem viewoption(option);
    initStyleOption(&viewoption, index);

    painter->setRenderHints(
        QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform, true);

    QRect item_rect = option.rect;
    item_rect.adjust(2, 2, -2, -2);

    // 绘制头像
    QRect userheadRect = QRect(item_rect.left() + 2, item_rect.center().y() - (item_rect.height() - 20) / 2,
                               item_rect.height() - 20, item_rect.height() - 20);

    QLabel temp(stUserData.strUserName);
    temp.adjustSize();
    QRect userNameRect =
        QRect(userheadRect.right() + 7, userheadRect.top() - 3, temp.width() + 10, temp.height());

    temp.setText(stUserData.stMessageInfo.strContent);
    temp.adjustSize();

    QString message = "";
    if (temp.width() > (item_rect.width() - item_rect.height() - 30))
    {
        message = temp.text().left(12) + "...";
    }
    else
    {
        message = temp.text();
    }

    QRect userMessageRect =
        QRect(userNameRect.left(), userNameRect.bottom(), temp.width() + 30, temp.height());

    painter->save();
    if (option.state.testFlag(QStyle::State_Selected))
    {
        painter->setPen(QPen(QColor(165, 109, 203), 1));
        painter->setBrush(QColor(241, 243, 249));
        painter->drawRoundedRect(item_rect, 10, 10);
    }
    else if (option.state.testFlag(QStyle::State_MouseOver))
    {
        painter->setPen(QPen(QColor(165, 179, 203), 1));
        painter->setBrush(QColor(241, 243, 249));
        painter->drawRoundedRect(item_rect, 10, 10);
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::transparent);
        painter->drawRoundedRect(item_rect, 10, 10);
    }
    painter->restore();

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);

    painter->drawPixmap(userheadRect,
                        stUserData.pixUserHead.scaled(QSize(userheadRect.size()), Qt::IgnoreAspectRatio,
                                                      Qt::SmoothTransformation));
    painter->restore();

    painter->save();
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(userNameRect, Qt::AlignCenter, stUserData.strUserName);
    painter->restore();

    painter->save();
    painter->setPen(Qt::gray);
    painter->setBrush(Qt::NoBrush);
    QFont font = painter->font();
    font.setPointSize(font.pointSize() - 2);
    painter->setFont(font);
    painter->drawText(userMessageRect, Qt::AlignLeft, message);
    painter->restore();

    if (stUserData.bIsUnread)
    {
        QRectF unread_rect = QRectF(
            QPointF(item_rect.right() - 20, (userMessageRect.center().y() - static_cast<qreal>(60) / 2)),
            QSize(15, 15));
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::red);
        painter->drawEllipse(unread_rect);
        painter->restore();

        QFont font;
        font.setPixelSize(10);

        QRectF nums_rect;
        nums_rect.setSize(QSize(unread_rect.width() - 4, unread_rect.height() - 4));
        nums_rect.moveCenter(unread_rect.center());
        painter->save();
        painter->setPen(Qt::white);
        painter->setFont(font);
        painter->setBrush(Qt::NoBrush);
        painter->drawText(nums_rect, Qt::AlignCenter, QString::number(stUserData.iUnReadMessageNums));
        painter->restore();
    }
}

QSize FriendChatDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(60);
    return size;
}
