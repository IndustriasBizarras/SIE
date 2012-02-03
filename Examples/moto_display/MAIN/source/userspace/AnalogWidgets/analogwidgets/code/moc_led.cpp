/****************************************************************************
** Meta object code from reading C++ file 'led.h'
**
** Created: Thu Dec 1 11:16:28 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../analogwidgets/led.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'led.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Led[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    5,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,    4,    4,    4, 0x0a,

 // properties: name, type, flags
      50,   45, 0x01095103,
      65,   58, 0x43095103,

       0        // eod
};

static const char qt_meta_stringdata_Led[] = {
    "Led\0\0val\0checkChanged(bool)\0"
    "setChecked(bool)\0bool\0checked\0QColor\0"
    "color\0"
};

const QMetaObject Led::staticMetaObject = {
    { &WidgetWithBackground::staticMetaObject, qt_meta_stringdata_Led,
      qt_meta_data_Led, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Led::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Led::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Led::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Led))
        return static_cast<void*>(const_cast< Led*>(this));
    return WidgetWithBackground::qt_metacast(_clname);
}

int Led::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WidgetWithBackground::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: setChecked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = isChecked(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = color(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setChecked(*reinterpret_cast< bool*>(_v)); break;
        case 1: setColor(*reinterpret_cast< QColor*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
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
void Led::checkChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
