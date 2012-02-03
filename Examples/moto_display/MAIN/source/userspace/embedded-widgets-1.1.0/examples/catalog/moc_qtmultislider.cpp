/****************************************************************************
** Meta object code from reading C++ file 'qtmultislider.h'
**
** Created: Mon Nov 14 21:09:27 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/multislider/qtmultislider.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtmultislider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtMultiSliderHelper[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QtMultiSliderHelper[] = {
    "QtMultiSliderHelper\0"
};

const QMetaObject QtMultiSliderHelper::staticMetaObject = {
    { &QAbstractSlider::staticMetaObject, qt_meta_stringdata_QtMultiSliderHelper,
      qt_meta_data_QtMultiSliderHelper, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtMultiSliderHelper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtMultiSliderHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtMultiSliderHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMultiSliderHelper))
        return static_cast<void*>(const_cast< QtMultiSliderHelper*>(this));
    return QAbstractSlider::qt_metacast(_clname);
}

int QtMultiSliderHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QtMultiSlider[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       1,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   15,   14,   14, 0x05,
      46,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      76,   68,   14,   14, 0x0a,
     105,   97,   14,   14, 0x0a,
     126,   14,   14,   14, 0x0a,
     146,  140,   14,   14, 0x08,
     169,  140,   14,   14, 0x08,

 // properties: name, type, flags
     200,  192, 0x0a095103,

       0        // eod
};

static const char qt_meta_stringdata_QtMultiSlider[] = {
    "QtMultiSlider\0\0exceeded\0maximumExceeded(bool)\0"
    "minimumExceeded(bool)\0maximum\0"
    "setMaximumRange(int)\0minimum\0"
    "setMinimumRange(int)\0setValue(int)\0"
    "value\0checkMinimumRange(int)\0"
    "checkMaximumRange(int)\0QString\0skin\0"
};

const QMetaObject QtMultiSlider::staticMetaObject = {
    { &QProgressBar::staticMetaObject, qt_meta_stringdata_QtMultiSlider,
      qt_meta_data_QtMultiSlider, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtMultiSlider::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtMultiSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtMultiSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMultiSlider))
        return static_cast<void*>(const_cast< QtMultiSlider*>(this));
    return QProgressBar::qt_metacast(_clname);
}

int QtMultiSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProgressBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: maximumExceeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: minimumExceeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: setMaximumRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setMinimumRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: checkMinimumRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: checkMaximumRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = skin(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSkin(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QtMultiSlider::maximumExceeded(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtMultiSlider::minimumExceeded(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
