#pragma once

#include <QWidget>

class ImageContainer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageContainer(const QString& strFilePath, QWidget* parent = nullptr);

signals:
};
