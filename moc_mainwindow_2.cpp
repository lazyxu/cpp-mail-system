/****************************************************************************
** Meta object code from reading C++ file 'mainwindow_2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow_2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow_2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_2_t {
    QByteArrayData data[11];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_2_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_2_t qt_meta_stringdata_MainWindow_2 = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 10),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 11),
QT_MOC_LITERAL(4, 37, 10),
QT_MOC_LITERAL(5, 48, 11),
QT_MOC_LITERAL(6, 60, 8),
QT_MOC_LITERAL(7, 69, 4),
QT_MOC_LITERAL(8, 74, 7),
QT_MOC_LITERAL(9, 82, 9),
QT_MOC_LITERAL(10, 92, 11)
    },
    "MainWindow_2\0sWriteMail\0\0std::string\0"
    "strAccount\0strPassword\0bIsDebug\0init\0"
    "revMail\0writeMail\0showRevMail\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow_2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       7,    3,   46,    2, 0x08,
       8,    0,   53,    2, 0x08,
       9,    0,   54,    2, 0x08,
      10,    0,   55,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Bool,    4,    5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Bool,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow_2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow_2 *_t = static_cast<MainWindow_2 *>(_o);
        switch (_id) {
        case 0: _t->sWriteMail((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->init((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->revMail(); break;
        case 3: _t->writeMail(); break;
        case 4: _t->showRevMail(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow_2::*_t)(std::string , std::string , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow_2::sWriteMail)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MainWindow_2::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow_2.data,
      qt_meta_data_MainWindow_2,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow_2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow_2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow_2.stringdata))
        return static_cast<void*>(const_cast< MainWindow_2*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow_2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MainWindow_2::sWriteMail(std::string _t1, std::string _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
