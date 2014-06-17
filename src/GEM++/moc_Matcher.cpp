/****************************************************************************
** Meta object code from reading C++ file 'Matcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Solver/Matcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Matcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Matcher_t {
    QByteArrayData data[10];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Matcher_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Matcher_t qt_meta_stringdata_Matcher = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 8),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 8),
QT_MOC_LITERAL(4, 27, 2),
QT_MOC_LITERAL(5, 30, 9),
QT_MOC_LITERAL(6, 40, 3),
QT_MOC_LITERAL(7, 44, 13),
QT_MOC_LITERAL(8, 58, 5),
QT_MOC_LITERAL(9, 64, 5)
    },
    "Matcher\0finished\0\0Problem*\0pb\0objective\0"
    "run\0SolutionList*\0slout\0clean\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Matcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x0a,
       6,    1,   40,    2, 0x0a,
       9,    0,   43,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Double,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void Matcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Matcher *_t = static_cast<Matcher *>(_o);
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< Problem*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->run(); break;
        case 2: _t->run((*reinterpret_cast< SolutionList*(*)>(_a[1]))); break;
        case 3: _t->clean(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Matcher::*_t)(Problem * , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Matcher::finished)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Matcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Matcher.data,
      qt_meta_data_Matcher,  qt_static_metacall, 0, 0}
};


const QMetaObject *Matcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Matcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Matcher.stringdata))
        return static_cast<void*>(const_cast< Matcher*>(this));
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(const_cast< Matcher*>(this));
    if (!strcmp(_clname, "ICleanable"))
        return static_cast< ICleanable*>(const_cast< Matcher*>(this));
    return QObject::qt_metacast(_clname);
}

int Matcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void Matcher::finished(Problem * _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
