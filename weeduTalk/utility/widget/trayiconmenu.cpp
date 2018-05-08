#include "trayiconmenu.h"
#include <QAction>
#include <QWidgetAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "config/echoconfig.h"

#pragma execution_character_set("utf-8")

trayIconMenu::trayIconMenu( QWidget *parent )
    :QMenu(parent)
{
    this->setFixedWidth( m_sizeWidget.getWidth(200) );
//    this->setContentsMargins(4,5,4,10);
//    resize( 200, 260  );
//    m_sizeWidget.reSetSize( this );
    QString _menuStyle = QString( getMenuStyle() );
    setStyleSheet( _menuStyle );

    setFont(QFont("微软雅黑",8,false));
    initMenu();
}

QString trayIconMenu::getMenuStyle()
{
    return QString("QMenu{background-color: white;border:1px solid #c8c8c8;\
            border-radius:4px;color:#666666;}\
            QMenu::item:selected{background-color: #dfdfdf;}");//\
//            QMenu::item{ height:45px;padding:%1px %2px %3px %4px;}").arg(m_sizeWidget.getWidth(0))
//            .arg(m_sizeWidget.getWidth(20)).arg(m_sizeWidget.getWidth(0)).arg(m_sizeWidget.getWidth(20));
}

void trayIconMenu::initMenu()
{
    m_currentMusicName = new QAction(QIcon(":/images/imagesMenu/playingMusic.png"),"playName",this);
    addAction( m_currentMusicName );
    m_playAction = new QAction(QIcon(":/images/imagesMenu/play.png"),"播放",this);
    addAction( m_playAction );
    connect( m_playAction, SIGNAL(triggered( bool )), this, SIGNAL( signal_clickPlayMusic() ) );
    m_lastAction = new QAction(QIcon(":/images/imagesMenu/lastMusic.png"),"上一首",this);
    addAction( m_lastAction );
    connect( m_lastAction, SIGNAL(triggered( bool )), this, SIGNAL( signal_clickPlayMusicLast(bool) ) );
    m_nextAction = new QAction(QIcon(":/images/imagesMenu/nextMusic.png"),"下一首",this);
    addAction( m_nextAction );
    connect( m_nextAction, SIGNAL(triggered( bool )), this, SIGNAL( signal_clickPlayMusicNext(bool) ) );

    m_loopMenu = new QAction( QIcon(":/images/imagesMenu/loopAll.png"),"列表循环", this );
    addAction( m_loopMenu );
    QMenu *_playWidgeteMenu = new QMenu(this);
//    _playWidgeteMenu->setFixedWidth( m_sizeWidget.getWidth(100) );
    m_playLoopAll = new QAction( /*QIcon(":/images/imagesMenu/next1.png"),*/ "列表循环", this);
    m_playLoopAll->setCheckable( true );
    m_playLoopAll->setChecked( true );
    _playWidgeteMenu->addAction( m_playLoopAll );
    connect( m_playLoopAll, SIGNAL(triggered( bool )), this, SLOT( slot_clickPlayTypeLoopAll() ) );
    m_playLoopOne = new QAction( /*QIcon(":/images/imagesMenu/next1.png"),*/ "单曲循环", this);
    m_playLoopOne->setCheckable( true );
    _playWidgeteMenu->addAction( m_playLoopOne );
    connect( m_playLoopOne, SIGNAL(triggered( bool )), this, SLOT( slot_clickPlayTypeLoopOne() ) );
    m_playLoopRandom = new QAction( /*QIcon(":/images/imagesMenu/next1.png"),*/ "随机播放", this);
    m_playLoopRandom->setCheckable( true );
    _playWidgeteMenu->addAction( m_playLoopRandom );
    connect( m_playLoopRandom, SIGNAL(triggered( bool )), this, SLOT( slot_clickPlayTypeRandem() ) );
    m_loopMenu->setMenu( _playWidgeteMenu );

    m_showMenu = new QAction(QIcon(":/images/imagesMenu/widgetNol.png"),"完整模式",this);

#ifndef Q_OS_MAC

   addAction( m_showMenu );

#endif

    QMenu *_widgetTypeMenu = new QMenu(this);
//    _widgetTypeMenu->setFixedWidth( m_sizeWidget.getWidth(100) );
//    _widgetTypeMenu->resize( 100, 90  );
//    m_sizeWidget.reSetSize( _playTypeMenu );
    m_widgetShowMin = new QAction( /*QIcon(":/images/imagesMenu/next1.png"),*/ "最小化", this);
    m_widgetShowMin->setCheckable( true );
    _widgetTypeMenu->addAction( m_widgetShowMin );
    connect( m_widgetShowMin, SIGNAL(triggered(bool)), this, SLOT( slot_clickwidgetShowMin() ) );
    m_widgetShowMax = new QAction( /*QIcon(":/images/imagesMenu/next1.png"),*/ "完整模式", this);
    m_widgetShowMax->setCheckable( true );
    m_widgetShowMax->setChecked( true );
    _widgetTypeMenu->addAction( m_widgetShowMax );
    connect( m_widgetShowMax, SIGNAL(triggered(bool)), this, SLOT( slot_clickwidgetShowNormal() ) );
    m_widgetPlayMini = new QAction( /*QIcon(":/images/imagesMenu/next1.png"),*/ "mini模式", this);
    m_widgetPlayMini->setCheckable( true );
    _widgetTypeMenu->addAction( m_widgetPlayMini );
    connect( m_widgetPlayMini, SIGNAL(triggered(bool)), this, SLOT( slot_clickwidgetPlayShowMine() ) );
    m_showMenu->setMenu( _widgetTypeMenu );

    addSeparator();
    QAction *appQuit = new QAction(QIcon(":/images/imagesMenu/quit.png"),"退出",this);
    addAction( appQuit );
    connect(appQuit, SIGNAL(triggered( bool )), this, SIGNAL( signal_appQuit() ) );
}

void trayIconMenu::slot_clickPlayTypeLoopOne()
{
    emit signal_choosePlayType( PLAYING_MUESIC_LOOP_ONE );
}

void trayIconMenu::slot_clickPlayTypeLoopAll()
{
    emit signal_choosePlayType( PLAYING_MUESIC_LOOP_ALL );
}

void trayIconMenu::slot_clickPlayTypeRandem()
{
    emit signal_choosePlayType( PLAYING_MUESIC_RANDOM );
}

void trayIconMenu::setPlayStatesAction(const MUESIC_PLAY_STATUS _playStates)
{
    qDebug()<<"setPlayStatesAction";
    if( _playStates == MUESIC_PLAYING_START )
    {
        m_playAction->setText( "暂停" );
        m_playAction->setIcon( QIcon(":/images/imagesMenu/pause.png") );
    }
    else
    {
        m_playAction->setText( "播放" );
        m_playAction->setIcon( QIcon(":/images/imagesMenu/play.png") );
    }
}

void trayIconMenu::setPlayTypeAction(const CURRING_PLAY_TYPE _playType )
{
    m_playLoopAll->setChecked( false );
    m_playLoopOne->setChecked( false );
    m_playLoopRandom->setChecked( false );

    qDebug()<<"setPlayTypeAction";
    switch ( _playType )
    {
    case PLAYING_MUESIC_LOOP_ONE:
        m_playLoopOne->setChecked( true );
        m_loopMenu->setText( "单曲循环" );
        m_loopMenu->setIcon( QIcon(":/images/imagesMenu/loopOne.png") );
        break;

    case PLAYING_MUESIC_LOOP_ALL:
        m_playLoopAll->setChecked( true );
        m_loopMenu->setText( "列表循环" );
        m_loopMenu->setIcon( QIcon(":/images/imagesMenu/loopAll.png") );
        break;

    case PLAYING_MUESIC_RANDOM:
        m_playLoopRandom->setChecked( true );
        m_loopMenu->setText( "随机播放" );
        m_loopMenu->setIcon( QIcon(":/images/imagesMenu/loopRandem.png") );
        break;
    default:
        break;
    }
}

void trayIconMenu::slot_clickwidgetShowMin()
{
    emit signal_clickWidgetShowType( WIDGET_SHOW_MIN );
}

void trayIconMenu::slot_clickwidgetShowNormal()
{
    emit signal_clickWidgetShowType( WIDGET_SHOW_NORMAL );
}

void trayIconMenu::slot_clickwidgetPlayShowMine()
{
    emit signal_clickWidgetShowType( WIDGET_SHOW_MINE );
}

void trayIconMenu::slot_updateCurrentMusicName( const QString _musicName )
{
    QString _showName = _musicName;
    if( _showName.length() > 15 )
        _showName = _showName.left(12) + QString("...");
    m_currentMusicName->setText( _showName );
}

void trayIconMenu::setWidgetShowTypeAction( const WIDGET_SHOW_TYPE _widgetShowType )
{
    m_widgetShowMin->setChecked( false );
    m_widgetShowMax->setChecked( false );
    m_widgetPlayMini->setChecked( false );

    qDebug()<<"setWidgetShowTypeAction";
    switch ( _widgetShowType )
    {
    case WIDGET_SHOW_MIN:
        m_widgetShowMin->setChecked( true );
        m_showMenu->setText( "最小化" );
        m_showMenu->setIcon( QIcon(":/images/imagesMenu/minWidget.png") );
        break;

    case WIDGET_SHOW_NORMAL:
        m_widgetShowMax->setChecked( true );
        m_showMenu->setText( "完整模式" );
        m_showMenu->setIcon( QIcon(":/images/imagesMenu/widgetNol.png") );
        break;

    case WIDGET_SHOW_MINE:
        m_widgetPlayMini->setChecked( true );
        m_showMenu->setText( "mini模式" );
        m_showMenu->setIcon( QIcon(":/images/imagesMenu/miniWidget.png") );
        break;
    default:
        break;
    }

}

trayMenuItem::trayMenuItem(int _num, QWidget *parent):
    BaseWidget( parent ),
    m_itemId( _num )
{
    this->setFont(QFont("Arial",10,false));
//    resize( parent->width(), 30 );
    this->setMinimumHeight( getHeight(30) );
    QHBoxLayout *_widgetLayout = new QHBoxLayout( this );
    QHBoxLayout *_labelLayout = new QHBoxLayout();
    iconLabel1.resize( 24, 24 );
    reSetSize( &iconLabel1 );
    iconLabel2.resize( 24, 24 );
    reSetSize( &iconLabel2 );
    iconLabel1.setScaledContents( true );
    iconLabel2.setScaledContents( true );
    _labelLayout->addWidget( &iconLabel1 );
    _labelLayout->addWidget( &textLabel );
    _labelLayout->setSpacing( getWidth( 10 ) );
    _widgetLayout->addLayout( _labelLayout );
    _labelLayout->setContentsMargins(0,0,0,0);
    _widgetLayout->setContentsMargins(10,0,10,0);
    _widgetLayout->addWidget( &iconLabel2 );

    this->setLayout( _widgetLayout );
}

void trayMenuItem::setMenuItem(const QString &icon1, const QString &text, const QString &icon2)
{
    iconLabel1.setPixmap( QPixmap( icon1 ) );
    iconLabel2.setPixmap( QPixmap( icon2 ) );
    textLabel.setText( text );
}

void trayMenuItem::setMenuItem(const QString &icon1, const QString &text)
{
    iconLabel1.setPixmap( QPixmap( icon1 ) );
    iconLabel2.setPixmap( QPixmap( "" ) );
    textLabel.setText( text );
}

void trayMenuItem::mouseReleaseEvent(QMouseEvent *event)
{
    emit signal_clicktrayMenuItem( m_itemId );
}
