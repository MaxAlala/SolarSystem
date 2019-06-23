/****************************************************************************
** Meta object code from reading C++ file 'serverproxy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serverproxy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverproxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_serverproxy_t {
    QByteArrayData data[18];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serverproxy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serverproxy_t qt_meta_stringdata_serverproxy = {
    {
QT_MOC_LITERAL(0, 0, 11), // "serverproxy"
QT_MOC_LITERAL(1, 12, 5), // "sendZ"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 11), // "sendprogbar"
QT_MOC_LITERAL(4, 31, 10), // "sendfinish"
QT_MOC_LITERAL(5, 42, 9), // "sendstart"
QT_MOC_LITERAL(6, 52, 17), // "sendFlag_mythread"
QT_MOC_LITERAL(7, 70, 7), // "sendLog"
QT_MOC_LITERAL(8, 78, 17), // "sendrestartserver"
QT_MOC_LITERAL(9, 96, 12), // "sendcurrentX"
QT_MOC_LITERAL(10, 109, 11), // "getcurrentX"
QT_MOC_LITERAL(11, 121, 4), // "getZ"
QT_MOC_LITERAL(12, 126, 10), // "getprogbar"
QT_MOC_LITERAL(13, 137, 8), // "getstart"
QT_MOC_LITERAL(14, 146, 9), // "getfinish"
QT_MOC_LITERAL(15, 156, 16), // "getFlag_mythread"
QT_MOC_LITERAL(16, 173, 6), // "getLog"
QT_MOC_LITERAL(17, 180, 16) // "getrestartserver"

    },
    "serverproxy\0sendZ\0\0sendprogbar\0"
    "sendfinish\0sendstart\0sendFlag_mythread\0"
    "sendLog\0sendrestartserver\0sendcurrentX\0"
    "getcurrentX\0getZ\0getprogbar\0getstart\0"
    "getfinish\0getFlag_mythread\0getLog\0"
    "getrestartserver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serverproxy[] = {

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
       3,    1,   97,    2, 0x06 /* Public */,
       4,    0,  100,    2, 0x06 /* Public */,
       5,    0,  101,    2, 0x06 /* Public */,
       6,    0,  102,    2, 0x06 /* Public */,
       7,    1,  103,    2, 0x06 /* Public */,
       8,    0,  106,    2, 0x06 /* Public */,
       9,    1,  107,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  110,    2, 0x0a /* Public */,
      11,    1,  113,    2, 0x0a /* Public */,
      12,    1,  116,    2, 0x0a /* Public */,
      13,    0,  119,    2, 0x0a /* Public */,
      14,    0,  120,    2, 0x0a /* Public */,
      15,    0,  121,    2, 0x0a /* Public */,
      16,    1,  122,    2, 0x0a /* Public */,
      17,    0,  125,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void serverproxy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<serverproxy *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendprogbar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sendfinish(); break;
        case 3: _t->sendstart(); break;
        case 4: _t->sendFlag_mythread(); break;
        case 5: _t->sendLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sendrestartserver(); break;
        case 7: _t->sendcurrentX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->getcurrentX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->getZ((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->getprogbar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->getstart(); break;
        case 12: _t->getfinish(); break;
        case 13: _t->getFlag_mythread(); break;
        case 14: _t->getLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->getrestartserver(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (serverproxy::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverproxy::sendZ)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (serverproxy::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverproxy::sendprogbar)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (serverproxy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverproxy::sendfinish)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (serverproxy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverproxy::sendstart)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (serverproxy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverproxy::sendFlag_mythread)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (serverproxy::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverproxy::sendLog)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (serverproxy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverproxy::sendrestartserver)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (serverproxy::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serverproxy::sendcurrentX)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject serverproxy::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_serverproxy.data,
    qt_meta_data_serverproxy,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *serverproxy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serverproxy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_serverproxy.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int serverproxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void serverproxy::sendZ(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void serverproxy::sendprogbar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void serverproxy::sendfinish()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void serverproxy::sendstart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void serverproxy::sendFlag_mythread()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void serverproxy::sendLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void serverproxy::sendrestartserver()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void serverproxy::sendcurrentX(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
