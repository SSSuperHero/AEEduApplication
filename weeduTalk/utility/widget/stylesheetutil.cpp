#include "stylesheetutil.h"
#include <utility/stringutility.h>


void StyleSheetSection::reset()
{
    sectionName.clear();
    fields.clear();
}

QString StyleSheetSection::toString() const
{
    return QString("sectionName:%1, feilds:%2").arg(sectionName).arg(ToStringUtil::vectorToString(fields));
}

QString StyleSheetSection::toStyleSheet() const
{
    QString header = QString("%1\n{\n").arg(sectionName);
    QString footer = "}\n";
    QString ret = header;

    QPair<QString, QString> pair;
    foreach (pair, fields)
    {
        ret += QString("%1:%2;\n").arg(pair.first).arg(pair.second);
    }

    ret += footer;

    return ret;
}

StyleSheetSection::StyleVector_t::iterator StyleSheetSection::findField(const QString &fieldName)
{
    StyleVector_t::iterator b = fields.begin();
    StyleVector_t::iterator e = fields.end();
    for (;b != e; ++b)
    {
        QPair<QString, QString>& field = *b;
        if (field.first.toLower() == fieldName.toLower())
        {
            return b;
        }
    }

    return fields.end();
}

QString sectionsToStyleSheet(const StyleSheetSections_t &sections)
{
    QString ret;
    foreach (const StyleSheetSection& section, sections)
    {
        ret += section.toStyleSheet();
    }

    return ret;
}




StyleSheetUtil::StyleSheetUtil()
    : parseStatus(STATUS_SECTION)
{

}

void StyleSheetUtil::changeStyle(QWidget *widget, const QString &sectionName, const QString &rawStyles)
{
    //qInfo("rawStyles:%s", qUtf8Printable(rawStyles));

    QStringList styles = rawStyles.trimmed().split(";", QString::SkipEmptyParts);
    foreach (const QString& style, styles)
    {
        QString styleName;
        QString styleValue;
        if (!StringUtility::splitPair(style, ":", styleName, styleValue))
        {
            qCritical("wrong style:%s", qUtf8Printable(style));
            continue;
        }

        //not efficient, should change the propery in one tme not a few times
        changeStyle(widget, sectionName, styleName, styleValue);
    }
}

void StyleSheetUtil::changeStyle(QWidget *widget, const QString& sectionName,
                                 const QString &styleName, const QString &newValue)
{
    if (!widget)
    {
        qCritical("empty widget");
        return;
    }

    QString styleSheet = widget->styleSheet().trimmed();
     //qInfo("oldStyleSheet:%s", qUtf8Printable(styleSheet));
    QString newStyleSheet = generateNew(styleSheet, sectionName, styleName, newValue);
    //qInfo("newStyleSheet:%s", qUtf8Printable(newStyleSheet));

    widget->setStyleSheet(newStyleSheet);

    return;
}


QString StyleSheetUtil::generateNew(const QString& styleSheet, const QString &sectionName, const QString &styleName, const QString &newValue)
{
    if (styleSheet.isEmpty())
    {
        //qInfo("styleSheet is empty");
        return generatePure(sectionName, styleName, newValue);
    }

    StyleSheetSections_t sections;
    parseToSections(styleSheet, sections);
    //qInfo("original style sheet:%s", qUtf8Printable(ToStringUtil::vectorToString(sections)));

    generateNewImpl(sections, sectionName, styleName, newValue);

    return sectionsToStyleSheet(sections);
}

void StyleSheetUtil::generateNewImpl(StyleSheetSections_t &sections, const QString &sectionName,
                                               const QString &styleName, const QString &newValue)
{
    StyleSheetSections_t::iterator section = findSection(sections, sectionName);
    if (section == sections.end())
    {
        //qInfo("no such sectionName:%s", qUtf8Printable(sectionName));

        addNewSection(sections, sectionName, styleName, newValue);
        return;
    }

    StyleSheetSection::StyleVector_t::iterator field = section->findField(styleName);
    if (field == section->fields.end())
    {
        //qInfo("no such style name:%s, add new style", qUtf8Printable(styleName));

        section->fields.append(qMakePair(styleName, newValue));
        return;
    }

    //qInfo("find such field, change the value");
    field->second = newValue;
    return;
}

void StyleSheetUtil::addNewSection(StyleSheetSections_t &sections, const QString &sectionName, const QString &styleName, const QString &newValue)
{
    //qInfo("addNewSection");

    StyleSheetSection newSection;
    newSection.sectionName = sectionName;
    newSection.fields.append(qMakePair(styleName, newValue));

    sections.append(newSection);
}

StyleSheetSections_t::iterator StyleSheetUtil::findSection(StyleSheetSections_t &sections, const QString &sectionName)
{
    StyleSheetSections_t::iterator b = sections.begin();
    StyleSheetSections_t::iterator e = sections.end();
    for (; b != e; ++b)
    {
        const StyleSheetSection& section = *b;
        if (section.sectionName.toLower() == sectionName.toLower())
        {
            return b;
        }
    }

    return sections.end();
}


QString StyleSheetUtil::generatePure(const QString &sectionName, const QString &styleName, const QString &newValue)
{
    StyleSheetSection section;
    section.sectionName = sectionName;
    section.fields.append(qMakePair(styleName, newValue));

    return section.toStyleSheet();
}

void StyleSheetUtil::parseToSections(const QString &styleSheet, StyleSheetSections_t &sections)
{
    StyleSheetSection section;
    QStringList lines = styleSheet.split("\n", QString::SkipEmptyParts);
    foreach (const QString& rawLine, lines)
    {
        QString line = rawLine.trimmed();
        parseToSectionsImpl(line, section, sections);
    }
}

void StyleSheetUtil::parseToSectionsImpl(const QString &line, StyleSheetSection &section, StyleSheetSections_t &sections)
{
    switch (parseStatus)
    {
    case STATUS_SECTION:
        parseSectionName(line, section);
        break;
    case STATUS_LEFT_BRACKET:
        //qInfo("parse status change to STATUS_FIELD");
        parseStatus = STATUS_FIELD;
        break;
    case STATUS_FIELD:
        parseField(line, section, sections);
        break;
    default:
        break;
    }
}

void StyleSheetUtil::onParseSectionFinished(StyleSheetSections_t &sections, StyleSheetSection &section)
{
    sections.append(section);
    //qInfo("finish parsing one section:%s", qUtf8Printable(section.toString()));

    //qInfo("parse status change to STATUS_SECTION");
    parseStatus = STATUS_SECTION;
}


void StyleSheetUtil::parseField(const QString& line, StyleSheetSection& section, StyleSheetSections_t &sections)
{
    if (line == "}" || line == "};" || line == "} ;")
    {
        //qInfo("parse status change to STATUS_RIGHT_BRACKET");
        parseStatus = STATUS_RIGHT_BRACKET;
        onParseSectionFinished(sections, section);
        return;
    }

    QString keyColonValue;
    if (line.at(line.size() - 1) == ';')
    {
        keyColonValue = line.left(line.size() -1);
    } else {
        keyColonValue = line;
    }

    //qInfo("keyColonValue:%s", qUtf8Printable(keyColonValue));


    QString key;
    QString value;
    if (!StringUtility::splitPair(keyColonValue, ":", key, value))
    {
        qCritical("wrong style:%s", qUtf8Printable(keyColonValue));
        return;
    }


    //qInfo("find field.key:%s, value:%s", qUtf8Printable(key), qUtf8Printable(value));
    section.fields.append(qMakePair(key, value));
}


void StyleSheetUtil::parseSectionName(const QString& line, StyleSheetSection& section)
{
    if (line.isEmpty())
    {
        return;
    }

    section.reset();
    section.sectionName = line;

    //qInfo("sectionName:%s, parse status change to STATUS_LEFT_BRACKET", qUtf8Printable(section.sectionName));
    parseStatus = STATUS_LEFT_BRACKET;
}


void widgetChangeBackgroundColor(QWidget *widget, const QString &sectionName, const QString &backgroundColor)
{
    if (!widget)
    {
        return;
    }

    StyleSheetUtil util;
    util.changeStyle(widget, sectionName, QString("background-color:%1;").arg(backgroundColor));
}

void widgetChangeBorderImage(QWidget *widget, const QString &sectionName, const QString &imageUrl)
{
    if (!widget)
    {
        return;
    }

    StyleSheetUtil util;
    util.changeStyle(widget, sectionName, QString("border-image:%1;").arg(imageUrl));
}

void widgetChangeTextColor(QWidget *widget, const QString &sectionName, const QString &textColor)
{
    if (!widget)
    {
        return;
    }

    StyleSheetUtil util;
    util.changeStyle(widget, sectionName, QString("color:%1;").arg(textColor));
}
