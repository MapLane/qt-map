#ifndef QT_MAP_LOCATIONSOCKET_H
#define QT_MAP_LOCATIONSOCKET_H

#include <QObject>
#include <QWebSocket>

class LocationSocket : public QObject {
    Q_OBJECT
public:
    explicit LocationSocket(const QUrl &url, QObject *parent = Q_NULLPTR);
signals:
    void closed();
    void locationUpdated(double *pos);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

public slots:
    void mapInitialized();

private:
    QWebSocket m_webSocket;
    QUrl m_url;
};


#endif //QT_MAP_LOCATIONSOCKET_H
