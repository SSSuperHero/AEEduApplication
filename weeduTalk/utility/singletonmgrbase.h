#ifndef SINGLETONMGRBASE_H
#define SINGLETONMGRBASE_H
#include <QObject>
#include "mybasesingleton.h"

#include "utility/singleton.h"

class SingletonMgrBase: public QObject
{
    Q_OBJECT

    virtual void init() = 0;

protected:
    SingletonMgrBase() {}


};

#endif // SINGLETONMGRBASE_H
