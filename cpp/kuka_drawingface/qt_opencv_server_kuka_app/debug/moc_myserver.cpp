/****************************************************************************
** Meta object code from reading C++ file 'myserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../myserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myserver_t {
    QByteArrayData data[18];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myserver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myserver_t qt_meta_stringdata_myserver = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myserver"
QT_MOC_LITERAL(1, 9, 11), // "sendprogbar"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10), // "sendfinish"
QT_MOC_LITERAL(4, 33, 9), // "sendstart"
QT_MOC_LITERAL(5, 43, 17), // "sendFlag_mythread"
QT_MOC_LITERAL(6, 61, 7), // "sendLog"
QT_MOC_LITERAL(7, 69, 17), // "sendrestartserver"
QT_MOC_LITERAL(8, 87, 5), // "sendZ"
QT_MOC_LITERAL(9, 93, 12), // "sendcurrentX"
QT_MOC_LITERAL(10, 106, 10), // "getprogbar"
QT_MOC_LITERAL(11, 117, 8), // "getstart"
QT_MOC_LITERAL(12, 126, 9), // "getfinish"
QT_MOC_LITERAL(13, 136, 16), // "getFlag_mythread"
QT_MOC_LITERAL(14, 153, 6), // "getLog"
QT_MOC_LITERAL(15, 160, 16), // "getrestartserver"
QT_MOC_LITERAL(16, 177, 4), // "getZ"
QT_MOC_LITERAL(17, 182, 11) // "getcurrentX"

    },
    "myserver\0sendprogbar\0\0sendfinish\0"
    "sendstart\0sendFlag_mythread\0sendLog\0"
    "sendrestartserver\0sendZ\0sendcurrentX\0"
    "getprogbar\0getstart\0getfinish\0"
    "getFlag_mythread\0getLog\0getrestartserver\0"
    "getZ\0getcurrentX"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myserver[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       3,    0,   97,    2, 0x06 /* Public */,
       4,    0,   98,    2, 0x06 /* Public */,
       5,    0,   99,    2, 0x06 /* Public */,
       6,    1,  100,    2, 0x06 /* Public */,
       7,    0,  103,    2, 0x06 /* Public */,
       8,    1,  104,    2, 0x06 /* Public */,
       9,    1,  107,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  110,    2, 0x0a /* Public */,
      11,    0,  113,    2, 0x0a /* Public */,
      12,    0,  114,    2, 0x0a /* Public */,
      13,    0,  115,    2, 0x0a /* Public */,
      14,    1,  116,    2, 0x0a /* Public */,
      15,    0,  119,    2, 0x0a /* Public */,
      16,    1,  120,    2, 0x0a /* Public */,
      17,    1,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void myserver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myserver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendprogbar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sendfinish(); break;
        case 2: _t->sendstart(); break;
        case 3: _t->sendFlag_mythread(); break;
        case 4: _t->sendLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sendrestartserver(); break;
        case 6: _t->sendZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->sendcurrentX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->getprogbar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->getstart(); break;
        case 10: _t->getfinish(); break;
        case 11: _t->getFlag_mythread(); break;
        case 12: _t->getLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->getrestartserver(); break;
        case 14: _t->getZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->getcurrentX((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myserver::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myserver::sendprogbar)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (myserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myserver::sendfinish)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (myserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myserver::sendstart)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (myserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myserver::sendFlag_mythread)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (myserver::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myserver::sendLog)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (myserver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myserver::sendrestartserver)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (myserver::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myserver::sendZ)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (myserver::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myserver::sendcurrentX)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject myserver::staticMetaObject = { {
    &QTcpServer::staticMetaObject,
    qt_meta_stringdata_myserver.data,
    qt_meta_data_myserver,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *myserver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myserver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myserver.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int myserver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void myserver::sendprogbar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myserver::sendfinish()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void myserver::sendstart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void myserver::sendFlag_mythread()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void myserver::sendLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void myserver::sendrestartserver()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void myserver::sendZ(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void myserver::sendcurrentX(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
