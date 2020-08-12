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
    QByteArrayData data[9];
    char stringdata0[66];
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
QT_MOC_LITERAL(4, 29, 9), // "StartScan"
QT_MOC_LITERAL(5, 39, 8), // "StopScan"
QT_MOC_LITERAL(6, 48, 1), // "x"
QT_MOC_LITERAL(7, 50, 13), // "QVector<bool>"
QT_MOC_LITERAL(8, 64, 1) // "y"

    },
    "PIBoardIO\0xChanged\0\0yChanged\0StartScan\0"
    "StopScan\0x\0QVector<bool>\0y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PIBoardIO[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   42, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   40,    2, 0x0a /* Public */,
       5,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       6, 0x80000000 | 7, 0x0049510b,
       8, 0x80000000 | 7, 0x0049510b,

 // properties: notify_signal_id
       0,
       1,

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
        case 2: _t->StartScan(); break;
        case 3: _t->StopScan(); break;
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
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        PIBoardIO *_t = static_cast<PIBoardIO *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setX(*reinterpret_cast< QVector<bool>*>(_v)); break;
        case 1: _t->setY(*reinterpret_cast< QVector<bool>*>(_v)); break;
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
