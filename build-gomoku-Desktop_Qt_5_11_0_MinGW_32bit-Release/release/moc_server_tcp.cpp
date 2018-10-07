/****************************************************************************
** Meta object code from reading C++ file 'server_tcp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gomoku/server_tcp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server_tcp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_server_tcp_t {
    QByteArrayData data[16];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_server_tcp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_server_tcp_t qt_meta_stringdata_server_tcp = {
    {
QT_MOC_LITERAL(0, 0, 10), // "server_tcp"
QT_MOC_LITERAL(1, 11, 15), // "connectionbuild"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "newgame"
QT_MOC_LITERAL(4, 36, 12), // "player1_down"
QT_MOC_LITERAL(5, 49, 1), // "x"
QT_MOC_LITERAL(6, 51, 1), // "y"
QT_MOC_LITERAL(7, 53, 6), // "player"
QT_MOC_LITERAL(8, 60, 15), // "display_message"
QT_MOC_LITERAL(9, 76, 7), // "message"
QT_MOC_LITERAL(10, 84, 14), // "disconnecttion"
QT_MOC_LITERAL(11, 99, 16), // "acceptConnection"
QT_MOC_LITERAL(12, 116, 5), // "close"
QT_MOC_LITERAL(13, 122, 9), // "send_data"
QT_MOC_LITERAL(14, 132, 9), // "read_data"
QT_MOC_LITERAL(15, 142, 12) // "chat_message"

    },
    "server_tcp\0connectionbuild\0\0newgame\0"
    "player1_down\0x\0y\0player\0display_message\0"
    "message\0disconnecttion\0acceptConnection\0"
    "close\0send_data\0read_data\0chat_message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_server_tcp[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    3,   66,    2, 0x06 /* Public */,
       8,    1,   73,    2, 0x06 /* Public */,
      10,    0,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   77,    2, 0x0a /* Public */,
      12,    0,   78,    2, 0x0a /* Public */,
      13,    3,   79,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x0a /* Public */,
      15,    1,   87,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void server_tcp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        server_tcp *_t = static_cast<server_tcp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectionbuild(); break;
        case 1: _t->newgame(); break;
        case 2: _t->player1_down((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->display_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->disconnecttion(); break;
        case 5: _t->acceptConnection(); break;
        case 6: _t->close(); break;
        case 7: _t->send_data((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->read_data(); break;
        case 9: _t->chat_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (server_tcp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server_tcp::connectionbuild)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (server_tcp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server_tcp::newgame)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (server_tcp::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server_tcp::player1_down)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (server_tcp::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server_tcp::display_message)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (server_tcp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&server_tcp::disconnecttion)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject server_tcp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_server_tcp.data,
      qt_meta_data_server_tcp,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *server_tcp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *server_tcp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_server_tcp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int server_tcp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void server_tcp::connectionbuild()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void server_tcp::newgame()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void server_tcp::player1_down(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void server_tcp::display_message(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void server_tcp::disconnecttion()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
