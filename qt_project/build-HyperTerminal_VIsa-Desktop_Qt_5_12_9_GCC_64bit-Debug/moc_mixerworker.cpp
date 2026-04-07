/****************************************************************************
** Meta object code from reading C++ file 'mixerworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HyperTerminal_VIsa/mixerworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mixerworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MixerWorker_t {
    QByteArrayData data[19];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MixerWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MixerWorker_t qt_meta_stringdata_MixerWorker = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MixerWorker"
QT_MOC_LITERAL(1, 12, 5), // "miLog"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "msg"
QT_MOC_LITERAL(4, 23, 7), // "miError"
QT_MOC_LITERAL(5, 31, 10), // "logMessage"
QT_MOC_LITERAL(6, 42, 12), // "portsUpdated"
QT_MOC_LITERAL(7, 55, 5), // "ports"
QT_MOC_LITERAL(8, 61, 9), // "connected"
QT_MOC_LITERAL(9, 71, 2), // "ok"
QT_MOC_LITERAL(10, 74, 9), // "scanPorts"
QT_MOC_LITERAL(11, 84, 11), // "connectPort"
QT_MOC_LITERAL(12, 96, 8), // "portName"
QT_MOC_LITERAL(13, 105, 14), // "disconnectPort"
QT_MOC_LITERAL(14, 120, 11), // "sendCommand"
QT_MOC_LITERAL(15, 132, 3), // "cmd"
QT_MOC_LITERAL(16, 136, 11), // "onReadyRead"
QT_MOC_LITERAL(17, 148, 9), // "onSetComd"
QT_MOC_LITERAL(18, 158, 3) // "num"

    },
    "MixerWorker\0miLog\0\0msg\0miError\0"
    "logMessage\0portsUpdated\0ports\0connected\0"
    "ok\0scanPorts\0connectPort\0portName\0"
    "disconnectPort\0sendCommand\0cmd\0"
    "onReadyRead\0onSetComd\0num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MixerWorker[] = {

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
       4,    1,   72,    2, 0x06 /* Public */,
       5,    1,   75,    2, 0x06 /* Public */,
       6,    1,   78,    2, 0x06 /* Public */,
       8,    1,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   84,    2, 0x0a /* Public */,
      11,    1,   85,    2, 0x0a /* Public */,
      13,    0,   88,    2, 0x0a /* Public */,
      14,    1,   89,    2, 0x0a /* Public */,
      16,    0,   92,    2, 0x0a /* Public */,
      17,    2,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QStringList,    7,
    QMetaType::Void, QMetaType::Bool,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   15,   18,

       0        // eod
};

void MixerWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MixerWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->miLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->miError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->logMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->portsUpdated((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 4: _t->connected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->scanPorts(); break;
        case 6: _t->connectPort((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->disconnectPort(); break;
        case 8: _t->sendCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->onReadyRead(); break;
        case 10: _t->onSetComd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MixerWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerWorker::miLog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MixerWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerWorker::miError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MixerWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerWorker::logMessage)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MixerWorker::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerWorker::portsUpdated)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MixerWorker::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MixerWorker::connected)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MixerWorker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MixerWorker.data,
    qt_meta_data_MixerWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MixerWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MixerWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MixerWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MixerWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MixerWorker::miLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MixerWorker::miError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MixerWorker::logMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MixerWorker::portsUpdated(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MixerWorker::connected(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
