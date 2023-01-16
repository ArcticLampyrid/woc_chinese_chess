#include "network.h"
#include "board.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Network::Network() {
    readSettings();
}

void Network::readSettings() {
    try {
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
        if (json_object.contains("host"))
            host = json_object["host"].toString();
        else
            throw Exception("Data is broken!", 1);
        if (json_object.contains("login"))
            url[(int)RequestType::LOGIN] = host + json_object["login"].toString();
        else
            throw Exception("Data is broken!", 1);
        if (json_object.contains("signup"))
            url[(int)RequestType::SIGNUP] = host + json_object["signup"].toString();
        else
            throw Exception("Data is broken!", 1);
        if (json_object.contains("message"))
            url[(int)RequestType::MESSAGE] = host + json_object["message"].toString();
        else
            throw Exception("Data is broken!", 1);
        if (json_object.contains("move"))
            url[(int)RequestType::MOVE] = host + json_object["move"].toString();
        else
            throw Exception("Data is broken!", 1);
        if (json_object.contains("main"))
            url[(int)RequestType::CONTINUE] = host + json_object["main"].toString();
        else
            throw Exception("Data is broken!", 1);
    } catch(Exception e) {
        e.process();
    }
}

void Network::onMove(const std::pair<int, int> from, const std::pair<int, int> to) {
    send(setRequest(RequestType::MOVE, QString("?x1=%1&y1=%2&x2=%3&y2=%4").arg(from.first).arg(from.second).arg(to.first).arg(to.second)));
}

void Network::onResponse(QNetworkReply* reply) {
    unsigned count = 0;
    timer.stop();
    try {
        auto code = reply->attribute(QNetworkRequest::Attribute::HttpStatusCodeAttribute).toInt();
        if (code / 100 != 2)    //2xx表示服务器正常响应
            error();
        oauth = reply->attribute(QNetworkRequest::AuthenticationReuseAttribute).toString();
        auto data = reply->readAll();
        QJsonParseError parser;
        auto json = QJsonDocument::fromJson(data, &parser);
        if (parser.error != QJsonParseError::NoError || json.isEmpty() || !json.isObject())
            error();
        auto json_object = json.object();
        if (!json_object.contains("Type"))
            error();
        //聊天功能
        //if (json_object.contains("Message"))
        //
        auto type = str2enum(json_object["Type"].toString());        
        if (!json_object["Sucess"].toBool()) {
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
        //Write your code below:
        ////////////////////////
        case RequestType::LOGIN:{

        }break;
        case RequestType::SIGNUP:{

        }break;
        case RequestType::MESSAGE:{

        }break;
        case RequestType::MOVE:{

        }break;
        }
        ////////////////////////
        if (code == 201)    //长轮询
            send(setRequest(RequestType::CONTINUE, QString("?time=%1").arg(count++)));
    } catch (Exception e) {
        e.process();
    }
}
