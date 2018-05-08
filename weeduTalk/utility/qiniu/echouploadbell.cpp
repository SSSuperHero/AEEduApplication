#include "echouploadbell.h"
#include "qiniu/include/qiniu/rs.h"
#include "qiniu/include/qiniu/io.h"
#include "qiniu/include/qiniu/resumable_io.h"
#include "widget/assistWidget/echobellmodule.h"
#include "utility/widget/mesgboxwidhget.h"
#include <QFile>

#define QINIU_ACCESSKEY         "AK:HIxVX64Pn2KxqWT5onR_lUopOJcFcQ2rQid1WpUf"
#define QINIU_SECRETKEY         "SK:AFjHIyHiVnWFwjvypPKJeFrGTxf_IebSd18kb9Lz"
#define QINIU_BUCKET            "ocnurs87t.bkt.clouddn.com"

//#pragma execution_character_set("utf-8")

EchoUploadBell::EchoUploadBell(QObject *parent) :
QThread(parent)
{

}


void EchoUploadBell::getQiniuToken()
{

}

void EchoUploadBell::run()
{
    Qiniu_Global_Init(-1);
    Qiniu_Mac mac;
    mac.accessKey = QINIU_ACCESSKEY;
    mac.secretKey = QINIU_SECRETKEY;
    const char *bucket = QINIU_BUCKET;
    const char *key = m_uploadKey.toLatin1().data();

    QByteArray localFileByte = m_uploadFile.toLatin1();
    const char *localFile = localFileByte.data();

    Qiniu_Io_PutRet putRet;
    Qiniu_Client client;
    Qiniu_RS_PutPolicy putPolicy;
    Qiniu_Io_PutExtra putExtra;
    Qiniu_Zero(putPolicy);
    Qiniu_Zero(putExtra);
    putPolicy.scope = bucket;
    putPolicy.expires = 7200; //单位秒
    const char *uptoken = m_uploadToken.toLatin1().data();
//    char *uptoken = Qiniu_RS_PutPolicy_Token(&putPolicy, &mac);

    Qiniu_Use_Zone_Huadong(Qiniu_True);

    Qiniu_Client_InitMacAuth(&client, 1024, &mac);
    Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uptoken, key, localFile, &putExtra);
    if (error.code != 200)
    {
        qDebug("upload file %s:%s error.\n", bucket, key);
        qDebug("error.code:%d msg:%s\n", error.code,error.message);
    }
    else
    {
      /*200, 正确返回了, 你可以通过statRet变量查询一些关于这个文件的信息*/
        qDebug("upload file %s:%s success.\n\n", bucket, key);
        qDebug("key:\t%s\n",putRet.key);
        qDebug("hash:\t%s\n", putRet.hash);

        emit signal_uploadBellFinish( QString(putRet.key) );
    }
//    Qiniu_Free(uptoken);
    Qiniu_Client_Cleanup(&client);
}

void EchoUploadBell::setUplodeInfo( const QString _key, const QString _localFile,
                                    const QString _token )
{
    m_uploadKey = _key;
    m_uploadFile = _localFile;
    m_uploadToken = _token;
}

void EchoUploadBell::uplodeQiniu( QObject *_uplodeOwner, const QString _key,
                                  const QString _localFile, const QString _token )
{
    EchoUploadBell *_echoUplodeQiniu = new EchoUploadBell( _uplodeOwner );
    _echoUplodeQiniu->setUplodeInfo( _key, _localFile, _token );
    qDebug()<<"_localFile:"<<_localFile<<"_token:"<<_token;
    connect( _echoUplodeQiniu, &EchoUploadBell::signal_uploadBellFinish,
             (EchoBellModule*)_uplodeOwner, &EchoBellModule::slot_uploadBellFinish);
    connect(_echoUplodeQiniu, SIGNAL(finished()), _echoUplodeQiniu, SLOT(deleteLater()));
    _echoUplodeQiniu->start();
}
