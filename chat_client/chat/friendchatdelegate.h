#pragma once

#include <QStyledItemDelegate>

class FriendChatDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FriendChatDelegate(QObject* parent = nullptr);

signals:

    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option,
                       const QModelIndex& index) const override;

    virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
