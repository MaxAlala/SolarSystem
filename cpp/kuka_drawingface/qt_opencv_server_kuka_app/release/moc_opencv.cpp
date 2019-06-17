/****************************************************************************
** Meta object code from reading C++ file 'opencv.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../opencv.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'opencv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_opencv_t {
    QByteArrayData data[17];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_opencv_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_opencv_t qt_meta_stringdata_opencv = {
    {
QT_MOC_LITERAL(0, 0, 6), // "opencv"
QT_MOC_LITERAL(1, 7, 7), // "sendImg"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 8), // "sendQImg"
QT_MOC_LITERAL(4, 25, 8), // "finished"
QT_MOC_LITERAL(5, 34, 5), // "error"
QT_MOC_LITERAL(6, 40, 3), // "err"
QT_MOC_LITERAL(7, 44, 12), // "sendPortrait"
QT_MOC_LITERAL(8, 57, 8), // "sendLog2"
QT_MOC_LITERAL(9, 66, 21), // "getRequestForPortrait"
QT_MOC_LITERAL(10, 88, 9), // "getFlagON"
QT_MOC_LITERAL(11, 98, 12), // "gettopborder"
QT_MOC_LITERAL(12, 111, 15), // "getbottomborder"
QT_MOC_LITERAL(13, 127, 9), // "getregime"
QT_MOC_LITERAL(14, 137, 7), // "getijxy"
QT_MOC_LITERAL(15, 145, 11), // "getcurrentX"
QT_MOC_LITERAL(16, 157, 13) // "getlenaattach"

    },
    "opencv\0sendImg\0\0sendQImg\0finished\0"
    "error\0err\0sendPortrait\0sendLog2\0"
    "getRequestForPortrait\0getFlagON\0"
    "gettopborder\0getbottomborder\0getregime\0"
    "getijxy\0getcurrentX\0getlenaattach"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_opencv[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       3,    1,   87,    2, 0x06 /* Public */,
       4,    0,   90,    2, 0x06 /* Public */,
       5,    1,   91,    2, 0x06 /* Public */,
       7,    1,   94,    2, 0x06 /* Public */,
       8,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  100,    2, 0x0a /* Public */,
      10,    0,  101,    2, 0x0a /* Public */,
      11,    1,  102,    2, 0x0a /* Public */,
      12,    1,  105,    2, 0x0a /* Public */,
      13,    1,  108,    2, 0x0a /* Public */,
      14,    2,  111,    2, 0x0a /* Public */,
      15,    1,  116,    2, 0x0a /* Public */,
      16,    1,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void opencv::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<opencv *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendImg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendQImg((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 2: _t->finished(); break;
        case 3: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sendPortrait((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 5: _t->sendLog2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->getRequestForPortrait(); break;
        case 7: _t->getFlagON(); break;
        case 8: _t->gettopborder((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->getbottomborder((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->getregime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->getijxy((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->getcurrentX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->getlenaattach((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (opencv::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&opencv::sendImg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (opencv::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&opencv::sendQImg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (opencv::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&opencv::finished)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (opencv::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&opencv::error)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (opencv::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&opencv::sendPortrait)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (opencv::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&opencv::sendLog2)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject opencv::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_opencv.data,
    qt_meta_data_opencv,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *opencv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *opencv::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_opencv.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int opencv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void opencv::sendImg(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void opencv::sendQImg(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void opencv::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void opencv::error(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void opencv::sendPortrait(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void opencv::sendLog2(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
