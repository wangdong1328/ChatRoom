#include "lineeditcomponent.h"

#include <QHBoxLayout>
#include <QPainter>

LineEditComponent::LineEditComponent(const QString& strIconPath, const QString& setPlaceholderText,
                                     QWidget* parent) :
    QWidget { parent }
{
    // 设置行高
    this->setFixedHeight(40);

    m_pMainHBoxLayout = new QHBoxLayout(this);
    m_pMainHBoxLayout->setContentsMargins(11, 0, 9, 0);

    // 创建输入框图标
    this->m_pLeftIcon = new QLabel(this);
    this->m_pLeftIcon->setPixmap(QPixmap(strIconPath));
    this->m_pLeftIcon->setFixedSize(19, 19);
    this->m_pLeftIcon->setScaledContents(true);

    // 创建输入框内容
    QFont font;
    font.setPixelSize(13);
    QStringList qsslist;
    qsslist.append("QLineEdit:Hover { background-color:transparent }");
    qsslist.append("QLineEdit { background-color:transparent }");

    this->m_pLineEdit = new QLineEdit(this);
    this->m_pLineEdit->setFont(font);
    this->m_pLineEdit->setStyleSheet(qsslist.join(""));
    this->m_pLineEdit->setFrame(QFrame::NoFrame);
    this->m_pLineEdit->setAlignment(Qt::AlignLeft);
    this->m_pLineEdit->setMaxLength(20);
    this->m_pLineEdit->setFocusPolicy(Qt::ClickFocus);
    this->m_pLineEdit->setPlaceholderText(setPlaceholderText);

    m_pMainHBoxLayout->addWidget(this->m_pLeftIcon);
    m_pMainHBoxLayout->addWidget(this->m_pLineEdit);

    this->setLayout(m_pMainHBoxLayout);
}

QString LineEditComponent::GetText() const
{
    return m_pLineEdit ? m_pLineEdit->text() : "";
}

void LineEditComponent::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(218, 221, 224));
    painter.drawRoundedRect(this->rect(), 10, 10);
}
