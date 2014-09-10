// checksum 0x5a0b version 0x9000c
/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/

#include "html5applicationviewer.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLinearLayout>
#include <QGraphicsWebView>
#include <QWebFrame>

#ifdef TOUCH_OPTIMIZED_NAVIGATION
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QWebElement>
/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/



class QWebFrame;

class WebTouchPhysicsInterface : public QObject
{
    Q_OBJECT

public:
    WebTouchPhysicsInterface(QObject *parent = 0);
    virtual ~WebTouchPhysicsInterface();
    static WebTouchPhysicsInterface* getSingleton();

    virtual bool inMotion() = 0;
    virtual void stop() = 0;
    virtual void start(const QPointF &pressPoint, const QWebFrame *frame) = 0;
    virtual bool move(const QPointF &pressPoint) = 0;
    virtual bool release(const QPointF &pressPoint) = 0;

signals:
    void positionChanged(const QPointF &point, const QPoint &startPressPoint);

public slots:
    virtual void setRange(const QRectF &range) = 0;

private:
    static WebTouchPhysicsInterface* s_instance;
};

/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/



static const int KCumulativeDistanceThreshold = 40;
static const int KDecelerationCount = 4;
static const int KDecelerationTimerSpeed = 10;
static const int KFlickScrollThreshold = 400;
static const int KJitterBufferThreshold = 200;
static const qreal KDecelerationSlowdownFactor = 0.975;

static const int KTouchDownStartTime = 200;
static const int KHoverTimeoutThreshold = 100;
static const int KNodeSearchThreshold = 400;

class WebTouchPhysics : public WebTouchPhysicsInterface
{
    Q_OBJECT

public:
    WebTouchPhysics(QObject *parent = 0);
    virtual ~WebTouchPhysics();

    virtual bool inMotion();
    virtual void stop();
    virtual void start(const QPointF &pressPoint, const QWebFrame *frame);
    virtual bool move(const QPointF &pressPoint);
    virtual bool release(const QPointF &pressPoint);

signals:
    void setRange(const QRectF &range);

public slots:
    void decelerationTimerFired();
    void changePosition(const QPointF &point);
    bool isFlick(const QPointF &point, int distance) const;
    bool isPan(const QPointF &point, int distance) const;

private:
    QPointF m_previousPoint;
    QPoint m_startPressPoint;
    QPointF m_decelerationSpeed;
    QList<QPointF> m_decelerationPoints;
    QTimer m_decelerationTimer;
    QPointF m_cumulativeDistance;
    const QWebFrame* m_frame;
    bool m_inMotion;
};

/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/



class WebTouchEvent
{
public:
    WebTouchEvent();
    WebTouchEvent(const QMouseEvent *mouseEvent);
    WebTouchEvent(const QGraphicsSceneMouseEvent *graphicsSceneMouseEvent);

    QPoint m_pos;
    QEvent::Type m_type;
    Qt::MouseButton m_button;
    Qt::MouseButtons m_buttons;
    bool m_graphicsSceneEvent;
    bool m_fired;
    bool m_editable;
    Qt::KeyboardModifiers m_modifier;

    //Graphics scene event members
    QPointF m_scenePos;
    QPoint m_screenPos;
    QPointF m_buttonDownPos;
    QPointF m_buttonDownScenePos;
    QPoint m_buttonDownScreenPos;
    QPointF m_lastPos;
    QPointF m_lastScenePos;
    QPoint m_lastScreenPos;
};

/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/



class QWebFrame;

class WebTouchScroller : public QObject
{
    Q_OBJECT

public:
    WebTouchScroller(QObject *parent = 0);
    virtual ~WebTouchScroller();

signals:
    void rangeChanged(const QRectF &range);

public slots:
    void setFrame(QWebFrame* frame);
    void scroll(const QPointF &delta, const QPoint &scrollStartPoint);

private:
    QWebFrame* m_webFrame;
    QSize m_range;
};

/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/



class QWebPage;

class WebTouchNavigation : public QObject
{
    Q_OBJECT

public:
    WebTouchNavigation(QObject *object, QWebPage *webPage);
    virtual ~WebTouchNavigation();

protected:
    bool eventFilter(QObject *object, QEvent *event);
    void handleDownEvent(const WebTouchEvent &event);
    void handleMoveEvent(const WebTouchEvent &event);
    void handleReleaseEvent(const WebTouchEvent &event);

public slots:
    void hoverTimerFired();
    void downTimerFired();
    void quickDownTimerFired();
    void quickUpTimerFired();

private:
    void invalidateLastTouchDown();
    void generateMouseEvent(const WebTouchEvent &touchEvent);

private:
    WebTouchPhysicsInterface* m_physics;
    WebTouchScroller* m_scroller;
    WebTouchEvent m_touchDown;
    QObject* m_viewObject;
    QWebPage* m_webPage;
    QWebFrame* m_webFrame;
    QTimer m_downTimer;
    QTimer m_hoverTimer;
    QTimer m_quickDownTimer;
    QTimer m_quickUpTimer;
    bool m_suppressMouseEvents;
};

/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/



class QWebPage;
class WebTouchNavigation;

class WebNavigation : public QObject
{
    Q_OBJECT

public:
    WebNavigation(QObject *parent, QWebPage *webPage);
    virtual ~WebNavigation();

private:
    QObject *m_viewObject;
    QWebPage *m_webPage;
    WebTouchNavigation *m_webTouchNavigation;
};

/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/



class QGraphicsWebView;
class QWebPage;

class NavigationController : public QObject
{
    Q_OBJECT

public:
    NavigationController(QWidget *parent, QGraphicsWebView *webView);
    virtual ~NavigationController();

    QWidget *webWidget() const;
    QWebPage* webPage() const;
    QGraphicsWebView* graphicsWebView() const;

signals:
    void pauseNavigation();
    void resumeNavigation();

private:
    class NavigationControllerPrivate *m_d;
};

/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/


WebTouchPhysicsInterface* WebTouchPhysicsInterface::s_instance = 0;

WebTouchPhysicsInterface::WebTouchPhysicsInterface(QObject *parent)
    : QObject(parent)
{
}

WebTouchPhysicsInterface::~WebTouchPhysicsInterface()
{
    if (s_instance == this)
        s_instance = 0;
}

WebTouchPhysicsInterface* WebTouchPhysicsInterface::getSingleton()
{
    if (!s_instance)
        s_instance = new WebTouchPhysics;
    return s_instance;
}
/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/



int fastDistance(const QPoint &p, const QPoint &q)
{
    return (p.x() - q.x()) * (p.x() - q.x()) + (p.y() - q.y()) * (p.y() - q.y());
}

WebTouchPhysics::WebTouchPhysics(QObject *parent)
    : WebTouchPhysicsInterface(parent)
    , m_frame(0)
    , m_inMotion(false)
{
    connect(&m_decelerationTimer, SIGNAL(timeout()), this, SLOT(decelerationTimerFired()));
}

WebTouchPhysics::~WebTouchPhysics()
{
}

bool WebTouchPhysics::inMotion()
{
    return m_inMotion;
}

void WebTouchPhysics::stop()
{
    m_decelerationTimer.stop();
    m_cumulativeDistance = QPoint();
    m_previousPoint = QPoint();
    m_startPressPoint = QPoint();
    m_decelerationPoints.clear();
    m_inMotion = false;
}

void WebTouchPhysics::start(const QPointF &pressPoint, const QWebFrame *frame)
{
    if (!frame)
        return;

    m_frame = frame;
    m_decelerationPoints.push_front(pressPoint);
    m_decelerationTimer.setSingleShot(false);
    m_decelerationTimer.setInterval(KDecelerationTimerSpeed);
    m_previousPoint = pressPoint;
    m_startPressPoint = pressPoint.toPoint();
}

bool WebTouchPhysics::move(const QPointF &pressPoint)
{
    int distance = fastDistance(pressPoint.toPoint(), m_startPressPoint);
    if (isFlick(pressPoint, distance) || isPan(pressPoint, distance)) {
        changePosition(pressPoint);
        return true;
    }
    return false;
}

bool WebTouchPhysics::release(const QPointF &pressPoint)
{
    // use the cumulative distance in this case because it seems like a positive user experience
    if (m_cumulativeDistance.manhattanLength() > KCumulativeDistanceThreshold) {
        m_decelerationSpeed = (m_decelerationPoints.back() - pressPoint) / (m_decelerationPoints.count() + 1);
        m_decelerationTimer.start();
        return true;
    } else {
        m_inMotion = false;
        return false;
    }
}

void WebTouchPhysics::changePosition(const QPointF &point)
{
    m_inMotion = true;
    QPointF diff = m_previousPoint - point;
    emit positionChanged(diff, m_startPressPoint);

    m_cumulativeDistance += (point - m_previousPoint);
    m_previousPoint = point;
    m_decelerationPoints.push_front(point);
    if (m_decelerationPoints.count() > KDecelerationCount)
        m_decelerationPoints.pop_back();
}

void WebTouchPhysics::decelerationTimerFired()
{
    if (!m_frame) {
        m_decelerationTimer.stop();
        return;
    }

    if (qAbs(m_decelerationSpeed.x()) < KDecelerationSlowdownFactor
            && qAbs(m_decelerationSpeed.y()) < KDecelerationSlowdownFactor) {
        m_inMotion = false;
        m_decelerationTimer.stop();
        return;
    }

    m_decelerationSpeed *= KDecelerationSlowdownFactor;
    emit positionChanged(QPoint(m_decelerationSpeed.x(), m_decelerationSpeed.y()), m_startPressPoint);
}

bool WebTouchPhysics::isFlick(const QPointF &pressPoint, int distance) const
{
    Q_UNUSED(pressPoint);
    // this mouse move event is far away from the touch down position in
    // less than xx sec, the user must want to scroll quickly.
    return !m_inMotion && distance > KFlickScrollThreshold;
}

bool WebTouchPhysics::isPan(const QPointF &pressPoint, int distance) const
{
    Q_UNUSED(pressPoint);
    return distance > KJitterBufferThreshold;
}
/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/


WebTouchEvent::WebTouchEvent()
    : m_type(QEvent::None)
    , m_button(Qt::NoButton)
    , m_buttons(Qt::NoButton)
    , m_graphicsSceneEvent(false)
    , m_fired(false)
    , m_editable(false)
    , m_modifier(Qt::NoModifier)
{}

WebTouchEvent::WebTouchEvent(const QMouseEvent *mouseEvent)
{
    Q_ASSERT(mouseEvent != 0);
    m_type = mouseEvent->type();
    m_pos = mouseEvent->pos();
    m_button = mouseEvent->button();
    m_buttons = mouseEvent->buttons();
    m_modifier = mouseEvent->modifiers();
    m_fired = false;
    m_editable = false;
    m_graphicsSceneEvent = false;
}

WebTouchEvent::WebTouchEvent(const QGraphicsSceneMouseEvent *graphicsSceneMouseEvent)
{
    Q_ASSERT(graphicsSceneMouseEvent != 0);
    m_type = graphicsSceneMouseEvent->type();
    m_pos = graphicsSceneMouseEvent->pos().toPoint();
    m_button = graphicsSceneMouseEvent->button();
    m_buttons = graphicsSceneMouseEvent->buttons();
    m_modifier = graphicsSceneMouseEvent->modifiers();
    m_scenePos = graphicsSceneMouseEvent->scenePos();
    m_screenPos = graphicsSceneMouseEvent->screenPos();
    m_buttonDownPos = graphicsSceneMouseEvent->buttonDownPos(graphicsSceneMouseEvent->button());
    m_buttonDownScenePos = graphicsSceneMouseEvent->buttonDownScenePos(graphicsSceneMouseEvent->button());
    m_buttonDownScreenPos = graphicsSceneMouseEvent->buttonDownScreenPos(graphicsSceneMouseEvent->button());
    m_lastPos = graphicsSceneMouseEvent->lastPos();
    m_lastScenePos = graphicsSceneMouseEvent->lastScenePos();
    m_lastScreenPos = graphicsSceneMouseEvent->lastScreenPos();
    m_fired = false;
    m_editable = false;
    m_graphicsSceneEvent = true;
}
/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/


void qtwebkit_webframe_scrollRecursively(QWebFrame* qFrame, int dx, int dy, const QPoint &pos)
{
    Q_UNUSED(pos);

    if (!qFrame)
        return;

    bool scrollHorizontal = false;
    bool scrollVertical = false;

    do {
        if (qFrame->scrollBarPolicy(Qt::Horizontal) == Qt::ScrollBarAlwaysOn) {
            if (dx > 0)  // scroll right
                scrollHorizontal = qFrame->scrollBarValue(Qt::Horizontal) < qFrame->scrollBarMaximum(Qt::Horizontal);
            else if (dx < 0)  // scroll left
                scrollHorizontal = qFrame->scrollBarValue(Qt::Horizontal) > qFrame->scrollBarMinimum(Qt::Horizontal);
        } else {
            scrollHorizontal = true;
        }

        if (qFrame->scrollBarPolicy(Qt::Vertical) == Qt::ScrollBarAlwaysOn) {
            if (dy > 0)  // scroll down
                scrollVertical = qFrame->scrollBarValue(Qt::Vertical) < qFrame->scrollBarMaximum(Qt::Vertical);
            else if (dy < 0) //scroll up
                scrollVertical = qFrame->scrollBarValue(Qt::Vertical) > qFrame->scrollBarMinimum(Qt::Vertical);
        } else {
            scrollVertical = true;
        }

        if (scrollHorizontal || scrollVertical) {
            qFrame->scroll(dx, dy);
            return;
        }

        qFrame = qFrame->parentFrame();
    } while (qFrame);
}

WebTouchScroller::WebTouchScroller(QObject *parent)
    : QObject(parent)
    , m_webFrame(0)
{
}

WebTouchScroller::~WebTouchScroller()
{
}

void WebTouchScroller::setFrame(QWebFrame* frame)
{
    m_webFrame = frame;
}

void WebTouchScroller::scroll(const QPointF &delta, const QPoint &scrollStartPoint)
{
    if (!m_webFrame)
        return;

    qtwebkit_webframe_scrollRecursively(m_webFrame, delta.x(), delta.y(),
                                        scrollStartPoint - m_webFrame->scrollPosition());
}
/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/


int xInRect(const QRect &r, int x)
{
    int x1 = qMin(x, r.right()-2);
    return qMax(x1, r.left()+2);
}

int yInRect(const QRect &r, int y)
{
    int y1 = qMin(y, r.bottom()-2);
    return qMax(y1, r.top()+2);
}

int wtnFastDistance(const QPoint &p, const QPoint &q)
{
    return (p.x() - q.x()) * (p.x() - q.x()) + (p.y() - q.y()) * (p.y() - q.y());
}

QPoint frameViewPosition(QWebFrame *frame)
{
    QPoint fp;
    QWebFrame* f = frame;
    while (1) {
        fp += f->pos();
        f = f->parentFrame();
        if (f) {
            fp -= f->scrollPosition();
        } else
            break;
    }
    return fp;
}

QPoint closestElement(QObject *viewObject, QWebFrame *frame, WebTouchEvent &touchEvent, int searchThreshold)
{
    Q_UNUSED(viewObject)
    QPoint adjustedPoint(touchEvent.m_pos);

    QWebHitTestResult htr = frame->hitTestContent(adjustedPoint);

    if (htr.isContentEditable()) {
        QString type = htr.element().attribute("type").toLower();
        // Don't summon the vkb for a hidden input element.
        // This should never happen anyway.
        if (type == "hidden") {
            touchEvent.m_editable = false;
            return adjustedPoint;
        }

        // Don't summon the vkb for a disabled input; in fact, close the vkbd.
        QString disabled = htr.element().attribute("disabled").toLower();
        if (disabled == "disabled" || disabled == "true") {
            touchEvent.m_editable = false;
            return adjustedPoint;
        }

        // QtWebKit EditorClientQt already enables these input hints. Thus, this should only be
        // enabled if QtWebKit happens to be old. Qt::ImhNoPredictiveText is only enalbed for Maemo on WebKit side.


        touchEvent.m_editable = true;
        return adjustedPoint;
    }

    if (!htr.element().tagName().toLower().compare("select") && htr.element().hasAttribute("multiple")) {
        touchEvent.m_modifier = Qt::ControlModifier;
        return adjustedPoint;
    }

    // If clicked element need receive event, do NOT adjust
    // like : achor, input, map, button, textarea
    QString tagName = htr.element().tagName().toLower();
    if (!htr.linkElement().isNull() ||
            !tagName.compare("input") ||
            !tagName.compare("map") ||
            !tagName.compare("button") ||
            !tagName.compare("textarea") ||
            htr.element().hasAttribute("onClick"))
        return adjustedPoint;

    // Attempt to find the closest radio button or checkbox.  Their areas can be so
    // small that we need to adjust the our position to be exactly on them if in the vicinity.
    QString selector = "input[type=\"radio\"], input[type=\"checkbox\"]";
    QWebElementCollection elementList = frame->findAllElements(selector);
    QWebElementCollection::iterator it(elementList.begin());

    // find the origin of current frame position in view based coordinate
    QPoint originPoint = frameViewPosition(frame);

    // transfer the event position from view based coordinate to the current frame's content based coordinate
    QPoint frameScrollPoint = frame->scrollPosition();
    QPoint framePoint = adjustedPoint - originPoint + frameScrollPoint;

    QPoint adjustedFramePoint = framePoint;

    // find the closest element
    int maxDist = searchThreshold;
    while (it != elementList.end()) {
        QRect nRect((*it).geometry());
        if (nRect.isValid()) {
            QPoint pt(xInRect(nRect, framePoint.x()), yInRect(nRect, framePoint.y()));
            int dist = wtnFastDistance(pt, framePoint);
            if (dist < maxDist) {
                adjustedFramePoint = pt;
                maxDist = dist;
            }
        }
        ++it;
    }

    // transfer the adjusted position from the current frame's content based coordinate to view based coordinate
    adjustedPoint = adjustedFramePoint - frameScrollPoint + originPoint;

    return adjustedPoint;
}

WebTouchNavigation::WebTouchNavigation(QObject *parent, QWebPage *webPage)
    : m_viewObject(parent)
    , m_webPage(webPage)
    , m_suppressMouseEvents(false)

{
    Q_ASSERT(m_webPage);
    connect(&m_downTimer, SIGNAL(timeout()), this, SLOT(downTimerFired()));
    connect(&m_hoverTimer, SIGNAL(timeout()), this, SLOT(hoverTimerFired()));
    connect(&m_quickDownTimer, SIGNAL(timeout()), this, SLOT(quickDownTimerFired()));
    connect(&m_quickUpTimer, SIGNAL(timeout()), this, SLOT(quickUpTimerFired()));

    m_physics = WebTouchPhysicsInterface::getSingleton();
    m_physics->setParent(this);
    m_scroller = new WebTouchScroller(this);

    connect(m_physics, SIGNAL(positionChanged(QPointF,QPoint)), m_scroller, SLOT(scroll(QPointF,QPoint)));
    connect(m_scroller, SIGNAL(rangeChanged(QRectF)), m_physics, SLOT(setRange(QRectF)));
}

WebTouchNavigation::~WebTouchNavigation()
{
}

bool WebTouchNavigation::eventFilter(QObject *object, QEvent *event)
{
    if (object != m_viewObject)
        return false;

    bool eventHandled = false;

    switch (event->type()) {
    case QEvent::MouseButtonPress:
        if (static_cast<QMouseEvent*>(event)->buttons() & Qt::LeftButton) {
            WebTouchEvent e(static_cast<QMouseEvent*>(event));
            handleDownEvent(e);
        }
        eventHandled = true;
        break;
    case QEvent::MouseMove:
        if (static_cast<QMouseEvent*>(event)->buttons() & Qt::LeftButton) {
            WebTouchEvent e(static_cast<QMouseEvent*>(event));
            handleMoveEvent(e);
        }
        eventHandled = true;
        break;
    case QEvent::MouseButtonRelease:
        {
            WebTouchEvent e(static_cast<QMouseEvent*>(event));
            handleReleaseEvent(e);
            eventHandled = true;
        }
        break;
    case QEvent::GraphicsSceneMousePress:
        if (static_cast<QGraphicsSceneMouseEvent*>(event)->buttons() & Qt::LeftButton) {
            WebTouchEvent e(static_cast<QGraphicsSceneMouseEvent*>(event));
            handleDownEvent(e);
        }
        eventHandled = true;
        break;
    case QEvent::GraphicsSceneMouseMove:
        if (static_cast<QGraphicsSceneMouseEvent *>(event)->buttons() & Qt::LeftButton) {
            WebTouchEvent e(static_cast<QGraphicsSceneMouseEvent*>(event));
            handleMoveEvent(e);
        }
        eventHandled = true;
        break;
    case QEvent::GraphicsSceneMouseRelease:
        {
            WebTouchEvent e(static_cast<QGraphicsSceneMouseEvent*>(event));
            handleReleaseEvent(e);
            eventHandled = true;
        }
        break;
    case QEvent::MouseButtonDblClick:
    case QEvent::ContextMenu:
    case QEvent::CursorChange:
    case QEvent::DragEnter:
    case QEvent::DragLeave:
    case QEvent::DragMove:
    case QEvent::Drop:
    case QEvent::GrabMouse:
    case QEvent::GraphicsSceneContextMenu:
    case QEvent::GraphicsSceneDragEnter:
    case QEvent::GraphicsSceneDragLeave:
    case QEvent::GraphicsSceneDragMove:
    case QEvent::GraphicsSceneDrop:
    case QEvent::GraphicsSceneHelp:
    case QEvent::GraphicsSceneHoverEnter:
    case QEvent::GraphicsSceneHoverLeave:
    case QEvent::GraphicsSceneHoverMove:
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
    case QEvent::HoverMove:
    case QEvent::Gesture:
    case QEvent::GestureOverride:
        eventHandled = true;
        break;
    default:
        break;
    }

    return eventHandled;
}

void WebTouchNavigation::quickDownTimerFired()
{
    m_touchDown.m_type = (m_touchDown.m_graphicsSceneEvent) ? QEvent::GraphicsSceneMousePress : QEvent::MouseButtonPress;
    m_touchDown.m_pos = closestElement(m_viewObject, m_webFrame, m_touchDown, KNodeSearchThreshold);
    m_touchDown.m_button = Qt::LeftButton;
    m_touchDown.m_buttons = Qt::NoButton;
    generateMouseEvent(m_touchDown);
    m_quickUpTimer.setSingleShot(true);
    m_quickUpTimer.start(0);
}

void WebTouchNavigation::quickUpTimerFired()
{
    m_touchDown.m_type = (m_touchDown.m_graphicsSceneEvent) ? QEvent::GraphicsSceneMouseRelease : QEvent::MouseButtonRelease;
    m_touchDown.m_button = Qt::LeftButton;
    m_touchDown.m_buttons = Qt::NoButton;
    generateMouseEvent(m_touchDown);
}

void WebTouchNavigation::downTimerFired()
{
    m_touchDown.m_type = (m_touchDown.m_graphicsSceneEvent) ? QEvent::GraphicsSceneMousePress : QEvent::MouseButtonPress;
    m_touchDown.m_pos = closestElement(m_viewObject, m_webFrame, m_touchDown, KNodeSearchThreshold);
    m_touchDown.m_button = Qt::LeftButton;
    m_touchDown.m_buttons = Qt::NoButton;
    generateMouseEvent(m_touchDown);
    m_touchDown.m_fired = true;
}

void WebTouchNavigation::hoverTimerFired()
{
    m_touchDown.m_type = (m_touchDown.m_graphicsSceneEvent) ? QEvent::GraphicsSceneMouseMove : QEvent::MouseMove;
    m_touchDown.m_button = Qt::NoButton;
    m_touchDown.m_buttons = Qt::NoButton;
    generateMouseEvent(m_touchDown);
}

void WebTouchNavigation::invalidateLastTouchDown()
{
    if (m_touchDown.m_fired) {
        // send mouse up event invalidate click
        m_touchDown.m_type = (m_touchDown.m_graphicsSceneEvent) ? QEvent::GraphicsSceneMouseRelease : QEvent::MouseButtonRelease;
        m_touchDown.m_pos = QPoint(-1, -1);
        m_touchDown.m_button = Qt::LeftButton;
        m_touchDown.m_buttons = Qt::NoButton;
        m_touchDown.m_editable = false;
        generateMouseEvent(m_touchDown);
    }
}

void WebTouchNavigation::handleDownEvent(const WebTouchEvent &event)
{
    // Stop previously running physics
    m_physics->stop();

    m_downTimer.stop();
    m_hoverTimer.stop();
    m_quickDownTimer.stop();
    m_quickUpTimer.stop();

    m_webFrame = m_webPage->frameAt(event.m_pos);
    if (!m_webFrame)
        m_webFrame = m_webPage->currentFrame();

    m_scroller->setFrame(m_webFrame);

    m_touchDown = event;

    m_hoverTimer.setSingleShot(true);
    m_hoverTimer.start(KHoverTimeoutThreshold);

    m_downTimer.setSingleShot(true);
    m_downTimer.start(KTouchDownStartTime);

    // Start physics again
    m_physics->start(event.m_pos, m_webFrame);
}

void WebTouchNavigation::handleMoveEvent(const WebTouchEvent &event)
{
    if (m_physics->move(event.m_pos)) {
        // don't send mouse down event.
        m_downTimer.stop();
        m_hoverTimer.stop();
    }
}

void WebTouchNavigation::handleReleaseEvent(const WebTouchEvent &event)
{
    if (!m_physics->inMotion() && (m_hoverTimer.isActive() || m_downTimer.isActive())) { // Quick tap
        if (m_hoverTimer.isActive()) {
            m_touchDown.m_type = (m_touchDown.m_graphicsSceneEvent) ? QEvent::GraphicsSceneMouseMove : QEvent::MouseMove;
            m_touchDown.m_button = Qt::NoButton;
            m_touchDown.m_buttons = Qt::NoButton;
            generateMouseEvent(m_touchDown);
        }

        m_hoverTimer.stop();
        m_downTimer.stop();

        m_quickDownTimer.setSingleShot(true);
        m_quickDownTimer.start(0);
        return;
    }

    m_hoverTimer.stop();
    m_downTimer.stop();

    if (m_physics->release(event.m_pos)) {
        // Going to kinetic motion. Thus, invalidating last touch down.
        invalidateLastTouchDown();
        return;
    }

    if (m_touchDown.m_fired) {
        // send mouse up event
        m_touchDown.m_type = (m_touchDown.m_graphicsSceneEvent) ? QEvent::GraphicsSceneMouseRelease : QEvent::MouseButtonRelease;
        m_touchDown.m_button = Qt::LeftButton;
        m_touchDown.m_buttons = Qt::NoButton;
        generateMouseEvent(m_touchDown);
    }
}

void WebTouchNavigation::generateMouseEvent(const WebTouchEvent &touchEvent)
{
    if (!touchEvent.m_editable && m_suppressMouseEvents) //do not suppress mouse events for input box, etc.
        return;

    if (touchEvent.m_type == QEvent::GraphicsSceneMousePress
            || touchEvent.m_type == QEvent::GraphicsSceneMouseMove
            || touchEvent.m_type == QEvent::GraphicsSceneMouseRelease) {
        QGraphicsSceneMouseEvent ievmm(touchEvent.m_type);
        ievmm.setPos(touchEvent.m_pos);
        ievmm.setScenePos(touchEvent.m_scenePos);
        ievmm.setScreenPos(touchEvent.m_screenPos);
        ievmm.setButtonDownPos(touchEvent.m_button, touchEvent.m_buttonDownPos);
        ievmm.setButtonDownScenePos( touchEvent.m_button, touchEvent.m_buttonDownScenePos);
        ievmm.setButtonDownScreenPos( touchEvent.m_button, touchEvent.m_buttonDownScreenPos);
        ievmm.setLastPos(touchEvent.m_lastPos);
        ievmm.setLastScenePos(touchEvent.m_lastScenePos);
        ievmm.setLastScreenPos(touchEvent.m_lastScreenPos);
        ievmm.setButtons(touchEvent.m_buttons);
        ievmm.setButton( touchEvent.m_button);
        ievmm.setModifiers(touchEvent.m_modifier);
        m_webPage->event(&ievmm);
    } else {
        bool inputMethodEnabled = static_cast<QWidget*>(m_viewObject)->testAttribute(Qt::WA_InputMethodEnabled);
        if (touchEvent.m_type == QEvent::MouseButtonRelease && inputMethodEnabled) {
            if (touchEvent.m_editable) {
                QEvent rsipevent(QEvent::RequestSoftwareInputPanel);
                QCoreApplication::sendEvent(static_cast<QWidget*>(m_viewObject), &rsipevent);
            } else {
                static_cast<QWidget*>(m_viewObject)->setAttribute(Qt::WA_InputMethodEnabled, false); // disable input methods if user didn't tap on editable area.
            }
        }

        QMouseEvent ievmm(touchEvent.m_type, touchEvent.m_pos, touchEvent.m_button, touchEvent.m_buttons, touchEvent.m_modifier);
        m_webPage->event(&ievmm);

        if (touchEvent.m_type == QEvent::MouseButtonRelease && inputMethodEnabled)
            static_cast<QWidget*>(m_viewObject)->setAttribute(Qt::WA_InputMethodEnabled, inputMethodEnabled); // re-enable input methods if disabled
    }
}
/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/


WebNavigation::WebNavigation(QObject *parent, QWebPage *webPage)
    : m_viewObject(parent)
    , m_webPage(webPage)
    , m_webTouchNavigation(0)
{
    m_webTouchNavigation = new WebTouchNavigation(m_viewObject, m_webPage);
    m_viewObject->installEventFilter(m_webTouchNavigation);
}

WebNavigation::~WebNavigation()
{
    delete m_webTouchNavigation;
}
/*
  This file was generated by the Html5 Application wizard of Qt Creator.
  Html5ApplicationViewer is a convenience class containing mobile device specific
  code such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/


class NavigationControllerPrivate
{
public:
    NavigationControllerPrivate(QWidget *parent, QGraphicsWebView *webView);
    ~NavigationControllerPrivate();

    QWebPage *m_webPage;
    QWidget *m_webWidget;
    QGraphicsWebView *m_graphicsWebView;
    WebNavigation *m_webNavigation;
};

NavigationControllerPrivate::NavigationControllerPrivate(QWidget *parent, QGraphicsWebView *webView)
    : m_webPage(0)
    , m_webWidget(0)
    , m_graphicsWebView(webView)
    , m_webNavigation(0)
{
    Q_UNUSED(parent);
    m_graphicsWebView->setAcceptTouchEvents(true);
    m_webPage = new QWebPage;
    m_graphicsWebView->setPage(m_webPage);
    m_webNavigation = new WebNavigation(m_graphicsWebView, m_webPage);
    m_webNavigation->setParent(m_graphicsWebView);
}

NavigationControllerPrivate::~NavigationControllerPrivate()
{
    if (m_webNavigation)
        delete m_webNavigation;
    if (m_webPage)
        delete m_webPage;
    if (m_graphicsWebView)
        delete m_graphicsWebView;
}

NavigationController::NavigationController(QWidget *parent, QGraphicsWebView *webView)
    : m_d(new NavigationControllerPrivate(parent, webView))
{
}

NavigationController::~NavigationController()
{
    delete m_d;
}

QWebPage* NavigationController::webPage() const
{
    return m_d->m_webPage;
}

QGraphicsWebView* NavigationController::graphicsWebView() const
{
    return m_d->m_graphicsWebView;
}
#endif // TOUCH_OPTIMIZED_NAVIGATION

class Html5ApplicationViewerPrivate : public QGraphicsView
{
    Q_OBJECT
public:
    Html5ApplicationViewerPrivate(QWidget *parent = 0);

    void resizeEvent(QResizeEvent *event);
    static QString adjustPath(const QString &path);

public slots:
    void quit();

private slots:
    void addToJavaScript();

signals:
    void quitRequested();

public:
    QGraphicsWebView *m_webView;
#ifdef TOUCH_OPTIMIZED_NAVIGATION
    NavigationController *m_controller;
#endif // TOUCH_OPTIMIZED_NAVIGATION
};

Html5ApplicationViewerPrivate::Html5ApplicationViewerPrivate(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene;
    setScene(scene);
    setFrameShape(QFrame::NoFrame);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_webView = new QGraphicsWebView;
    m_webView->setAcceptTouchEvents(true);
    m_webView->setAcceptHoverEvents(false);
    setAttribute(Qt::WA_AcceptTouchEvents, true);
    scene->addItem(m_webView);
    scene->setActiveWindow(m_webView);
#ifdef TOUCH_OPTIMIZED_NAVIGATION
    m_controller = new NavigationController(parent, m_webView);
#endif // TOUCH_OPTIMIZED_NAVIGATION
    connect(m_webView->page()->mainFrame(),
            SIGNAL(javaScriptWindowObjectCleared()), SLOT(addToJavaScript()));
}

void Html5ApplicationViewerPrivate::resizeEvent(QResizeEvent *event)
{
    m_webView->resize(event->size());
}

QString Html5ApplicationViewerPrivate::adjustPath(const QString &path)
{
#ifdef Q_OS_UNIX
#ifdef Q_OS_MAC
    if (!QDir::isAbsolutePath(path))
        return QCoreApplication::applicationDirPath()
                + QLatin1String("/../Resources/") + path;
#else
    const QString pathInInstallDir = QCoreApplication::applicationDirPath()
        + QLatin1String("/../") + path;
    if (pathInInstallDir.contains(QLatin1String("opt"))
            && pathInInstallDir.contains(QLatin1String("bin"))
            && QFileInfo(pathInInstallDir).exists()) {
        return pathInInstallDir;
    }
#endif
#endif
    return QFileInfo(path).absoluteFilePath();
}

void Html5ApplicationViewerPrivate::quit()
{
    emit quitRequested();
}

void Html5ApplicationViewerPrivate::addToJavaScript()
{
    m_webView->page()->mainFrame()->addToJavaScriptWindowObject("Qt", this);
}

Html5ApplicationViewer::Html5ApplicationViewer(QWidget *parent)
    : QWidget(parent)
    , m_d(new Html5ApplicationViewerPrivate(this))
{
    connect(m_d, SIGNAL(quitRequested()), SLOT(close()));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_d);
    layout->setMargin(0);
    setLayout(layout);
}

Html5ApplicationViewer::~Html5ApplicationViewer()
{
    delete m_d;
}

void Html5ApplicationViewer::loadFile(const QString &fileName)
{
    m_d->m_webView->setUrl(QUrl::fromLocalFile(Html5ApplicationViewerPrivate::adjustPath(fileName)));
}

void Html5ApplicationViewer::loadUrl(const QUrl &url)
{
    m_d->m_webView->setUrl(url);
}

void Html5ApplicationViewer::setOrientation(ScreenOrientation orientation)
{
    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#elif QT_VERSION < 0x050000
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#else
    default:
        attribute = Qt::WidgetAttribute();
#endif
    };
    setAttribute(attribute, true);
}

void Html5ApplicationViewer::showExpanded()
{
    showMaximized();
}

QGraphicsWebView *Html5ApplicationViewer::webView() const
{
    return m_d->m_webView;
}

#include "html5applicationviewer.moc"
