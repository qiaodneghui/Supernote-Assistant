#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include "check.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Assistant_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    Check check;
    engine.rootContext()->setContextProperty("check",&check);

    const QUrl url(u"qrc:/Assistant/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

//    const string filePath="C:\\Users\\work\\Desktop\\test\\bb.note";
//    const string exportPath="C:\\Users\\work\\Desktop\\test\\a.docx";
//    Test test;
//    test.run(filePath);
//    test.exportDocx("123",exportPath);
//    test.exportDocx("456",exportPath);

    return app.exec();
}
