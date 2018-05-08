#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include "utility/widget/basewidget.h"

class trayMenuItem : public BaseWidget
{
    Q_OBJECT
public:
    trayMenuItem( int _num, QWidget*parent = 0 );

    void setMenuItem(const QString &icon1, const QString &text,
                      const QString &icon2 );
    void setMenuItem(const QString &icon1, const QString &text );

public:
signals:
    void signal_clicktrayMenuItem( int );

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QLabel          iconLabel1;
    QLabel          iconLabel2;
    QLabel          textLabel;

    int             m_itemId;
};

class trayIconMenu : public QMenu
{
    Q_OBJECT
public:
    trayIconMenu(QWidget*parent=0);
    void   initMenu();

    void setPlayTypeAction(const CURRING_PLAY_TYPE _playType);
    void setWidgetShowTypeAction(const WIDGET_SHOW_TYPE _widgetShowType);
    void setPlayStatesAction(const MUESIC_PLAY_STATUS _playStates);
    QString getMenuStyle();

signals:
    void sig_OpenDeskTopLrc();
    void signal_appQuit();
    void signal_clickPlayMusic();
    void signal_clickPlayMusicNext(bool isClick);
    void signal_clickPlayMusicLast(bool isClick);

    void signal_clickWidgetShowType( const WIDGET_SHOW_TYPE );
    void signal_choosePlayType( const CURRING_PLAY_TYPE );
    void signal_choosePlayStates( const MUESIC_PLAY_STATUS );

public slots:
    void slot_clickPlayTypeLoopOne();
    void slot_clickPlayTypeLoopAll();
    void slot_clickPlayTypeRandem();

    void slot_clickwidgetShowMin();
    void slot_clickwidgetShowNormal();
    void slot_clickwidgetPlayShowMine();

    void slot_updateCurrentMusicName( const QString );

private:
    QAction             *m_currentMusicName;
    QAction             *m_playAction;
    QAction             *m_lastAction;
    QAction             *m_nextAction;
    QAction             *m_loopMenu;
    QAction             *m_showMenu;

    QAction             *m_widgetShowMin;
    QAction             *m_widgetShowMax;
    QAction             *m_widgetPlayMini;

    QAction             *m_playLoopAll;
    QAction             *m_playLoopOne;
    QAction             *m_playLoopRandom;

    BaseWidget           m_sizeWidget;

};

#endif // TRAYICONMENU_H
