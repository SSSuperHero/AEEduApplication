#ifndef MESGBOXWIDHGET_H
#define MESGBOXWIDHGET_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "utility/widget/basemainwidget.h"
#include "utility/widget/clicklabel.h"

enum ECHO_MESSAGEBOX_RETURN
{
    ECHO_MESSAGEBOX_CANCLE = 0,
    ECHO_MESSAGEBOX_OK,
    ECHO_MESSAGEBOX_SAVE,

    ECHO_MESSAGEBOX_DOWNLOAD,
    ECHO_MESSAGEBOX_OTHER
};

class EchoMessageBox : public QWidget
{
    Q_OBJECT
public:
    static ECHO_MESSAGEBOX_RETURN information(QWidget *parent, const QString &title,
                                              const QString &text, const QString OkText,
                                              const QString cancleText, const bool cancleFlag = true );
    static ECHO_MESSAGEBOX_RETURN bellGoldInfo(QWidget *parent, const QString &title,
                                               const QString _bellGoldNum, const QString _RMBNum,
                                               const QString _curBellGoldNum, const QString creationInfo,
                                               const QString OkText, const QString cancleText,
                                               const bool cancleFlag = false);
    static ECHO_MESSAGEBOX_RETURN bellMakeInfo(QWidget *parent, const QString &title, const QString OkText, const QString cancleText, const bool cancleFlag);
    static ECHO_MESSAGEBOX_RETURN bellInstructions(QWidget *parent, const QString &title, const QString OkText, const QString cancleText, const bool cancleFlag);
};

class MesgBoxWidhget : public BaseMainWidget
{
    Q_OBJECT
public:
    explicit MesgBoxWidhget(QWidget *parent = 0);
    ~MesgBoxWidhget(){
        delete m_close;
        delete m_title;
        delete m_info;
        delete m_ok;
        delete m_cancle;
    }
public slots:
    void closeBox();
    void ok_clicked();
    void cancle_clicked();
    void downlad_clicked();
    void manage_clicked();
public:
    void set_title(QString);
    void set_info(QString);
    void set_bellDownLoadInfo( const QString, const QString, const QString, const QString );
    void set_bellMakeInfo();
    void set_ok_cancle(bool);
    void set_ok_text(QString str);
    void set_cancle_text(QString str);
    ECHO_MESSAGEBOX_RETURN returnClickFlag();
    void showBellInstructions();
private:
    void intUI();
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

signals:
    void signal_clickButton( bool );

protected slots:
    void slot_clickBellInstructions();
private:
    QPixmap             m_p;
    QPushButton*        m_close;
    QLabel*             m_title;
    QLabel*             m_info;
    QPushButton*        m_ok;
    QPushButton*        m_cancle;

    QPushButton*        m_bellDownload;
    QPushButton*        m_bellManage;
    QPushButton*        m_bellClose;

    ClickedLabel*       m_goldPic1;
    ClickedLabel*       m_goldPic2;
    QLabel*             m_bellText;
    QLabel*             m_curBellText;
    QLabel*             m_bellGoldNum;
    QLabel*             m_curBellGoldNum;
    QLabel*             m_RMBNum;
    QLabel*             m_creationInfo;

    ECHO_MESSAGEBOX_RETURN      m_clickButtonFlag;
};

#endif // MESGBOXWIDHGET_H
