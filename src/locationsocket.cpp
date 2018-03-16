#include "locationsocket.hpp"
#include <iostream>

std::vector<std::string> SplitString(const std::string& s, const std::string& c) {
    std::vector<std::string> result;
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2) {
        result.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length()) {
        result.push_back(s.substr(pos1));
    }
    return result;
}

LocationSocket::LocationSocket(const QUrl &url, QObject *parent) :
        QObject(parent),
        m_url(url)
{
    connect(&m_webSocket, &QWebSocket::connected, this, &LocationSocket::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &LocationSocket::closed);
}

void LocationSocket::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &LocationSocket::onTextMessageReceived);
    std::cout << "websocket connected" << std::endl;
}

void LocationSocket::onTextMessageReceived(QString message)
{
//    qDebug() << message;
    std::vector<std::string> positions = SplitString(message.toStdString(), ",");
    double mapPos[3];
    for (int i = 0; i < positions.size(); i++) {
        mapPos[i] = std::stod(positions[i]);
    }
    qDebug() << "lat:" << mapPos[0] << ", lon:" << mapPos[1] << ", euler:" << mapPos[2];

    emit this->locationUpdated(mapPos);
}

void LocationSocket::mapInitialized()
{
    m_webSocket.open(m_url);
}