#include "bridge.h"
#include <QMessageBox>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJSEngine>
#include <QDebug>

Bridge* Bridge::instance()
{
    static Bridge s_obj;
    return &s_obj;
}

Bridge::Bridge()
{

}

void Bridge::init()
{

}

void Bridge::sendMessage( QString msg )
{
    parseJson( msg.toLatin1() );
//    QMessageBox::aboutQt(0, tr("Qt"));
    qDebug()<<"Bridge showMsgBox:"<<msg;
}

void Bridge::parseJson(const QByteArray &data)
{
    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(data, &jsonError);
    if(jsonError.error == QJsonParseError::NoError){
        if(json.isObject())
        {
            QJsonObject obj = json.object();
            QString name;
            QJsonObject param;
            if(obj.contains("name"))
            {
                if(obj["name"].isString())
                {
                    name = obj["name"].toString();
//                    qDebug()<<"name:"<<name;
                }
            }
            if(obj.contains("param"))
            {
                if(obj["param"].isObject())
                {
                    param = obj["param"].toObject();
//                    qDebug()<<"param id:"<<param["id"].toInt();
                }
            }

            if( !name.isEmpty() )
            {
                WidgetManager::instance()->addWebMediaMsg( name, param );
                WidgetManager::instance()->do_cmd();
            }
        }
    }
}

void Bridge::slot_sendMessageToWeb(const MUESIC_PLAY_STATUS _playType, const int _id)
{

    QString _statesStr;
    if( _playType == MUESIC_PLAYING_START )
        _statesStr = "play";
    else
        _statesStr = "pause";

    // 构建 JSON 对象
    QJsonObject json;
    json.insert("states", _statesStr);
    json.insert("id", _id);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

//    qDebug()<<"slot_sendMessageToWeb strJson:"<<strJson;
    emit sendMessageToWeb( strJson );
}
