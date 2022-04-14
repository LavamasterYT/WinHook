#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <winhook.h>

static PyObject *
WinHook_ShowMessageBox(PyObject *self, PyObject *args)
{
    const char* msg;
    const char* title;
    
    if (!PyArg_ParseTuple(args, "zz", &msg, &title)) {
        return NULL;
    }

    if (msg == NULL ||
        title == NULL) {
        PyErr_SetString(PyExc_SyntaxError, "No values defined in arguments.");
    }

    ShowMessageBox(msg, title, MB_OK | MB_ICONINFORMATION);

    Py_RETURN_NONE;
}

static PyObject *
WinHook_GetWindowHandle(PyObject *self, PyObject *args)
{
    const char* title;

    if (!PyArg_ParseTuple(args, "z", &title)) {
        return NULL;
    }

    if (title == NULL) {
        PyErr_SetString(PyExc_SyntaxError, "No values defined in arguments.");
    }

    long res = GetHandleFromTitle(title);

    if (res == -1) {
        PyErr_SetString(PyExc_OSError, "Unable to get handle from title.");
        return NULL;
    }

    return PyLong_FromLong(res);
}

static PyObject *
WinHook_ForceDarkTitleBar(PyObject *self, PyObject *args)
{
    const long hwnd;

    if (!PyArg_ParseTuple(args, "l", &hwnd)) {
        return NULL;
    }

    int res = ForceDarkTitleBar(hwnd);

    if (res) {
        PyErr_SetString(PyExc_OSError, "Unable to set title bar.");
        return NULL;
    }

    Py_RETURN_NONE;
}

static PyMethodDef WinHookMethods[] = {
    { "mb", WinHook_ShowMessageBox, METH_VARARGS, "A rudementary message box function, just for testing." },
    { "getwindowhandle", WinHook_GetWindowHandle, METH_VARARGS, "Returns the handle of the main window of a specified window title." },
    { "forcedarktitlebar", WinHook_ForceDarkTitleBar, METH_VARARGS, "Undefined." },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef WinHookModule = {
    PyModuleDef_HEAD_INIT,
    "winhook",
    "Window hooking",
    -1,
    WinHookMethods
};

PyObject* 
PyInit_winhook(void) {
    return PyModule_Create(&WinHookModule);
}