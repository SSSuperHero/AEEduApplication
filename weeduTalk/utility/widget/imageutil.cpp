#include "imageutil.h"
#include <QDebug>
#include <QFile>
#include <utility/widget/stylesheetutil.h>

ImageUtil::ImageUtil()
{

}

bool ImageUtil::setBackgroundImage(QWidget* label, const QString& styleSheetSectionName, const QString &imageFilePath, bool bBackgroundImage)
{
    qInfo("styleSheetSectionName:%s, imageFilePath:%s", qUtf8Printable(styleSheetSectionName), qUtf8Printable(imageFilePath));

    if (!label)
    {
        qCritical("label is null");
        return false;
    }

    qDebug()<<"setBackgroundImage label:"<<label->width()<<label->height();

    if (styleSheetSectionName.isEmpty())
    {
        qCritical("styleSheetSectionName is empty");
        return false;
    }

    QString filePath = imageFilePath;
//    if( imageFilePath.indexOf(":") != 0 )
//    {
//        QPixmap pixmap;
//        bool ret = pixmap.load(imageFilePath);
//        if (!ret)
//        {
//            qCritical("load imageFilePath:%s failed", qUtf8Printable(imageFilePath));
//            return false;
//        }

//        const QRect rcLabel = label->geometry();
//        QPixmap finalP = centerCrop(pixmap, rcLabel.width(), rcLabel.height());

//        filePath = croppedImageFilePath(imageFilePath, rcLabel.width(), rcLabel.height());
//        qInfo("cropped image file path:%s", qUtf8Printable(filePath));

//        if (!QFile::exists(filePath))
//        {
//            qInfo("file not exits");
//            QFile file(filePath);
//            if (!file.open(QIODevice::WriteOnly))
//            {
//                qCritical("file open failed");
//                return false;
//            }

//            if (!finalP.save(&file, "PNG"))
//            {
//                qCritical("save filePath failed");
//                return false;
//            }
//        }
//        else
//        {
//            qInfo("file exists");
//        }
//    }
//    else
//    {
//        filePath = imageFilePath;
//    }

    StyleSheetUtil styleUtil;
    if(bBackgroundImage)
    {
        styleUtil.changeStyle(label, styleSheetSectionName, QString("background-image: url(%1);").arg(filePath));
    } else {
        filePath = imageFilePath;
        styleUtil.changeStyle(label, styleSheetSectionName, QString("border-image: url(%1);").arg(filePath));
    }

    return true;
}

QPixmap ImageUtil::centerCrop(const QPixmap &pixmap, int destW, int destH)
{
    qInfo("centerCrop, dest width:%d, dest height:%d", destW, destH);

    QPixmap p = pixmap.scaled(destW, destH, Qt::KeepAspectRatioByExpanding);

    int w = p.width();
    int h = p.height();
    qInfo("scaled, width:%d, height:%d", w, h);

    QRect rcCenter;
    if (w > h)
    {
        int newW = 0;
        newW = destW * h / destH;
        int diff = (w - newW) / 2;
        rcCenter = QRect(diff, 0, newW, h);
    }
    else
    {
        int newH = 0;
        newH = destH * w / destW;
        int diff = (h - newH) / 2;
        rcCenter = QRect(0, diff, w, newH);
    }

    return p.copy(rcCenter);
}

QString ImageUtil::croppedImageFilePath(const QString &imageFilePath, int crop_width, int crop_height)
{
    qInfo("croppedImageFilePath imageFilePath:%s, crop_width:%d, crop_height:%d", qUtf8Printable(imageFilePath),
          crop_width, crop_height);

    QString suffix = QString(".%1_%2").arg(crop_width).arg(crop_height);
    return imageFilePath + suffix;
}
