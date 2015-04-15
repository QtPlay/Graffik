#include <QApplication>
#include <QQmlApplicationEngine>
#include "mainWindow.h"
#include "filter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    filter *eventFilter = new filter;
    app.installEventFilter(eventFilter);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    QObject *root = engine.rootObjects().at(0);

    mainWindow mw(root);

    QObject::connect(eventFilter, SIGNAL(mousePressed(QVariant,QVariant,QVariant)), root, SLOT(mousePressed(QVariant,QVariant,QVariant)));
    QObject::connect(eventFilter, SIGNAL(mouseReleased(QVariant,QVariant,QVariant)), root, SLOT(mouseReleased(QVariant,QVariant,QVariant)));

    return app.exec();
}