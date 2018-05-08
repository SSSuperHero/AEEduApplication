#include "languageinternationalization.h"
#include <QTranslator>
#include <QApplication>

EchoLanguage::EchoLanguage()
{

}

void EchoLanguage::initLanguage()
{
    static QTranslator translator;

    if(translator.load(QString(":/languages/change_language_CN.qm")))
    {
        qApp->installTranslator(&translator);
    }
}
