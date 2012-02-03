/****************************************************************************
** Meta object code from reading C++ file 'qtbasicdialgauge.h'
**
** Created: Mon Nov 14 21:08:20 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/basicdialgauge/qtbasicdialgauge.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtbasicdialgauge.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtBasicDialGauge[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   18,   17,   17, 0x0a,
      64,   56,   17,   17, 0x0a,
      88,   80,   17,   17, 0x0a,
     120,  104,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QtBasicDialGauge[] = {
    "QtBasicDialGauge\0\0value\0valueChanged(int)\0"
    "setValue(int)\0maximum\0setMaximum(int)\0"
    "minimum\0setMinimum(int)\0minimum,maximum\0"
    "setRange(int,int)\0"
};

const QMetaObject QtBasicDialGauge::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QtBasicDialGauge,
      qt_meta_data_QtBasicDialGauge, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtBasicDialGauge::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtBasicDialGauge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtBasicDialGauge::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtBasicDialGauge))
        return static_cast<void*>(const_cast< QtBasicDialGauge*>(this));
    return QWidget::qt_metacast(_clname);
}

int QtBasicDialGauge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: setMaximum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setMinimum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QtBasicDialGauge::valueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
