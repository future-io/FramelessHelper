#ifndef JWINDWMAPI_H
#define JWINDWMAPI_H

#include <QMargins>
#include <qwindowdefs.h>

// - private pointer
#ifndef J_DECLARE_PRIVATE
#define J_DECLARE_PRIVATE(Class) \
    friend class Class##Private; \
    inline Class##Private *d_func(void) \
    { \
        return reinterpret_cast<Class##Private *>(d_ptr_); \
    } \
    inline const Class##Private *d_func(void) const \
    { \
        return reinterpret_cast<const Class##Private *>(d_ptr_); \
    } \
    Class##Private *d_ptr_;
#endif

#ifndef J_DECLARE_PUBLIC
#define J_DECLARE_PUBLIC(Class) \
    friend class Class; \
    inline Class *q_func(void) \
    { \
        return static_cast<Class *>(q_ptr_); \
    } \
    inline const Class *q_func(void) const \
    { \
        return static_cast<const Class *>(q_ptr_); \
    } \
    Class *q_ptr_;
#endif

#ifndef J_DPTR
#define J_DPTR d_ptr_
#endif

#ifndef J_QPTR
#define J_QPTR q_ptr_
#endif

class JWinDwmapiPrivate;

class JWinDwmapi
{
public:
    JWinDwmapi(void);
    virtual ~JWinDwmapi(void);

    bool isCompositionEnabled(void) const;
    bool extendFrameIntoClientArea(WId winId, const QMargins &margins) const;

private:
    Q_DISABLE_COPY(JWinDwmapi)
    J_DECLARE_PRIVATE(JWinDwmapi)
};

#endif  // JWINDWMAPI_H
