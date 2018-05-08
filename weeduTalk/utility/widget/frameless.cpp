#include "frameless.h"

FrameLess::FrameLess(QWidget *parent) :
_parent(parent),
_cursorchanged(false),
_leftButtonPressed(false),
_borderWidth(5),
_dragPos(QPoint()),
_resizeEnabled(true)
{
    _parent->setMouseTracking(true);
    _parent->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint );
    _parent->setAttribute(Qt::WA_Hover);
    _parent->installEventFilter(this);
    _rubberband = new QRubberBand(QRubberBand::Rectangle);
    m_SetWinRect=false;
    m_xMargin=50;
    m_yMargin=100;
}

bool FrameLess::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseMove ||
        event->type() == QEvent::HoverMove ||
        event->type() == QEvent::Leave ||
        event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::MouseButtonRelease)
    {

        switch (event->type()) {
        case QEvent::MouseMove:
            mouseMove(static_cast<QMouseEvent*>(event));
            return true;
            break;
        case QEvent::HoverMove:
            mouseHover(static_cast<QHoverEvent*>(event));
            return true;
            break;
        case QEvent::Leave:
            mouseLeave(event);
//            return true;
            break;
        case QEvent::MouseButtonPress:
            ((QWidget*)obj)->setFocus();
            mousePress(static_cast<QMouseEvent*>(event));
            return true;
            break;
        case QEvent::MouseButtonRelease:
            mouseRealese(static_cast<QMouseEvent*>(event));
            return true;
            break;
        }
    }

    return _parent->eventFilter(obj, event);
}

void FrameLess::mouseHover(QHoverEvent *event) {
    updateCursorShape(_parent->mapToGlobal(event->pos()));
}

void FrameLess::mouseLeave(QEvent* /*event*/) {
    if (!_leftButtonPressed) {
        _parent->unsetCursor();
    }
}

void FrameLess::mousePress(QMouseEvent *event) {
    if (event->button() & Qt::LeftButton) {
        _leftButtonPressed = true;
        calculateCursorPosition(event->globalPos(), _parent->frameGeometry(), _mousePress);
        if (!_mousePress.testFlag(Edge::None)) {
            _rubberband->setGeometry(_parent->frameGeometry());
        }
        if (_parent->rect().marginsRemoved(QMargins(borderWidth(),borderWidth(),borderWidth(),borderWidth())).contains(event->pos())) {
            _dragStart = true;
            _dragPos = event->pos();
        }
    }
}

void FrameLess::mouseRealese(QMouseEvent *event) {
    if (event->button() & Qt::LeftButton) {
        _leftButtonPressed = false;
        _dragStart = false;
    }
}

void FrameLess::mouseMove(QMouseEvent *event) {
    if (_leftButtonPressed) {
        if (_dragStart) {
            //write by leo
            QPoint newPoint=_parent->frameGeometry().topLeft() + (event->pos() - _dragPos);
            if(m_SetWinRect){

                int xMargin,yMargin;
                xMargin = (_parent->frameSize().rwidth()-m_xMargin);
                yMargin = (_parent->frameSize().height()-m_xMargin);

                if(newPoint.x()<-xMargin)
                {
                    newPoint.setX(-xMargin);
                }
                if(newPoint.x()>m_width-_parent->width()+xMargin)
                {
                    newPoint.setX(m_width-_parent->width()+xMargin);
                }

                if(newPoint.y()<-yMargin)
                {
                    newPoint.setY(-yMargin);
                }
                if(newPoint.y()>m_high-_parent->height()+yMargin)
                {
                    newPoint.setY(m_high-_parent->height()+yMargin);

                }
            }
            _parent->move(newPoint);
        }

        if (!_mousePress.testFlag(Edge::None)) {
            int left = _rubberband->frameGeometry().left();
            int top = _rubberband->frameGeometry().top();
            int right = _rubberband->frameGeometry().right();
            int bottom = _rubberband->frameGeometry().bottom();
            switch (_mousePress) {
            case Edge::Top:
                top = event->globalPos().y();
                break;
            case Edge::Bottom:
                bottom = event->globalPos().y();
                break;
            case Edge::Left:
                left = event->globalPos().x();
                break;
            case Edge::Right:
                right = event->globalPos().x();
                break;
            case Edge::TopLeft:
                top = event->globalPos().y();
                left = event->globalPos().x();
                break;
            case Edge::TopRight:
                right = event->globalPos().x();
                top = event->globalPos().y();
                break;
            case Edge::BottomLeft:
                bottom = event->globalPos().y();
                left = event->globalPos().x();
                break;
            case Edge::BottomRight:
                bottom = event->globalPos().y();
                right = event->globalPos().x();
                break;
            }
            QRect newRect(QPoint(left, top), QPoint(right, bottom));
            if (newRect.width() < _parent->minimumWidth()) {
                left = _parent->frameGeometry().x();
            } else if (newRect.height() < _parent->minimumHeight()) {
                top = _parent->frameGeometry().y();
            }
            _parent->setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)));
            _rubberband->setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)));
        }
    } else {
        updateCursorShape(event->globalPos());
    }
}

void FrameLess::updateCursorShape(const QPoint &pos) {
    if (!_resizeEnabled)
    {
        return;
    }

    if (_parent->isFullScreen() || _parent->isMaximized()) {
        if (_cursorchanged) {
            _parent->unsetCursor();
        }
        return;
    }
    if (!_leftButtonPressed) {
        calculateCursorPosition(pos, _parent->frameGeometry(), _mouseMove);
        _cursorchanged = true;
        if (_mouseMove.testFlag(Edge::Top) || _mouseMove.testFlag(Edge::Bottom)) {
            _parent->setCursor(Qt::SizeVerCursor);
        } else if (_mouseMove.testFlag(Edge::Left) || _mouseMove.testFlag(Edge::Right)) {
            _parent->setCursor(Qt::SizeHorCursor);
        } else if (_mouseMove.testFlag(Edge::TopLeft) || _mouseMove.testFlag(Edge::BottomRight)) {
            _parent->setCursor(Qt::SizeFDiagCursor);
        } else if (_mouseMove.testFlag(Edge::TopRight) || _mouseMove.testFlag(Edge::BottomLeft)) {
            _parent->setCursor(Qt::SizeBDiagCursor);
        } else if (_cursorchanged) {
            _parent->unsetCursor();
            _cursorchanged = false;
        }
    }
}

void FrameLess::calculateCursorPosition(const QPoint &pos, const QRect &framerect, Edges &_edge) {
    if (!_resizeEnabled)
    {
        _edge = None;
        return;
    }

    bool onLeft = pos.x() >= framerect.x() - _borderWidth && pos.x() <= framerect.x() + _borderWidth &&
        pos.y() <= framerect.y() + framerect.height() - _borderWidth && pos.y() >= framerect.y() + _borderWidth;

    bool onRight = pos.x() >= framerect.x() + framerect.width() - _borderWidth && pos.x() <= framerect.x() + framerect.width() &&
        pos.y() >= framerect.y() + _borderWidth && pos.y() <= framerect.y() + framerect.height() - _borderWidth;

    bool onBottom = pos.x() >= framerect.x() + _borderWidth && pos.x() <= framerect.x() + framerect.width() - _borderWidth  &&
        pos.y() >= framerect.y() + framerect.height() - _borderWidth && pos.y() <= framerect.y() + framerect.height();

    bool onTop = pos.x() >= framerect.x() + _borderWidth && pos.x() <= framerect.x() + framerect.width() - _borderWidth &&
        pos.y() >= framerect.y() && pos.y() <= framerect.y() + _borderWidth;

    bool  onBottomLeft = pos.x() <= framerect.x() + _borderWidth && pos.x() >= framerect.x() &&
        pos.y() <= framerect.y() + framerect.height() && pos.y() >= framerect.y() + framerect.height() - _borderWidth;

    bool onBottomRight = pos.x() >= framerect.x() + framerect.width() - _borderWidth && pos.x() <= framerect.x() + framerect.width() &&
        pos.y() >= framerect.y() + framerect.height() - _borderWidth && pos.y() <= framerect.y() + framerect.height();

    bool onTopRight = pos.x() >= framerect.x() + framerect.width() - _borderWidth && pos.x() <= framerect.x() + framerect.width() &&
        pos.y() >= framerect.y() && pos.y() <= framerect.y() + _borderWidth;

    bool onTopLeft = pos.x() >= framerect.x() && pos.x() <= framerect.x() + _borderWidth &&
        pos.y() >= framerect.y() && pos.y() <= framerect.y() + _borderWidth;

    if (onLeft) {
        _edge = Left;
    } else if (onRight) {
        _edge = Right;
    } else if (onBottom) {
        _edge = Bottom;
    } else if (onTop) {
        _edge = Top;
    } else if (onBottomLeft) {
        _edge = BottomLeft;
    } else if (onBottomRight) {
        _edge = BottomRight;
    } else if (onTopRight) {
        _edge = TopRight;
    } else if (onTopLeft) {
        _edge = TopLeft;
    } else {
        _edge = None;
    }
}

bool FrameLess::getResizeEnabled() const
{
    return _resizeEnabled;
}

void FrameLess::setResizeEnabled(bool value)
{
    _resizeEnabled = value;
}

void FrameLess::setBorderWidth(int borderWidth) {
    _borderWidth = borderWidth;
}

int FrameLess::borderWidth() const {
    return _borderWidth;
}
void FrameLess::SetWinRect(int width,int high,int xMargin,int yMargin)
{
    m_width=width;
    m_high=high;
    m_xMargin=xMargin;
    m_yMargin=yMargin;
    m_SetWinRect=true;
}
