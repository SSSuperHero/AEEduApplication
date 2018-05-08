#ifndef HASHUTILITY_H
#define HASHUTILITY_H

#include <QString>



class HashUtility
{
public:
    HashUtility();

    static QString toMd5(const QString& message);
    static QString fileToMd5(const QString& filePath);

};

#endif // HASHUTILITY_H
