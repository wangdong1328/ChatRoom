#include "applicationtitlebar.h"

#include <QHBoxLayout>

ApplicationTitleBar::ApplicationTitleBar(QWidget* parent) : QWidget { parent }
{
    QHBoxLayout* pMainLayout = new QHBoxLayout(this);
    pMainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(pMainLayout);

    // 窗口图标设置
    this->m_pIconLabel = new QLabel(this);
    this->m_pIconLabel->setFixedSize(25, 25);
    this->m_pIconLabel->setScaledContents(true);
    QPixmap pixmap(":/res/ico/TablerBrandUnity.png");
    pixmap = pixmap.scaled(QSize(this->m_pIconLabel->width(), this->m_pIconLabel->height()),
                           Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->m_pIconLabel->setPixmap(pixmap);

    // 窗口标题
    QFont font;
    font.setBold(true);
    font.setPixelSize(15);
    QPalette pale;
    pale.setColor(QPalette::WindowText, QColor(30, 110, 254));
    this->m_pTitleLabel = new QLabel(this);
    this->m_pTitleLabel->setText("聊天客户端");
    this->m_pTitleLabel->setAlignment(Qt::AlignCenter);
    this->m_pTitleLabel->setPalette(pale);
    this->m_pTitleLabel->setFont(font);
    this->m_pTitleLabel->adjustSize();

    // 搜索
    this->m_pSearchLabel = new QLabel(this);
    this->m_pSearchLabel->setCursor(Qt::PointingHandCursor);
    this->m_pSearchLabel->setFixedSize(18, 18);
    this->m_pSearchLabel->setScaledContents(true);
    pixmap.load(":/res/ico/RiSearchLine.png");
    this->m_pSearchLabel->setPixmap(pixmap);
    this->m_pSearchLabel->installEventFilter(this);

    // 通知
    pixmap.load(":/res/ico/RiNotification3Line.png");
    this->m_pIconWithRedPoint = new IconWithRedPoint(QSize(28, 28), pixmap, this);
    this->m_pIconWithRedPoint->SetUnRead(true);

    // 下拉框
    this->m_pPullDownListLabel = new QLabel(this);
    this->m_pPullDownListLabel->setCursor(Qt::PointingHandCursor);
    this->m_pPullDownListLabel->setFixedSize(18, 18);
    this->m_pPullDownListLabel->setScaledContents(true);
    pixmap.load(":/res/ico/IconamoonArrowDown2Bold.png");
    this->m_pPullDownListLabel->setPixmap(pixmap);
    this->m_pPullDownListLabel->installEventFilter(this);

    // 标题栏
    this->m_pNormalTitleBar = new NormalTitleBar(parent);
    this->m_pNormalTitleBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    pMainLayout->addWidget(m_pIconLabel);
    pMainLayout->addSpacing(10);
    pMainLayout->addWidget(m_pTitleLabel);
    pMainLayout->addStretch();

    pMainLayout->addWidget(m_pIconWithRedPoint);
    pMainLayout->addSpacing(10);
    pMainLayout->addWidget(m_pSearchLabel);
    pMainLayout->addSpacing(10);
    pMainLayout->addWidget(m_pPullDownListLabel);
    pMainLayout->addSpacing(20);
    pMainLayout->addWidget(m_pNormalTitleBar);
}
