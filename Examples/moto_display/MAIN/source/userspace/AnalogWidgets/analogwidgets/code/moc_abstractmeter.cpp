/****************************************************************************
** Meta object code from reading C++ file 'abstractmeter.h'
**
** Created: Thu Dec 1 11:16:34 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../analogwidgets/abstractmeter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractmeter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AbstractMeter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
      11,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   15,   14,   14, 0x05,
      37,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   15,   14,   14, 0x0a,
      72,   15,   14,   14, 0x0a,

 // properties: name, type, flags
      96,   89, 0x06095103,
     104,   89, 0x06095103,
     112,   89, 0x06095103,
     118,   89, 0x06095103,
     126,   89, 0x06095103,
     143,  135, 0x0a095103,
     150,  135, 0x0a095103,
     163,  157, 0x40095103,
     173,   89, 0x06095103,
     185,  157, 0x40095103,
     195,   89, 0x06095103,

       0        // eod
};

static const char qt_meta_stringdata_AbstractMeter[] = {
    "AbstractMeter\0\0val\0valueChanged(int)\0"
    "valueChanged(double)\0setValue(int)\0"
    "setValue(double)\0double\0minimum\0maximum\0"
    "value\0nominal\0critical\0QString\0prefix\0"
    "suffix\0QFont\0valueFont\0valueOffset\0"
    "digitFont\0digitOffset\0"
};

const QMetaObject AbstractMeter::staticMetaObject = {
    { &WidgetWithBackground::staticMetaObject, qt_meta_stringdata_AbstractMeter,
      qt_meta_data_AbstractMeter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AbstractMeter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AbstractMeter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AbstractMeter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractMeter))
        return static_cast<void*>(const_cast< AbstractMeter*>(this));
    return WidgetWithBackground::qt_metacast(_clname);
}

int AbstractMeter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WidgetWithBackground::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = minimum(); break;
        case 1: *reinterpret_cast< double*>(_v) = maximum(); break;
        case 2: *reinterpret_cast< double*>(_v) = value(); break;
        case 3: *reinterpret_cast< double*>(_v) = nominal(); break;
        case 4: *reinterpret_cast< double*>(_v) = critical(); break;
        case 5: *reinterpret_cast< QString*>(_v) = prefix(); break;
        case 6: *reinterpret_cast< QString*>(_v) = suffix(); break;
        case 7: *reinterpret_cast< QFont*>(_v) = valueFont(); break;
        case 8: *reinterpret_cast< double*>(_v) = valueOffset(); break;
        case 9: *reinterpret_cast< QFont*>(_v) = digitFont(); break;
        case 10: *reinterpret_cast< double*>(_v) = digitOffset(); break;
        }
        _id -= 11;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setMinimum(*reinterpret_cast< double*>(_v)); break;
        case 1: setMaximum(*reinterpret_cast< double*>(_v)); break;
        case 2: setValue(*reinterpret_cast< double*>(_v)); break;
        case 3: setNominal(*reinterpret_cast< double*>(_v)); break;
        case 4: setCritical(*reinterpret_cast< double*>(_v)); break;
        case 5: setPrefix(*reinterpret_cast< QString*>(_v)); break;
        case 6: setSuffix(*reinterpret_cast< QString*>(_v)); break;
        case 7: setValueFont(*reinterpret_cast< QFont*>(_v)); break;
        case 8: setValueOffset(*reinterpret_cast< double*>(_v)); break;
        case 9: setDigitFont(*reinterpret_cast< QFont*>(_v)); break;
        case 10: setDigitOffset(*reinterpret_cast< double*>(_v)); break;
        }
        _id -= 11;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AbstractMeter::valueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AbstractMeter::valueChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
