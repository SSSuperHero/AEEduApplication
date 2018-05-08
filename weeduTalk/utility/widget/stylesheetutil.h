#ifndef STYLESHEETUTIL_H
#define STYLESHEETUTIL_H
#include <QVector>
#include <QPair>
#include <QWidget>
#include "utility/tostringutil.h"

/*
 *
QLineEdit#editMobile
{
border-top-left-radius: 6px;
border-top-right-radius: 6px;
background-color:#f5f5f5;
padding-left: 10px;
font-size: 12px;
color: #cccccc;
};
1. sectionName：QLineEdit#editMobile
2. constraints: style must be written in the format like above example
3. why don't use QMap instead of QVector?
   Because in css, background related fields has strict orders
*
*/

void widgetChangeBackgroundColor(QWidget* widget, const QString& sectionName,
                                 const QString& backgroundColor);

void widgetChangeBorderImage(QWidget* widget, const QString& sectionName,
                             const QString& imageUrl);

void widgetChangeTextColor(QWidget* widget, const QString& sectionName,
                           const QString& textColor);

struct StyleSheetSection
{
    typedef QVector<QPair<QString, QString>>  StyleVector_t;
    void reset();
    QString toString() const;
    QString toStyleSheet() const;
    StyleVector_t::iterator findField(const QString& fieldName);

    QString       sectionName;
    StyleVector_t fields;
};

typedef QVector<StyleSheetSection> StyleSheetSections_t;
QString sectionsToStyleSheet(const StyleSheetSections_t& sections);

class StyleSheetUtil
{
public:
    StyleSheetUtil();

    void changeStyle(QWidget* widget, const QString& sectionName,
                     const QString& styles);

    void changeStyle(QWidget* widget, const QString& sectionName,
                     const QString& styleName, const QString& newValue);


private:
    void parseToSections(const QString& styleSheet, StyleSheetSections_t& sections);

    void parseToSectionsImpl(const QString& line, StyleSheetSection& section, StyleSheetSections_t& sections);

    QString generateNew(const QString& styleSheet, const QString& sectionName,
                        const QString& styleName, const QString& newValue);

    QString generatePure(const QString& sectionName, const QString& styleName, const QString& newValue);


    void parseSectionName(const QString& line, StyleSheetSection& section);
    void parseField(const QString& line, StyleSheetSection& section, StyleSheetSections_t &sections);

    void onParseSectionFinished(StyleSheetSections_t &sections, StyleSheetSection &section);

    void generateNewImpl(StyleSheetSections_t& sections, const QString& sectionName,
                         const QString& styleName, const QString& newValue);

    void addNewSection(StyleSheetSections_t& sections, const QString& sectionName,
                         const QString& styleName, const QString& newValue);

    StyleSheetSections_t::iterator findSection(StyleSheetSections_t& sections, const QString& sectionName);
private:
    enum ParseStatus {STATUS_SECTION, STATUS_LEFT_BRACKET, STATUS_FIELD, STATUS_RIGHT_BRACKET};
    ParseStatus parseStatus;

};

#endif // STYLESHEETUTIL_H
