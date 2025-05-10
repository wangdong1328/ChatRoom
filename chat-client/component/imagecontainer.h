#pragma once

#include <QWidget>

class ImageContainer final : public QWidget
{
    Q_OBJECT
public:
    explicit ImageContainer(const QString& strFilePath, QWidget* parent = nullptr);

signals:
};
