/******************************************************************************
    Simple Player:  this file is part of QtAV examples
    Copyright (C) 2012-2016 Wang Bin <wbsecg1@gmail.com>

*   This file is part of QtAV

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QWidget>
#include <QtAV/QtAV>
#include "mybasesingleton.h"

enum PLAY_SEEK_TYPE
{
    PLAY_SEEK_NONE,
    PLAY_SEEK_START,
    PLAY_SEEK_END
};

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE
class PlayerWindow : public QWidget
{
    MY_DECLARE_SINGLETON(PlayerWindow)

    Q_OBJECT
public:
        explicit PlayerWindow(QWidget *parent = 0);
    QWidget *startPlayMidea( const QString _file, int _startTime = -1, int _endTime = -1 );
public Q_SLOTS:
    void openMedia();
    void seekBySlider(int value);
    void seekBySlider();
    void playPause();
    void slot_positionChanged(qint64 position);
private Q_SLOTS:
    void updateSlider(qint64 value);
    void updateSlider();
    void updateSliderUnit();

    void slot_stateChanged(QtAV::AVPlayer::State state);
    void slot_durationChanged(qint64 duration);

    void seekPlayTime(int value);

public:
signals:
    void signal_playOverThenNext();

private:
    QtAV::VideoOutput           *m_vo;
    QtAV::AVPlayer              *m_player;
    QSlider                     *m_slider;
    QPushButton                 *m_openBtn;
    QPushButton                 *m_playBtn;
    QPushButton                 *m_stopBtn;
    int                         m_unit;

    int                         m_playStartTime;
    int                         m_playEndTime;
    PLAY_SEEK_TYPE              m_seekType;

    qint64                      m_currentPlayDuration;

};

#endif // PLAYERWINDOW_H
