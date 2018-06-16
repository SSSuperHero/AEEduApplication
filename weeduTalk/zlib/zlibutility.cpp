#include "zlibutility.h"
#include "zlib.h"
#include "zlib/unzip.h"
#include "zconf.h"
#include <QDir>
#include <QDebug>

#define FILE_ATTRIBUTE_DIRECTORY            0x00000010
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020


ZlibUtility::ZlibUtility(QObject *parent) : QObject(parent)
{

}

void ZlibUtility::uncompressedFile( QString FileName ,QStringList & ListPic )
{
    /**新建一个文件夹,用来保存解压后的文件*/
    QString UnpressPath = FileName.remove( ".zip" );
    QDir dir;
    dir.mkpath( UnpressPath );

    unz_file_info64     FileInfo;
    /**打开zip文件,这里记得一定要加上".zip",因为在上面的时候已经将".zip"移出去了。*/
    unzFile zFile = unzOpen64( ( FileName + ".zip" ).toStdString().c_str() );
    unz_global_info64 gi;
    /**获取文件数量*/
    if ( unzGetGlobalInfo64( zFile, &gi ) == UNZ_OK )
    {
        int result;

        for ( int i = 0; i < gi.number_entry; ++i )
        {
            char file[256]  = { 0 };
            char ext[256]   = { 0 };
            char com[1024]  = { 0 };
            if ( unzGetCurrentFileInfo64( zFile, &FileInfo, file, sizeof(file), ext, 256, com, 1024 ) != UNZ_OK )
            {
                return;
            }

            QString _fileDir = file;
            QString _mkDirPath = "";
            while (_fileDir.indexOf("/") > -1)
            {
                QString _dirPath = _fileDir.left(_fileDir.indexOf("/"));

                _mkDirPath += _dirPath;
                QDir _secdir;
                _secdir.mkpath( UnpressPath + "/" + _mkDirPath );

                _fileDir = _fileDir.mid( _fileDir.indexOf("/") + 1 );
                qDebug()<<"uncompressedFile _fileDir:"<<_fileDir;
            }

            if( !( FileInfo.external_fa & FILE_ATTRIBUTE_DIRECTORY ) ) //文件，否则为目录
            {
                result=unzOpenCurrentFile(zFile);//无密码
                result=unzOpenCurrentFilePassword(zFile,"szPassword");//有密码
            }

            char data[1024] = { 0 };
            int size;
            /**将路径写到list中*/
            QString path = UnpressPath + QString ("/") + file;
            ListPic << path;
            QFile File( path );
            File.open( QFile::WriteOnly );
            /**打开新文件并将数据写进去*/
            while(true)
            {
                size= unzReadCurrentFile(zFile,data,sizeof(data));
                if(size <= 0) { break; }
                File.write(data, size);
            }
            File.close();
            unzCloseCurrentFile(zFile);
            if( i < gi.number_entry - 1 && unzGoToNextFile( zFile ) != UNZ_OK ) { return; }
        }
        unzClose(zFile);
    }
    else { return; }
}
