/****************************************************************************
** Meta object code from reading C++ file 'sigworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HyperTerminal_VIsa/sigworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sigworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SigWorker_t {
    QByteArrayData data[20];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SigWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SigWorker_t qt_meta_stringdata_SigWorker = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SigWorker"
QT_MOC_LITERAL(1, 10, 6), // "sigLog"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 3), // "msg"
QT_MOC_LITERAL(4, 22, 8), // "sigError"
QT_MOC_LITERAL(5, 31, 14), // "connectSuccess"
QT_MOC_LITERAL(6, 46, 9), // "connected"
QT_MOC_LITERAL(7, 56, 13), // "connectDevice"
QT_MOC_LITERAL(8, 70, 4), // "addr"
QT_MOC_LITERAL(9, 75, 8), // "writeCmd"
QT_MOC_LITERAL(10, 84, 3), // "cmd"
QT_MOC_LITERAL(11, 88, 7), // "readCmd"
QT_MOC_LITERAL(12, 96, 16), // "disconnectDevice"
QT_MOC_LITERAL(13, 113, 12), // "downloadWave"
QT_MOC_LITERAL(14, 126, 12), // "QVector<int>"
QT_MOC_LITERAL(15, 139, 6), // "points"
QT_MOC_LITERAL(16, 146, 7), // "channel"
QT_MOC_LITERAL(17, 154, 4), // "freq"
QT_MOC_LITERAL(18, 159, 3), // "vpp"
QT_MOC_LITERAL(19, 163, 6) // "offset"

    },
    "SigWorker\0sigLog\0\0msg\0sigError\0"
    "connectSuccess\0connected\0connectDevice\0"
    "addr\0writeCmd\0cmd\0readCmd\0disconnectDevice\0"
    "downloadWave\0QVector<int>\0points\0"
    "channel\0freq\0vpp\0offset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SigWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   63,    2, 0x0a /* Public */,
       9,    1,   66,    2, 0x0a /* Public */,
      11,    0,   69,    2, 0x0a /* Public */,
      12,    0,   70,    2, 0x0a /* Public */,
      13,    5,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double,   15,   16,   17,   18,   19,

       0        // eod
};

void SigWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SigWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->connectSuccess((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->connectDevice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->writeCmd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->readCmd(); break;
        case 6: _t->disconnectDevice(); break;
        case 7: _t->downloadWave((*reinterpret_cast< QVector<int>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SigWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SigWorker::sigLog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SigWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SigWorker::sigError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SigWorker::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SigWorker::connectSuccess)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SigWorker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SigWorker.data,
    qt_meta_data_SigWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SigWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SigWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SigWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SigWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SigWorker::sigLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SigWorker::sigError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SigWorker::connectSuccess(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
