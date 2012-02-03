/****************************************************************************
** Meta object code from reading C++ file 'potentiometer.h'
**
** Created: Thu Dec 1 11:16:44 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../analogwidgets/potentiometer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'potentiometer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PotentioMeter[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   34, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      26,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   37,   14,   14, 0x0a,
      82,   73,   14,   14, 0x0a,

 // properties: name, type, flags
      37,  110, 0x02095103,

       0        // eod
};

static const char qt_meta_stringdata_PotentioMeter[] = {
    "PotentioMeter\0\0valueInc()\0valueDec()\0"
    "rotationRange\0setRotationRange(int)\0"
    "filePath\0setSvgResourceFile(QString)\0"
    "int\0"
};

const QMetaObject PotentioMeter::staticMetaObject = {
    { &QAbstractSlider::staticMetaObject, qt_meta_stringdata_PotentioMeter,
      qt_meta_data_PotentioMeter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PotentioMeter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PotentioMeter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PotentioMeter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PotentioMeter))
        return static_cast<void*>(const_cast< PotentioMeter*>(this));
    return QAbstractSlider::qt_metacast(_clname);
}

int PotentioMeter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueInc(); break;
        case 1: valueDec(); break;
        case 2: setRotationRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setSvgResourceFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = rotationRange(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setRotationRange(*reinterpret_cast< int*>(_v)); break;
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
void PotentioMeter::valueInc()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void PotentioMeter::valueDec()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
