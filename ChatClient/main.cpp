
#include <QApplication>
#include "graphicmanager.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    GraphicManager::GetInstance().Init();

    return a.exec();
}
