#include <Windows.h>
#include <dwmapi.h>

long GetHandleFromTitle(char *title)
{
    HWND handle = FindWindowA(NULL, title);
    if (handle == NULL || handle == INVALID_HANDLE_VALUE) {
        return -1;
    }
    return handle;
}

int ShowMessageBox(const char* msg, const char* title, unsigned int buttons)
{
    return MessageBoxA(NULL, msg, title, buttons);
}

int ShowMessageBoxHandle(long handle, const char* msg, const char* title, unsigned int buttons)
{
    return MessageBoxA(handle, msg, title, buttons);
}

int ForceDarkTitleBar(HWND handle)
{
    BOOL val = TRUE;
    HRESULT res = DwmSetWindowAttribute(handle, DWMWA_USE_IMMERSIVE_DARK_MODE, &val, sizeof(val));

    if (res != S_OK) {
        return 1;
    }

    return 0;
}