/****************************************************************************
** Meta object code from reading C++ file 'mythread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mythread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mythread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mythread_t {
    QByteArrayData data[15];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mythread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mythread_t qt_meta_stringdata_mythread = {
    {
QT_MOC_LITERAL(0, 0, 8), // "mythread"
QT_MOC_LITERAL(1, 9, 5), // "error"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 23), // "QTcpSocket::SocketError"
QT_MOC_LITERAL(4, 40, 11), // "socketerror"
QT_MOC_LITERAL(5, 52, 11), // "sendprogbar"
QT_MOC_LITERAL(6, 64, 10), // "sendfinish"
QT_MOC_LITERAL(7, 75, 9), // "sendstart"
QT_MOC_LITERAL(8, 85, 7), // "sendLog"
QT_MOC_LITERAL(9, 93, 16), // "getFlag_mythread"
QT_MOC_LITERAL(10, 110, 12), // "disconnected"
QT_MOC_LITERAL(11, 123, 16), // "getrestartserver"
QT_MOC_LITERAL(12, 140, 4), // "getZ"
QT_MOC_LITERAL(13, 145, 9), // "sockReady"
QT_MOC_LITERAL(14, 155, 11) // "getcurrentX"

    },
    "mythread\0error\0\0QTcpSocket::SocketError\0"
    "socketerror\0sendprogbar\0sendfinish\0"
    "sendstart\0sendLog\0getFlag_mythread\0"
    "disconnected\0getrestartserver\0getZ\0"
    "sockReady\0getcurrentX"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mythread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    1,   72,    2, 0x06 /* Public */,
       6,    0,   75,    2, 0x06 /* Public */,
       7,    0,   76,    2, 0x06 /* Public */,
       8,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   80,    2, 0x0a /* Public */,
      10,    0,   81,    2, 0x0a /* Public */,
      11,    0,   82,    2, 0x0a /* Public */,
      12,    1,   83,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    1,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void mythread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mythread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QTcpSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->sendprogbar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sendfinish(); break;
        case 3: _t->sendstart(); break;
        case 4: _t->sendLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->getFlag_mythread(); break;
        case 6: _t->disconnected(); break;
        case 7: _t->getrestartserver(); break;
        case 8: _t->getZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->sockReady(); break;
        case 10: _t->getcurrentX((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (mythread::*)(QTcpSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mythread::error)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (mythread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mythread::sendprogbar)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (mythread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mythread::sendfinish)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (mythread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mythread::sendstart)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (mythread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mythread::sendLog)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mythread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_mythread.data,
    qt_meta_data_mythread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mythread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mythread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mythread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int mythread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void mythread::error(QTcpSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mythread::sendprogbar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void mythread::sendfinish()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void mythread::sendstart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void mythread::sendLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
