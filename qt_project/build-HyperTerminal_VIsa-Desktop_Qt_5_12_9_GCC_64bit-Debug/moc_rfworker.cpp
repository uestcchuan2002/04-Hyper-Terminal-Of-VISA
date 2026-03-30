/****************************************************************************
** Meta object code from reading C++ file 'rfworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HyperTerminal_VIsa/rfworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rfworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RFWorker_t {
    QByteArrayData data[18];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RFWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RFWorker_t qt_meta_stringdata_RFWorker = {
    {
QT_MOC_LITERAL(0, 0, 8), // "RFWorker"
QT_MOC_LITERAL(1, 9, 5), // "rfLog"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 3), // "msg"
QT_MOC_LITERAL(4, 20, 7), // "rfError"
QT_MOC_LITERAL(5, 28, 14), // "connectSuccess"
QT_MOC_LITERAL(6, 43, 9), // "connected"
QT_MOC_LITERAL(7, 53, 13), // "connectDevice"
QT_MOC_LITERAL(8, 67, 4), // "addr"
QT_MOC_LITERAL(9, 72, 16), // "disconnectDevice"
QT_MOC_LITERAL(10, 89, 8), // "writeCmd"
QT_MOC_LITERAL(11, 98, 3), // "cmd"
QT_MOC_LITERAL(12, 102, 7), // "readCmd"
QT_MOC_LITERAL(13, 110, 6), // "output"
QT_MOC_LITERAL(14, 117, 2), // "on"
QT_MOC_LITERAL(15, 120, 6), // "config"
QT_MOC_LITERAL(16, 127, 4), // "freq"
QT_MOC_LITERAL(17, 132, 5) // "power"

    },
    "RFWorker\0rfLog\0\0msg\0rfError\0connectSuccess\0"
    "connected\0connectDevice\0addr\0"
    "disconnectDevice\0writeCmd\0cmd\0readCmd\0"
    "output\0on\0config\0freq\0power"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RFWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   68,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    1,   72,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,
      13,    1,   76,    2, 0x0a /* Public */,
      15,    2,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   16,   17,

       0        // eod
};

void RFWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RFWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rfLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->rfError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->connectSuccess((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->connectDevice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->disconnectDevice(); break;
        case 5: _t->writeCmd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->readCmd(); break;
        case 7: _t->output((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->config((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RFWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RFWorker::rfLog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RFWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RFWorker::rfError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RFWorker::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RFWorker::connectSuccess)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RFWorker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_RFWorker.data,
    qt_meta_data_RFWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RFWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RFWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RFWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RFWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void RFWorker::rfLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RFWorker::rfError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RFWorker::connectSuccess(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
