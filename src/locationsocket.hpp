//
// Created by 王思远 on 2018/3/16.
//

#ifndef QT_MAP_LOCATIONSOCKET_H
#define QT_MAP_LOCATIONSOCKET_H

#include <QObject>
#include <QWebSocket>

class Locationsocket : public QObject {
    Q_OBJECT
public:
    explicit Locationsocket(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);
signals:
    void closed();

private solts:


};


#endif //QT_MAP_LOCATIONSOCKET_H
