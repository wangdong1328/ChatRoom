#pragma once

#include <QStyledItemDelegate>

class FriendChatDelegate final : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FriendChatDelegate(QObject* parent = nullptr);

signals:

    // QAbstractItemDelegate interface
public:
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
                       const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
