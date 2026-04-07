/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HyperTerminal_VIsa/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[44];
    char stringdata0[633];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "sig_connect"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 14), // "sig_disconnect"
QT_MOC_LITERAL(4, 39, 9), // "sig_write"
QT_MOC_LITERAL(5, 49, 8), // "sig_read"
QT_MOC_LITERAL(6, 58, 16), // "sig_downloadWave"
QT_MOC_LITERAL(7, 75, 12), // "QVector<int>"
QT_MOC_LITERAL(8, 88, 10), // "rf_connect"
QT_MOC_LITERAL(9, 99, 13), // "rf_disconnect"
QT_MOC_LITERAL(10, 113, 8), // "rf_write"
QT_MOC_LITERAL(11, 122, 7), // "rf_read"
QT_MOC_LITERAL(12, 130, 9), // "rf_output"
QT_MOC_LITERAL(13, 140, 9), // "rf_config"
QT_MOC_LITERAL(14, 150, 12), // "sigScanPorts"
QT_MOC_LITERAL(15, 163, 15), // "sigConnectMixer"
QT_MOC_LITERAL(16, 179, 4), // "port"
QT_MOC_LITERAL(17, 184, 18), // "sigDisconnectMixer"
QT_MOC_LITERAL(18, 203, 12), // "sigSendMixer"
QT_MOC_LITERAL(19, 216, 3), // "cmd"
QT_MOC_LITERAL(20, 220, 10), // "sigSetComd"
QT_MOC_LITERAL(21, 231, 3), // "num"
QT_MOC_LITERAL(22, 235, 19), // "onSigConnectClicked"
QT_MOC_LITERAL(23, 255, 19), // "onSigConnectSuccess"
QT_MOC_LITERAL(24, 275, 9), // "connected"
QT_MOC_LITERAL(25, 285, 17), // "onSigWriteClicked"
QT_MOC_LITERAL(26, 303, 16), // "onSigReadClicked"
QT_MOC_LITERAL(27, 320, 17), // "onLoadFileClicked"
QT_MOC_LITERAL(28, 338, 21), // "onDownloadWaveClicked"
QT_MOC_LITERAL(29, 360, 18), // "onRfConnectClicked"
QT_MOC_LITERAL(30, 379, 18), // "onRfConnectSuccess"
QT_MOC_LITERAL(31, 398, 16), // "onRFWriteClicked"
QT_MOC_LITERAL(32, 415, 15), // "onRFReadClicked"
QT_MOC_LITERAL(33, 431, 19), // "onRFOutputOnClicked"
QT_MOC_LITERAL(34, 451, 20), // "onRFOutputOffClicked"
QT_MOC_LITERAL(35, 472, 17), // "onRFConfigClicked"
QT_MOC_LITERAL(36, 490, 14), // "onPortsUpdated"
QT_MOC_LITERAL(37, 505, 5), // "ports"
QT_MOC_LITERAL(38, 511, 22), // "onMixBtnConnectClicked"
QT_MOC_LITERAL(39, 534, 22), // "onMixBtnSetFreqClicked"
QT_MOC_LITERAL(40, 557, 22), // "onMixBtnSetDownClicked"
QT_MOC_LITERAL(41, 580, 20), // "onMixBtnSetUpClicked"
QT_MOC_LITERAL(42, 601, 19), // "onMixBtnSendClicked"
QT_MOC_LITERAL(43, 621, 11) // "closeVisaRF"

    },
    "MainWindow\0sig_connect\0\0sig_disconnect\0"
    "sig_write\0sig_read\0sig_downloadWave\0"
    "QVector<int>\0rf_connect\0rf_disconnect\0"
    "rf_write\0rf_read\0rf_output\0rf_config\0"
    "sigScanPorts\0sigConnectMixer\0port\0"
    "sigDisconnectMixer\0sigSendMixer\0cmd\0"
    "sigSetComd\0num\0onSigConnectClicked\0"
    "onSigConnectSuccess\0connected\0"
    "onSigWriteClicked\0onSigReadClicked\0"
    "onLoadFileClicked\0onDownloadWaveClicked\0"
    "onRfConnectClicked\0onRfConnectSuccess\0"
    "onRFWriteClicked\0onRFReadClicked\0"
    "onRFOutputOnClicked\0onRFOutputOffClicked\0"
    "onRFConfigClicked\0onPortsUpdated\0ports\0"
    "onMixBtnConnectClicked\0onMixBtnSetFreqClicked\0"
    "onMixBtnSetDownClicked\0onMixBtnSetUpClicked\0"
    "onMixBtnSendClicked\0closeVisaRF"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  194,    2, 0x06 /* Public */,
       3,    0,  197,    2, 0x06 /* Public */,
       4,    1,  198,    2, 0x06 /* Public */,
       5,    0,  201,    2, 0x06 /* Public */,
       6,    5,  202,    2, 0x06 /* Public */,
       8,    1,  213,    2, 0x06 /* Public */,
       9,    0,  216,    2, 0x06 /* Public */,
      10,    1,  217,    2, 0x06 /* Public */,
      11,    0,  220,    2, 0x06 /* Public */,
      12,    1,  221,    2, 0x06 /* Public */,
      13,    2,  224,    2, 0x06 /* Public */,
      14,    0,  229,    2, 0x06 /* Public */,
      15,    1,  230,    2, 0x06 /* Public */,
      17,    0,  233,    2, 0x06 /* Public */,
      18,    1,  234,    2, 0x06 /* Public */,
      20,    2,  237,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    0,  242,    2, 0x08 /* Private */,
      23,    1,  243,    2, 0x08 /* Private */,
      25,    0,  246,    2, 0x08 /* Private */,
      26,    0,  247,    2, 0x08 /* Private */,
      27,    0,  248,    2, 0x08 /* Private */,
      28,    0,  249,    2, 0x08 /* Private */,
      29,    0,  250,    2, 0x08 /* Private */,
      30,    1,  251,    2, 0x08 /* Private */,
      31,    0,  254,    2, 0x08 /* Private */,
      32,    0,  255,    2, 0x08 /* Private */,
      33,    0,  256,    2, 0x08 /* Private */,
      34,    0,  257,    2, 0x08 /* Private */,
      35,    0,  258,    2, 0x08 /* Private */,
      36,    1,  259,    2, 0x08 /* Private */,
      38,    0,  262,    2, 0x08 /* Private */,
      39,    0,  263,    2, 0x08 /* Private */,
      40,    0,  264,    2, 0x08 /* Private */,
      41,    0,  265,    2, 0x08 /* Private */,
      42,    0,  266,    2, 0x08 /* Private */,
      43,    0,  267,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   19,   21,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_connect((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sig_disconnect(); break;
        case 2: _t->sig_write((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sig_read(); break;
        case 4: _t->sig_downloadWave((*reinterpret_cast< QVector<int>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 5: _t->rf_connect((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->rf_disconnect(); break;
        case 7: _t->rf_write((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->rf_read(); break;
        case 9: _t->rf_output((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->rf_config((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 11: _t->sigScanPorts(); break;
        case 12: _t->sigConnectMixer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->sigDisconnectMixer(); break;
        case 14: _t->sigSendMixer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->sigSetComd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: _t->onSigConnectClicked(); break;
        case 17: _t->onSigConnectSuccess((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->onSigWriteClicked(); break;
        case 19: _t->onSigReadClicked(); break;
        case 20: _t->onLoadFileClicked(); break;
        case 21: _t->onDownloadWaveClicked(); break;
        case 22: _t->onRfConnectClicked(); break;
        case 23: _t->onRfConnectSuccess((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->onRFWriteClicked(); break;
        case 25: _t->onRFReadClicked(); break;
        case 26: _t->onRFOutputOnClicked(); break;
        case 27: _t->onRFOutputOffClicked(); break;
        case 28: _t->onRFConfigClicked(); break;
        case 29: _t->onPortsUpdated((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 30: _t->onMixBtnConnectClicked(); break;
        case 31: _t->onMixBtnSetFreqClicked(); break;
        case 32: _t->onMixBtnSetDownClicked(); break;
        case 33: _t->onMixBtnSetUpClicked(); break;
        case 34: _t->onMixBtnSendClicked(); break;
        case 35: _t->closeVisaRF(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
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
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sig_connect)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sig_disconnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sig_write)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sig_read)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QVector<int> , int , double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sig_downloadWave)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::rf_connect)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::rf_disconnect)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::rf_write)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::rf_read)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::rf_output)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::rf_config)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sigScanPorts)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sigConnectMixer)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sigDisconnectMixer)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sigSendMixer)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sigSetComd)) {
                *result = 15;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sig_connect(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sig_disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::sig_write(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::sig_read()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::sig_downloadWave(QVector<int> _t1, int _t2, double _t3, double _t4, double _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::rf_connect(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::rf_disconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::rf_write(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::rf_read()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void MainWindow::rf_output(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::rf_config(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::sigScanPorts()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void MainWindow::sigConnectMixer(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::sigDisconnectMixer()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void MainWindow::sigSendMixer(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MainWindow::sigSetComd(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
