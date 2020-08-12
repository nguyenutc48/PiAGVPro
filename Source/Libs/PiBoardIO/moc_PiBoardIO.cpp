/****************************************************************************
** Meta object code from reading C++ file 'PiBoardIO.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "PiBoardIO.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PiBoardIO.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PIBoardIO_t {
    QByteArrayData data[13];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PIBoardIO_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PIBoardIO_t qt_meta_stringdata_PIBoardIO = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PIBoardIO"
QT_MOC_LITERAL(1, 10, 8), // "xChanged"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "yChanged"
QT_MOC_LITERAL(4, 29, 12), // "stateChanged"
QT_MOC_LITERAL(5, 42, 10), // "logChanged"
QT_MOC_LITERAL(6, 53, 9), // "StartScan"
QT_MOC_LITERAL(7, 63, 8), // "StopScan"
QT_MOC_LITERAL(8, 72, 1), // "x"
QT_MOC_LITERAL(9, 74, 13), // "QVector<bool>"
QT_MOC_LITERAL(10, 88, 1), // "y"
QT_MOC_LITERAL(11, 90, 5), // "state"
QT_MOC_LITERAL(12, 96, 3) // "log"

    },
    "PIBoardIO\0xChanged\0\0yChanged\0stateChanged\0"
    "logChanged\0StartScan\0StopScan\0x\0"
    "QVector<bool>\0y\0state\0log"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PIBoardIO[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       4,   58, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,
       4,    1,   50,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   56,    2, 0x0a /* Public */,
       7,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, 0x80000000 | 9, 0x0049510b,
      10, 0x80000000 | 9, 0x0049510b,
      11, QMetaType::Int, 0x00495103,
      12, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void PIBoardIO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PIBoardIO *_t = static_cast<PIBoardIO *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->xChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->logChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->StartScan(); break;
        case 5: _t->StopScan(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PIBoardIO::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIBoardIO::xChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PIBoardIO::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIBoardIO::yChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PIBoardIO::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIBoardIO::stateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PIBoardIO::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PIBoardIO::logChanged)) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<bool> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        PIBoardIO *_t = static_cast<PIBoardIO *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVector<bool>*>(_v) = _t->x(); break;
        case 1: *reinterpret_cast< QVector<bool>*>(_v) = _t->y(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->state(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->log(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        PIBoardIO *_t = static_cast<PIBoardIO *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setX(*reinterpret_cast< QVector<bool>*>(_v)); break;
        case 1: _t->setY(*reinterpret_cast< QVector<bool>*>(_v)); break;
        case 2: _t->setState(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setLog(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PIBoardIO::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PIBoardIO.data,
      qt_meta_data_PIBoardIO,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PIBoardIO::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PIBoardIO::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PIBoardIO.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int PIBoardIO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PIBoardIO::xChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PIBoardIO::yChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PIBoardIO::stateChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PIBoardIO::logChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
