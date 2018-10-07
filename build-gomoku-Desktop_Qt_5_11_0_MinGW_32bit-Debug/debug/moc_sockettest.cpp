/****************************************************************************
** Meta object code from reading C++ file 'sockettest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gomoku/sockettest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sockettest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sockettest_t {
    QByteArrayData data[15];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sockettest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sockettest_t qt_meta_stringdata_sockettest = {
    {
QT_MOC_LITERAL(0, 0, 10), // "sockettest"
QT_MOC_LITERAL(1, 11, 11), // "clientbuild"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "newgame"
QT_MOC_LITERAL(4, 32, 12), // "player0_down"
QT_MOC_LITERAL(5, 45, 1), // "x"
QT_MOC_LITERAL(6, 47, 1), // "y"
QT_MOC_LITERAL(7, 49, 6), // "player"
QT_MOC_LITERAL(8, 56, 15), // "display_message"
QT_MOC_LITERAL(9, 72, 7), // "message"
QT_MOC_LITERAL(10, 80, 13), // "disconnection"
QT_MOC_LITERAL(11, 94, 8), // "readdata"
QT_MOC_LITERAL(12, 103, 6), // "discon"
QT_MOC_LITERAL(13, 110, 9), // "send_data"
QT_MOC_LITERAL(14, 120, 12) // "chat_message"

    },
    "sockettest\0clientbuild\0\0newgame\0"
    "player0_down\0x\0y\0player\0display_message\0"
    "message\0disconnection\0readdata\0discon\0"
    "send_data\0chat_message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sockettest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    3,   61,    2, 0x06 /* Public */,
       8,    1,   68,    2, 0x06 /* Public */,
      10,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   72,    2, 0x0a /* Public */,
      12,    0,   73,    2, 0x0a /* Public */,
      13,    3,   74,    2, 0x0a /* Public */,
      14,    1,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void sockettest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sockettest *_t = static_cast<sockettest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clientbuild(); break;
        case 1: _t->newgame(); break;
        case 2: _t->player0_down((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->display_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->disconnection(); break;
        case 5: _t->readdata(); break;
        case 6: _t->discon(); break;
        case 7: _t->send_data((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->chat_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (sockettest::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sockettest::clientbuild)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (sockettest::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sockettest::newgame)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (sockettest::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sockettest::player0_down)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (sockettest::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sockettest::display_message)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (sockettest::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sockettest::disconnection)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sockettest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_sockettest.data,
      qt_meta_data_sockettest,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *sockettest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sockettest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sockettest.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int sockettest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void sockettest::clientbuild()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void sockettest::newgame()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void sockettest::player0_down(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void sockettest::display_message(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void sockettest::disconnection()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
