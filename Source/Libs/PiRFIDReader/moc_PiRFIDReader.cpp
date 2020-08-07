/****************************************************************************
** Meta object code from reading C++ file 'PiRFIDReader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "PiRFIDReader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PiRFIDReader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PiRFIDReader_t {
    QByteArrayData data[12];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PiRFIDReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PiRFIDReader_t qt_meta_stringdata_PiRFIDReader = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PiRFIDReader"
QT_MOC_LITERAL(1, 13, 12), // "stateChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 10), // "logChanged"
QT_MOC_LITERAL(4, 38, 15), // "dataCardChanged"
QT_MOC_LITERAL(5, 54, 11), // "ReaderStart"
QT_MOC_LITERAL(6, 66, 10), // "ReaderStop"
QT_MOC_LITERAL(7, 77, 8), // "readData"
QT_MOC_LITERAL(8, 86, 12), // "timer_update"
QT_MOC_LITERAL(9, 99, 5), // "state"
QT_MOC_LITERAL(10, 105, 3), // "log"
QT_MOC_LITERAL(11, 109, 8) // "dataCard"

    },
    "PiRFIDReader\0stateChanged\0\0logChanged\0"
    "dataCardChanged\0ReaderStart\0ReaderStop\0"
    "readData\0timer_update\0state\0log\0"
    "dataCard"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PiRFIDReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       3,   62, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::Int, 0x00495103,
      10, QMetaType::QString, 0x00495103,
      11, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void PiRFIDReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PiRFIDReader *_t = static_cast<PiRFIDReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->logChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->dataCardChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ReaderStart(); break;
        case 4: _t->ReaderStop(); break;
        case 5: _t->readData(); break;
        case 6: _t->timer_update(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PiRFIDReader::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PiRFIDReader::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PiRFIDReader::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PiRFIDReader::logChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PiRFIDReader::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PiRFIDReader::dataCardChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        PiRFIDReader *_t = static_cast<PiRFIDReader *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->state(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->log(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->dataCard(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        PiRFIDReader *_t = static_cast<PiRFIDReader *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setState(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setLog(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setDataCard(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject PiRFIDReader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PiRFIDReader.data,
      qt_meta_data_PiRFIDReader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PiRFIDReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PiRFIDReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PiRFIDReader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PiRFIDReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PiRFIDReader::stateChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PiRFIDReader::logChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PiRFIDReader::dataCardChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
