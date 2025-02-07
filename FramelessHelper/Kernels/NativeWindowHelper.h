#ifndef NATIVEWINDOWHELPER_H
#define NATIVEWINDOWHELPER_H

#include <QMargins>
#include <QPoint>
#include <QWindow>

class NativeWindowTester
{
public:
    virtual QMargins draggableMargins() const = 0;
    virtual QMargins maximizedMargins() const = 0;

    virtual bool hitTest(const QPoint &pos) const = 0;
};

class NativeWindowHelperPrivate;

class NativeWindowHelper : public QObject
{
    Q_OBJECT
public:
    NativeWindowHelper(QWindow *window, NativeWindowTester *tester);
    explicit NativeWindowHelper(QWindow *window);
    ~NativeWindowHelper();

    bool isCompositionEnabled(void) const;
    bool extendFrameIntoClientArea(WId winId, const QMargins &margins) const;

public:
    bool nativeEventFilter(void *msg, qintptr *result);

protected:
    bool eventFilter(QObject *obj, QEvent *ev) final;

protected:
    QScopedPointer<NativeWindowHelperPrivate> d_ptr;

signals:
    void scaleFactorChanged(qreal factor);

public:
    qreal scaleFactor() const;

private:
    Q_DECLARE_PRIVATE(NativeWindowHelper)
};

#endif  // NATIVEWINDOWHELPER_H
