#include "baselogindialog.h"
#include "passwordcomponent.h"

#include <QPainter>
#include <QDebug>

BaseLoginDialog::BaseLoginDialog(QWidget* parent) : FramelessWindowForDialog(parent)
{
    this->setFixedSize(320, 450);

    // 主垂直布局
    m_pMainVBoxLayout = new QVBoxLayout(this);
    m_pMainVBoxLayout->setContentsMargins(11, 0, 11, 11);
    this->setLayout(m_pMainVBoxLayout);

    m_pNormalTitleBar = new NormalTitleBar("", this);
    this->setTitleBar(m_pNormalTitleBar);

    // 用户图像
    QLabel* pUserHeadLabel = new QLabel(this);
    pUserHeadLabel->setFixedSize(80, 80);
    pUserHeadLabel->setScaledContents(true);

    QPixmap clsUserHeadPixmap;
    clsUserHeadPixmap.load(":/res/ico/TablerBrandUnity.png");
    clsUserHeadPixmap =
        clsUserHeadPixmap.scaled(pUserHeadLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pUserHeadLabel->setPixmap(clsUserHeadPixmap);

    // 内容区
    this->m_pAccountLineEdit = new LineEditComponent(":/res/ico/MingcuteUser2Fill.png", "输入账户", this);
    this->m_pPasswordLineEdit = new PasswordComponent(":/res/ico/MajesticonsLock.png", this);
    this->m_pLoginButton = new ButtonComponent("登 录", this);
    this->m_pLoginButton->installEventFilter(this);

    QPalette pale;
    pale.setColor(QPalette::WindowText, QColor(45, 119, 229));
    this->m_pRegisterButton = new QLabel("注册账号", this);
    this->m_pRegisterButton->setPalette(pale);
    this->m_pRegisterButton->adjustSize();
    this->m_pRegisterButton->setCursor(Qt::PointingHandCursor);
    this->m_pRegisterButton->installEventFilter(this);

    // 添加内容到布局
    m_pContentVBoxLayout = new QVBoxLayout();
    m_pContentVBoxLayout->setContentsMargins(15, 11, 15, 11);
    m_pContentVBoxLayout->addWidget(this->m_pAccountLineEdit);
    m_pContentVBoxLayout->addSpacing(10);
    m_pContentVBoxLayout->addWidget(this->m_pPasswordLineEdit);
    m_pContentVBoxLayout->addSpacing(20);
    m_pContentVBoxLayout->addWidget(this->m_pLoginButton);
    m_pContentVBoxLayout->addSpacing(20);
    m_pContentVBoxLayout->addWidget(this->m_pRegisterButton, 0, Qt::AlignCenter);

    // 添加到界面
    m_pMainVBoxLayout->addWidget(m_pNormalTitleBar);
    m_pMainVBoxLayout->addSpacing(20);
    m_pMainVBoxLayout->addWidget(pUserHeadLabel, 0, Qt::AlignCenter);
    m_pMainVBoxLayout->addSpacing(20);
    m_pMainVBoxLayout->addLayout(m_pContentVBoxLayout);
    m_pMainVBoxLayout->addStretch();

    InitSignalSlot();
}

void BaseLoginDialog::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QLinearGradient gradient(QPoint(this->rect().topLeft()), QPoint(this->rect().bottomLeft()));
    gradient.setColorAt(0, QColor(204, 244, 254));
    gradient.setColorAt(1, Qt::white);
    painter.setBrush(gradient);
    painter.drawRect(this->rect());
    QWidget::paintEvent(event);
}

void BaseLoginDialog::InitSignalSlot()
{
    connect(m_pNormalTitleBar, &NormalTitleBar::CloseWindowSignal, this, [&]() {
        this->close();
    });
}
