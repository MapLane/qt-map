#include "mapwindow.hpp"
#include "locationsocket.hpp"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QMapboxGLSettings settings;
    settings.setCacheDatabasePath("/tmp/mbgl-cache.db");
    settings.setCacheDatabaseMaximumSize(200 * 1024 * 1024);

    LocationSocket socket(QUrl(QString("ws://10.2.133.251:3000")));
    MapWindow window(settings, socket);

    QObject::connect(&socket, &LocationSocket::locationUpdated, &window, &MapWindow::mapUpdated);
    QObject::connect(&window, &MapWindow::mapReady, &socket, &LocationSocket::mapInitialized);

    window.resize(800, 600);
    window.show();

    if (argc == 2 && QString("--test") == argv[1]) {
        window.selfTest();
    }

    return app.exec();
}