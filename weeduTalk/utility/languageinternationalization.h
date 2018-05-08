#ifndef LANGUAGEINTERNATIONALIZATION_H
#define LANGUAGEINTERNATIONALIZATION_H

#include <QObject>
//#include <utility/singletonmgrbase.h>

class EchoLanguage : public QObject
{
    Q_OBJECT

//    DECLARE_SINGLETON(LanguageInternationalization)
public:
    EchoLanguage();
public:
    static void initLanguage();

signals:

public slots:
};

#endif // LANGUAGEINTERNATIONALIZATION_H
