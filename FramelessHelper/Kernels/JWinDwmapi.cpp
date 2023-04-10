#include "JWinDwmapi.h"
#ifdef Q_OS_WIN32
#include <Windows.h>
//
#include <Uxtheme.h>
#endif

// class JWinDwmapiPrivate

class JWinDwmapiPrivate
{
public:
    JWinDwmapiPrivate(void)
        : dwmapiDll(nullptr)
        , funcDwmIsCompositionEnabled(nullptr)
        , funcDwmExtendFrameIntoClientArea(nullptr)
    {
        dwmapiDll = ::LoadLibraryA("dwmapi.dll");
    }

    virtual ~JWinDwmapiPrivate(void)
    {
        if (dwmapiDll) {
            ::FreeLibrary(dwmapiDll);
        }
    }

    void init(void);

private:
    Q_DISABLE_COPY(JWinDwmapiPrivate)
    friend class JWinDwmapi;
    typedef HRESULT(WINAPI *FuncDwmIsCompositionEnabled)(BOOL *pfEnabled);
    typedef HRESULT(WINAPI *FuncDwmExtendFrameIntoClientArea)(HWND hWnd, const MARGINS *pMarInset);
    HMODULE dwmapiDll;
    FuncDwmIsCompositionEnabled funcDwmIsCompositionEnabled;
    FuncDwmExtendFrameIntoClientArea funcDwmExtendFrameIntoClientArea;
};

void JWinDwmapiPrivate::init(void)
{
    if (dwmapiDll) {
        funcDwmIsCompositionEnabled = reinterpret_cast<FuncDwmIsCompositionEnabled>(
            ::GetProcAddress(dwmapiDll, "DwmIsCompositionEnabled"));
        funcDwmExtendFrameIntoClientArea = reinterpret_cast<FuncDwmExtendFrameIntoClientArea>(
            GetProcAddress(dwmapiDll, "DwmExtendFrameIntoClientArea"));
    }
}

// class JWinDwmapi

JWinDwmapi::JWinDwmapi(void)
    : d_ptr_(new JWinDwmapiPrivate())
{
    Q_D(JWinDwmapi);
    d->init();
}

JWinDwmapi::~JWinDwmapi(void)
{
    Q_D(JWinDwmapi);
    delete d;
}

bool JWinDwmapi::isCompositionEnabled(void) const
{
    Q_D(const JWinDwmapi);
    if (d->funcDwmIsCompositionEnabled) {
        BOOL enabled = FALSE;
        if (SUCCEEDED(d->funcDwmIsCompositionEnabled(&enabled))) {
            return (enabled == TRUE);
        }
    }

    return false;
}

bool JWinDwmapi::extendFrameIntoClientArea(WId winId, const QMargins &margins) const
{
    Q_D(const JWinDwmapi);
    if (d->funcDwmExtendFrameIntoClientArea) {
        MARGINS _margins;
        _margins.cxLeftWidth = margins.left();
        _margins.cxRightWidth = margins.right();
        _margins.cyTopHeight = margins.top();
        _margins.cyBottomHeight = margins.bottom();
        if (SUCCEEDED(d->funcDwmExtendFrameIntoClientArea(HWND(winId), &_margins))) {
            return true;
        }
    }

    return false;
}
