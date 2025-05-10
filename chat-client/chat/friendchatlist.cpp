#include "friendchatlist.h"

#include "friendchatdelegate.h"
#include "global.h"
#include <QPainter>
#include <QVBoxLayout>

FriendChatList::FriendChatList(QWidget* parent) : QWidget { parent }
{
    this->setFixedWidth(200);

    QVBoxLayout* m_pMainVBoxLayout = new QVBoxLayout(this);
    m_pMainVBoxLayout->setContentsMargins(9, 0, 0, 0);
    this->setLayout(m_pMainVBoxLayout);

    QFont font;
    font.setBold(true);
    font.setPixelSize(14);
    QPalette pale;
    pale.setColor(QPalette::WindowText, Qt::black);

    QHBoxLayout* pTitleLayout = new QHBoxLayout;
    pTitleLayout->setContentsMargins(9, 0, 9, 0);

    this->m_pTitleLabel = new QLabel("", this);
    this->m_pTitleLabel->setFont(font);
    this->m_pTitleLabel->setPalette(pale);

    this->m_pEditLabel = new QLabel(this);
    this->m_pEditLabel->setFixedSize(15, 15);
    this->m_pEditLabel->setCursor(Qt::PointingHandCursor);
    this->m_pEditLabel->setScaledContents(true);
    QPixmap pixmap(":/res/ico/friend_edit_sel.png");
    this->m_pEditLabel->setPixmap(pixmap);

    pTitleLayout->addWidget(this->m_pTitleLabel);
    pTitleLayout->addStretch();
    pTitleLayout->addWidget(this->m_pEditLabel);

    pale.setColor(QPalette::Window, Qt::transparent);

    this->m_pChatListWidget = new QListWidget(this);
    this->m_pChatListWidget->setPalette(pale);
    this->m_pChatListWidget->setFrameShape(QFrame::NoFrame);
    this->m_pChatListWidget->sortItems(Qt::AscendingOrder);

    FriendChatDelegate* pFriendDlegate = new FriendChatDelegate(this);
    this->m_pChatListWidget->setItemDelegate(pFriendDlegate);

    m_pMainVBoxLayout->addLayout(pTitleLayout);
    m_pMainVBoxLayout->addSpacing(8);
    m_pMainVBoxLayout->addWidget(this->m_pChatListWidget);

    connect(this->m_pChatListWidget, &QListWidget::itemClicked, this, [&](QListWidgetItem* pItem) {
        SUserData stUserData = pItem->data(Qt::UserRole).value<SUserData>();
        if ((stUserData.iUnReadMessageNums != 0) || stUserData.bIsUnread)
        {
            stUserData.iUnReadMessageNums = 0;
            stUserData.bIsUnread = false;
            pItem->setData(Qt::UserRole, QVariant::fromValue(stUserData));
        }

        emit ItemClickedSignal(stUserData);
    });
}

void FriendChatList::IncreaseChatItem(QListWidgetItem* pItem)
{
    this->m_pChatListWidget->addItem(pItem);
    this->m_pChatListWidget->sortItems(Qt::DescendingOrder);
}

int FriendChatList::IsExistFriendChatItem(const QString& strAccount)
{
    for (int iIndex = 0; iIndex < this->m_pChatListWidget->count(); iIndex++)
    {
        QListWidgetItem* pItem = this->m_pChatListWidget->item(iIndex);
        SUserData stUserData = pItem->data(Qt::UserRole).value<SUserData>();
        if (stUserData.strUserAccount == strAccount)
        {
            return iIndex;
        }
    }
    return -1;
}
void FriendChatList::SetItemSelected(const QString& strAccount)
{
    for (int iIndex = 0; iIndex < this->m_pChatListWidget->count(); iIndex++)
    {
        QListWidgetItem* pItem = this->m_pChatListWidget->item(iIndex);
        SUserData stUserData = pItem->data(Qt::UserRole).value<SUserData>();
        if (stUserData.strUserAccount == strAccount)
        {
            pItem->setSelected(true);
            break;
        }
    }
}

void FriendChatList::SetItemData(const int index, const SUserData& stUserData)
{
    QListWidgetItem* pItem = this->m_pChatListWidget->item(index);
    SUserData stSelfUserData = pItem->data(Qt::UserRole).value<SUserData>();

    if (!pItem->isSelected())
    {
        stSelfUserData.iUnReadMessageNums++;
        stSelfUserData.bIsUnread = true;
    }

    stSelfUserData.stMessageInfo.strContent = stUserData.stMessageInfo.strContent;
    pItem->setData(Qt::UserRole, QVariant::fromValue(stSelfUserData));
}

SUserData FriendChatList::GetItemData(const int index) const
{
    QListWidgetItem* pItem = this->m_pChatListWidget->item(index);
    return pItem->data(Qt::UserRole).value<SUserData>();
}

void FriendChatList::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setPen(QColor(0, 0, 0, 20));
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(QPoint(this->rect().topLeft()), QPoint(this->rect().bottomLeft()));
    painter.restore();
}

ListWidgetItem::ListWidgetItem(QWidget* parent) {}

bool ListWidgetItem::operator<(const QListWidgetItem& other) const
{
    SUserData stSelfData = this->data(Qt::UserRole).value<SUserData>();
    SUserData stUserData = other.data(Qt::UserRole).value<SUserData>();

    if (stSelfData.bStatus != stUserData.bStatus)
    {
        return stSelfData.bStatus < stUserData.bStatus;
    }
    else
    {
        return stSelfData.strUserAccount < stUserData.strUserAccount;
    }

    return QListWidgetItem::operator<(other);
}
