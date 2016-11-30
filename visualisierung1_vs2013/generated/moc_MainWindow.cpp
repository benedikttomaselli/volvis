/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "openFileAction"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "closeAction"
QT_MOC_LITERAL(4, 39, 13), // "invertClicked"
QT_MOC_LITERAL(5, 53, 10), // "MIPClicked"
QT_MOC_LITERAL(6, 64, 9), // "ACClicked"
QT_MOC_LITERAL(7, 74, 9), // "FHClicked"
QT_MOC_LITERAL(8, 84, 11), // "stepChanged"
QT_MOC_LITERAL(9, 96, 10), // "TOPClicked"
QT_MOC_LITERAL(10, 107, 11), // "SIDEClicked"
QT_MOC_LITERAL(11, 119, 12), // "FRONTClicked"
QT_MOC_LITERAL(12, 132, 13), // "threshChanged"
QT_MOC_LITERAL(13, 146, 14), // "shadingClicked"
QT_MOC_LITERAL(14, 161, 16), // "intensityChanged"
QT_MOC_LITERAL(15, 178, 14) // "ambientChanged"

    },
    "MainWindow\0openFileAction\0\0closeAction\0"
    "invertClicked\0MIPClicked\0ACClicked\0"
    "FHClicked\0stepChanged\0TOPClicked\0"
    "SIDEClicked\0FRONTClicked\0threshChanged\0"
    "shadingClicked\0intensityChanged\0"
    "ambientChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x09 /* Protected */,
       3,    0,   85,    2, 0x09 /* Protected */,
       4,    0,   86,    2, 0x09 /* Protected */,
       5,    0,   87,    2, 0x09 /* Protected */,
       6,    0,   88,    2, 0x09 /* Protected */,
       7,    0,   89,    2, 0x09 /* Protected */,
       8,    0,   90,    2, 0x09 /* Protected */,
       9,    0,   91,    2, 0x09 /* Protected */,
      10,    0,   92,    2, 0x09 /* Protected */,
      11,    0,   93,    2, 0x09 /* Protected */,
      12,    0,   94,    2, 0x09 /* Protected */,
      13,    0,   95,    2, 0x09 /* Protected */,
      14,    0,   96,    2, 0x09 /* Protected */,
      15,    0,   97,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFileAction(); break;
        case 1: _t->closeAction(); break;
        case 2: _t->invertClicked(); break;
        case 3: _t->MIPClicked(); break;
        case 4: _t->ACClicked(); break;
        case 5: _t->FHClicked(); break;
        case 6: _t->stepChanged(); break;
        case 7: _t->TOPClicked(); break;
        case 8: _t->SIDEClicked(); break;
        case 9: _t->FRONTClicked(); break;
        case 10: _t->threshChanged(); break;
        case 11: _t->shadingClicked(); break;
        case 12: _t->intensityChanged(); break;
        case 13: _t->ambientChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
