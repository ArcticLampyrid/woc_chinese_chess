#include "network.h"
#include "board.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Network::Network() {
    readSettings();
    connect(&manager, &QNetworkAccessManager::finished, this, &Network::onResponse);
}

void Network::readSettings() {
    QFile file(SETTING_FILENAME);
    if (!file.exists() || !file.open(QFile::OpenModeFlag::ReadOnly))
        throw Exception("Data is broken!", 1);
    QJsonParseError parser;
    QJsonDocument data = QJsonDocument::fromJson(file.readAll(), &parser);
    if (parser.error != QJsonParseError::NoError || data.isEmpty() || !data.isObject())
        throw Exception("Data is broken!", 1);
    auto json_object = data.object();
    QString host;
    if (json_object.contains("timeout"))
        timeout = json_object["timeout"].toInt();
    else
        throw Exception("Data is broken!", 1);
    if (json_object.contains("host"))
        host = json_object["host"].toString();
    else
        throw Exception("Data is broken!", 1);
    unsigned count = 0;
    for (const auto& i : json_object.keys()) {
        auto key = str2enum(i);
        if (key != RequestType::UNEXPECTED) {
            url[(int)key] = host + json_object[i].toString();
            count++;
        }
    }
    if (count != 6)
        throw Exception("Data is broken!", 1);
}

void Network::onMove(const std::pair<int, int> from, const std::pair<int, int> to) {
    send(setRequest(RequestType::MOVE, QString("?X1=%1&Y1=%2&X2=%3&Y2=%4").arg(from.first).arg(from.second).arg(to.first).arg(to.second)));
}

void Network::onResponse(QNetworkReply* reply) {
    unsigned count = 0;
    timer.stop();
    try {
        auto code = reply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt();
        if (code / 100 != 2)    //2xx表示服务器正常响应
            error();
        auto data = reply->readAll();
        QJsonParseError parser;
        auto json = QJsonDocument::fromJson(data, &parser);
        if (parser.error != QJsonParseError::NoError || json.isEmpty() || !json.isObject())
            error();
        auto json_object = json.object();
        if (!json_object.contains("Type"))
            error();
        auto type = str2enum(json_object["Type"].toString());        
        if (!json_object["Success"].toBool()) {
            emit failure(json_object["ErrMessage"].toString());
            if (type == RequestType::FIND)
                findOpp(true);
        }
        else switch(type) {
        case RequestType::UNEXPECTED:error();
        case RequestType::CONTINUE:break;
        case RequestType::FIND:
            if (json_object.contains("Side") && json_object["Side"].isBool() && json_object.contains("Opp")) {
                Board::getBoard()->SIDE = json_object["Side"].toBool();
                emit findOK(json_object["Opp"].toString());
            } else
                error();
            break;
        case RequestType::LOGIN:
            emit loginOK();
            break;
        case RequestType::SIGNUP:
            emit signupOK();
            break;
        //聊天功能
        //case RequestType::MESSAGE:{

        //}break;
        case RequestType::MOVE:
            int x1, y1, x2, y2;
            try {
                x1 = json_object["X1"].toInt();
                y1 = json_object["Y1"].toInt();
                x2 = json_object["X2"].toInt();
                y2 = json_object["Y2"].toInt();
            } catch (...) {
                error();
            }
            emit move(Pos(x1, y1), Pos(x2, y2));
            break;
        }
        ////////////////////////
        if (code == 201)    //长轮询
            send(setRequest(RequestType::CONTINUE, QString("?time=%1").arg(count++)));
    } catch (Exception e) {
        e.process();
    }
}
