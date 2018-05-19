#ifndef ZLIBUTILITY_H
#define ZLIBUTILITY_H

#include <QObject>

class ZlibUtility : public QObject
{
    Q_OBJECT
public:
    explicit ZlibUtility(QObject *parent = nullptr);

    static void uncompressedFile(QString FileName, QStringList &ListPic);
signals:

public slots:
};

#endif // ZLIBUTILITY_H
