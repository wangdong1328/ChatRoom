
#include <QApplication>
#include <QFontDatabase>
#include "graphicmanager.h"

void SetFont(QApplication& app)
{
    const int iFontID = QFontDatabase::addApplicationFont(":/res/font/flache.ttf");
    const QString family = QFontDatabase::applicationFontFamilies(iFontID).at(0);

    QFont font;
    font.setHintingPreference(QFont::PreferNoHinting);
    font.setFamily(family);
    font.setPointSize(12);
    app.setFont(font);
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // 设置窗口字体
    SetFont(a);

    GraphicManager::GetInstance().Init();

    return a.exec();
}
