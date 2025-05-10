#include "normaltitlebar.h"

#include <QCoreApplication>
#include <QHBoxLayout>
#include <QMessageBox>

NormalTitleBar::NormalTitleBar(QWidget* parent, bool bIsDialog /*= false*/) :
    QWidget(parent),
    m_pParentWidget(parent),
    m_bIsDialog(bIsDialog)
{
    QHBoxLayout* pMainLayout = new QHBoxLayout(this);
    pMainLayout->setContentsMargins(0, 9, 0, 9);
    pMainLayout->addStretch();

    // 关闭按钮设置
    this->m_pCloseWindowLabel = new QLabel(this);
    this->m_pCloseWindowLabel->setCursor(Qt::PointingHandCursor);
    this->m_pCloseWindowLabel->setFixedSize(25, 25);
    this->m_pCloseWindowLabel->setScaledContents(true);
    this->m_pCloseWindowLabel->setToolTip("关闭");

    QPixmap pixmap;
    pixmap.load(":/res/ico/IconamoonClose.png");
    this->m_pCloseWindowLabel->setPixmap(pixmap);
    this->m_pCloseWindowLabel->installEventFilter(this);

    if (!m_bIsDialog)
    {
        // 最小按钮设置
        this->m_pMinWindowLabel = new QLabel(this);
        this->m_pMinWindowLabel->setCursor(Qt::PointingHandCursor);
        this->m_pMinWindowLabel->setFixedSize(20, 20);
        this->m_pMinWindowLabel->setScaledContents(true);
        pixmap.load(":/res/ico/MingcuteMinimizeLine.png");
        this->m_pMinWindowLabel->setPixmap(pixmap);
        this->m_pMinWindowLabel->installEventFilter(this);
        this->m_pMinWindowLabel->setToolTip("最小化");

        // 最大按钮设置
        this->m_pMaxWindowLabel = new QLabel(this);
        this->m_pMaxWindowLabel->setCursor(Qt::PointingHandCursor);
        this->m_pMaxWindowLabel->setFixedSize(23, 23);
        this->m_pMaxWindowLabel->setScaledContents(true);
        pixmap.load(":/res/ico/FluentMaximize16Regular.png");
        this->m_pMaxWindowLabel->setPixmap(pixmap);
        this->m_pMaxWindowLabel->installEventFilter(this);
        this->m_pMaxWindowLabel->setToolTip("最大化");

        pMainLayout->addWidget(m_pMinWindowLabel);
        pMainLayout->addSpacing(3);

        pMainLayout->addWidget(m_pMaxWindowLabel);
        pMainLayout->addSpacing(3);
    }

    pMainLayout->addWidget(m_pCloseWindowLabel);

    this->setLayout(pMainLayout);
}

bool NormalTitleBar::eventFilter(QObject* watched, QEvent* event)
{
    if (QEvent::MouseButtonPress == event->type())
    {
        if (this->m_pMinWindowLabel == watched)
        {
            if (!m_pParentWidget->isMinimized())
            {
                m_pParentWidget->showMinimized();
            }
        }
        else if (this->m_pMaxWindowLabel == watched)
        {
            if (!m_pParentWidget->isMaximized())
            {
                m_pParentWidget->showMaximized();
            }
            else
            {
                m_pParentWidget->showNormal();
            }
        }
        else if (this->m_pCloseWindowLabel == watched)
        {
            if (m_bIsDialog || (QMessageBox::Yes == QMessageBox::information(
                                                        this, QString("关闭窗口"), QString("是否关闭窗口？"),
                                                        QMessageBox::No | QMessageBox::Yes, QMessageBox::No)))
            {
                QCoreApplication::exit();
            }
        }

        return true;
    }

    if (QEvent::Enter == event->type())
    {
        // 鼠标进入
        if (this->m_pMinWindowLabel == watched)
        {
            this->m_pMinWindowLabel->setAutoFillBackground(true);
            QPalette palette = this->m_pMinWindowLabel->palette();
            palette.setColor(this->m_pMinWindowLabel->backgroundRole(), Qt::gray);
            this->m_pMinWindowLabel->setPalette(palette);
        }
        else if (this->m_pMaxWindowLabel == watched)
        {
            this->m_pMaxWindowLabel->setAutoFillBackground(true);
            QPalette palette = this->m_pMaxWindowLabel->palette();
            palette.setColor(this->m_pMaxWindowLabel->backgroundRole(), Qt::gray);
            this->m_pMaxWindowLabel->setPalette(palette);
        }
        else if (this->m_pCloseWindowLabel == watched)
        {
            this->m_pCloseWindowLabel->setAutoFillBackground(true);
            QPalette palette = this->m_pCloseWindowLabel->palette();
            palette.setColor(this->m_pCloseWindowLabel->backgroundRole(), Qt::red);
            this->m_pCloseWindowLabel->setPalette(palette);
        }
    }
    else if (QEvent::Leave == event->type())
    {
        // 鼠标离开
        if (this->m_pMinWindowLabel == watched)
        {
            QPalette palette = this->m_pMinWindowLabel->palette();
            palette.setColor(this->m_pMinWindowLabel->backgroundRole(), Qt::white);
            this->m_pMinWindowLabel->setPalette(palette);
            this->m_pMinWindowLabel->setAutoFillBackground(false);
        }
        else if (this->m_pMaxWindowLabel == watched)
        {
            QPalette palette = this->m_pMaxWindowLabel->palette();
            palette.setColor(this->m_pMaxWindowLabel->backgroundRole(), Qt::white);
            this->m_pMaxWindowLabel->setPalette(palette);
            this->m_pMaxWindowLabel->setAutoFillBackground(false);
        }
        else if (this->m_pCloseWindowLabel == watched)
        {
            QPalette palette = this->m_pCloseWindowLabel->palette();
            palette.setColor(this->m_pCloseWindowLabel->backgroundRole(), Qt::white);
            this->m_pCloseWindowLabel->setPalette(palette);
            this->m_pCloseWindowLabel->setAutoFillBackground(false);
        }
    }

    return QWidget::eventFilter(watched, event);
}
