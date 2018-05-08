#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H
#include <QLabel>
#include <QPixmap>

class ImageUtil
{
public:
    ImageUtil();
    //change the label name
    static bool setBackgroundImage(QWidget* label, const QString& styleSheetSectionName,
                                   const QString& imageFilePath,
                                   bool bBackgroundImage);
    static QPixmap centerCrop(const QPixmap& pixmap, int destW, int destH);
    static QString croppedImageFilePath(const QString& imageFilePath, int crop_width, int crop_height);
};

#endif // IMAGEUTIL_H
