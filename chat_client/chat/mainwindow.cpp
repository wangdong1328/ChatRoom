#include "mainwindow.h"

#include <QPainter>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : FramelessWindow(parent)
{
    QVBoxLayout* pMainLayout = new QVBoxLayout(this);
    pMainLayout->setContentsMargins(9, 0, 0, 0);
    this->setLayout(pMainLayout);

    this->setAttribute(Qt::WA_TranslucentBackground);   // 设置窗口背景透明
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setMinimumSize(1050, 750);

    this->m_pApplicationTitleBar = new ApplicationTitleBar(this);
    this->setTitleBar(this->m_pApplicationTitleBar);

    QHBoxLayout* pContentHBoxLayout = new QHBoxLayout;
    this->m_pApplicationFeatureBar = new ApplicationFeatureBar(this);

    this->m_pStackedLayout = new QStackedLayout;

    this->m_pChatPage = new ChatPage(this);
    this->m_pStackedLayout->addWidget(m_pChatPage);

    this->m_pFriendPage = new FriendPage(this);
    this->m_pStackedLayout->addWidget(m_pFriendPage);

    this->m_pAccountPage = new AccountPage(this);
    this->m_pStackedLayout->addWidget(m_pAccountPage);

    pContentHBoxLayout->addWidget(m_pApplicationFeatureBar);
    pContentHBoxLayout->addLayout(m_pStackedLayout);

    pMainLayout->addWidget(this->m_pApplicationTitleBar);
    pMainLayout->addLayout(pContentHBoxLayout);

    InitSignalSlot();
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(this->rect(), 8, 8);

    FramelessWindow::paintEvent(event);
}

void MainWindow::InitSignalSlot()
{
    connect(this->m_pApplicationFeatureBar, &ApplicationFeatureBar::ItemChangedSignal, this->m_pStackedLayout,
            &QStackedLayout::setCurrentIndex);
}
