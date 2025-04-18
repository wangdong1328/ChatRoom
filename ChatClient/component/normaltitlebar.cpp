#include "normaltitlebar.h"

#include <QHBoxLayout>

NormalTitleBar::NormalTitleBar(const QString& strTitleText, QWidget* parent)
{
    QHBoxLayout* pMainLayout = new QHBoxLayout(this);
    pMainLayout->setContentsMargins(0, 9, 9, 9);

    // 标题栏设置
    QFont font;
    font.setPixelSize(14);
    font.setBold(true);
    this->m_pTitleLabel = new QLabel(strTitleText, this);
    this->m_pTitleLabel->setFont(font);
    this->m_pTitleLabel->adjustSize();

    // 关闭按钮设置
    this->m_pCloseLabel = new QLabel(this);
    this->m_pCloseLabel->setCursor(Qt::PointingHandCursor);
    this->m_pCloseLabel->setFixedSize(25, 25);
    this->m_pCloseLabel->setScaledContents(true);
    QPixmap pixmap(":/res/ico/IconamoonClose.png");
    pixmap =
        pixmap.scaled(QSize(this->m_pCloseLabel->size()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->m_pCloseLabel->setPixmap(pixmap);

    pMainLayout->addWidget(m_pTitleLabel);
    pMainLayout->addStretch();
    pMainLayout->addWidget(m_pCloseLabel);

    this->setLayout(pMainLayout);

    // 关闭按钮安装事件过滤器
    this->m_pCloseLabel->installEventFilter(this);
}

bool NormalTitleBar::eventFilter(QObject* watched, QEvent* event)
{
    if ((this->m_pCloseLabel == watched) && (QEvent::MouseButtonPress == event->type()))
    {
        emit CloseWindowSignal();
        return true;
    }
    return QWidget::eventFilter(watched, event);
}
