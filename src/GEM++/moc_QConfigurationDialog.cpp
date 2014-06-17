/****************************************************************************
** Meta object code from reading C++ file 'QConfigurationDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Application/Widgets/QConfigurationDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QConfigurationDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QConfigurationDialog_t {
    QByteArrayData data[14];
    char stringdata[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QConfigurationDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QConfigurationDialog_t qt_meta_stringdata_QConfigurationDialog = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 7),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 8),
QT_MOC_LITERAL(4, 39, 2),
QT_MOC_LITERAL(5, 42, 14),
QT_MOC_LITERAL(6, 57, 3),
QT_MOC_LITERAL(7, 61, 7),
QT_MOC_LITERAL(8, 69, 6),
QT_MOC_LITERAL(9, 76, 11),
QT_MOC_LITERAL(10, 88, 18),
QT_MOC_LITERAL(11, 107, 2),
QT_MOC_LITERAL(12, 110, 11),
QT_MOC_LITERAL(13, 122, 10)
    },
    "QConfigurationDialog\0compute\0\0Problem*\0"
    "pb\0Configuration*\0cfg\0confirm\0cancel\0"
    "loadWeights\0Weights::Operation\0op\0"
    "saveWeights\0toggleMore\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QConfigurationDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       7,    0,   59,    2, 0x09,
       8,    0,   60,    2, 0x09,
       9,    1,   61,    2, 0x08,
       9,    0,   64,    2, 0x28,
      12,    1,   65,    2, 0x08,
      12,    0,   68,    2, 0x28,
      13,    0,   69,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QConfigurationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QConfigurationDialog *_t = static_cast<QConfigurationDialog *>(_o);
        switch (_id) {
        case 0: _t->compute((*reinterpret_cast< Problem*(*)>(_a[1])),(*reinterpret_cast< Configuration*(*)>(_a[2]))); break;
        case 1: _t->confirm(); break;
        case 2: _t->cancel(); break;
        case 3: _t->loadWeights((*reinterpret_cast< Weights::Operation(*)>(_a[1]))); break;
        case 4: _t->loadWeights(); break;
        case 5: _t->saveWeights((*reinterpret_cast< Weights::Operation(*)>(_a[1]))); break;
        case 6: _t->saveWeights(); break;
        case 7: _t->toggleMore(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QConfigurationDialog::*_t)(Problem * , Configuration * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QConfigurationDialog::compute)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QConfigurationDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QConfigurationDialog.data,
      qt_meta_data_QConfigurationDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *QConfigurationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QConfigurationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QConfigurationDialog.stringdata))
        return static_cast<void*>(const_cast< QConfigurationDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QConfigurationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QConfigurationDialog::compute(Problem * _t1, Configuration * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
