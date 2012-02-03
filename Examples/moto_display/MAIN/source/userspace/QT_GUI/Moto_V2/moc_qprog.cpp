/****************************************************************************
** Meta object code from reading C++ file 'qprog.h'
**
** Created: Mon Jan 30 10:51:01 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qprog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qprog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QProg[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       6,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,    6,    6,    6, 0x0a,
      45,    6,    6,    6, 0x0a,
      65,    6,    6,    6, 0x0a,
      85,    6,    6,    6, 0x0a,
     101,    6,    6,    6, 0x0a,
     119,    6,    6,    6, 0x0a,

 // properties: name, type, flags
     146,  139, 0x06095103,
     152,  139, 0x06095003,
     156,  139, 0x06095003,
     164,  160, 0x02095003,
     169,  160, 0x02095003,
     184,  177, 0x43095003,

       0        // eod
};

static const char qt_meta_stringdata_QProg[] = {
    "QProg\0\0valueChanged(double)\0"
    "setValue(double)\0setMaxValue(double)\0"
    "setMinValue(double)\0setFontDim(int)\0"
    "setPrecision(int)\0setBarColor(QColor)\0"
    "double\0value\0min\0max\0int\0font\0numPrec\0"
    "QColor\0color\0"
};

const QMetaObject QProg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QProg,
      qt_meta_data_QProg, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QProg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QProg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QProg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QProg))
        return static_cast<void*>(const_cast< QProg*>(this));
    return QWidget::qt_metacast(_clname);
}

int QProg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: setMaxValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: setMinValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: setFontDim((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setPrecision((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setBarColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = value(); break;
        case 1: *reinterpret_cast< double*>(_v) = minValue(); break;
        case 2: *reinterpret_cast< double*>(_v) = maxValue(); break;
        case 3: *reinterpret_cast< int*>(_v) = font(); break;
        case 4: *reinterpret_cast< int*>(_v) = numPrec(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = color(); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setValue(*reinterpret_cast< double*>(_v)); break;
        case 1: setMinValue(*reinterpret_cast< double*>(_v)); break;
        case 2: setMaxValue(*reinterpret_cast< double*>(_v)); break;
        case 3: setFontDim(*reinterpret_cast< int*>(_v)); break;
        case 4: setPrecision(*reinterpret_cast< int*>(_v)); break;
        case 5: setBarColor(*reinterpret_cast< QColor*>(_v)); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QProg::valueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
