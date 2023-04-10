#include <QtGui>
#include <QtQml>
#include <QtWidgets>

#include "MainWindow.h"
#include "WindowFramelessHelper.h"

int main(int argc, char *argv[])
{
    // QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    qmlRegisterType<WindowFramelessHelper>("QtShark.Window", 1, 0, "FramelessHelper");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    MainWindow w;
    w.show();

    return a.exec();
}
