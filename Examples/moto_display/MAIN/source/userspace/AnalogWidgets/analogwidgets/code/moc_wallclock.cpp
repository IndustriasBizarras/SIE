/****************************************************************************
** Meta object code from reading C++ file 'wallclock.h'
**
** Created: Thu Dec 1 11:16:36 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../analogwidgets/wallclock.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wallclock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WallClock[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
      14,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      26,   10,   10,   10, 0x0a,
      41,   10,   10,   10, 0x0a,
      84,   64,   10,   10, 0x0a,
     113,   10,   10,   10, 0x09,

 // properties: name, type, flags
     132,  126, 0x40095103,
     142,  126, 0x40095103,
     151,  126, 0x40095103,
     160,  126, 0x40095103,
     172,  168, 0x02095103,
     184,  168, 0x02095103,
     195,  168, 0x02095103,
     206,  168, 0x02095103,
     223,  216, 0x43095103,
     234,  216, 0x43095103,
     244,  216, 0x43095103,
     254,  216, 0x43095103,
     273,  263, 0x10095103,
      64,  282, 0x01095103,

       0        // eod
};

static const char qt_meta_stringdata_WallClock[] = {
    "WallClock\0\0setTime(QTime)\0setDate(QDate)\0"
    "setDateTime(QDateTime)\0showCurrentDateTime\0"
    "setShowCurrentDateTime(bool)\0updateTime()\0"
    "QFont\0digitFont\0dateFont\0timeFont\0"
    "dayFont\0int\0digitOffset\0dateOffset\0"
    "timeOffset\0dayOffset\0QColor\0digitColor\0"
    "dateColor\0timeColor\0dayColor\0QDateTime\0"
    "dateTime\0bool\0"
};

const QMetaObject WallClock::staticMetaObject = {
    { &WidgetWithBackground::staticMetaObject, qt_meta_stringdata_WallClock,
      qt_meta_data_WallClock, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WallClock::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WallClock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WallClock::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WallClock))
        return static_cast<void*>(const_cast< WallClock*>(this));
    return WidgetWithBackground::qt_metacast(_clname);
}

int WallClock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WidgetWithBackground::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setTime((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 1: setDate((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 2: setDateTime((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 3: setShowCurrentDateTime((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: updateTime(); break;
        default: ;
        }
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QFont*>(_v) = digitFont(); break;
        case 1: *reinterpret_cast< QFont*>(_v) = dateFont(); break;
        case 2: *reinterpret_cast< QFont*>(_v) = timeFont(); break;
        case 3: *reinterpret_cast< QFont*>(_v) = dayFont(); break;
        case 4: *reinterpret_cast< int*>(_v) = digitOffset(); break;
        case 5: *reinterpret_cast< int*>(_v) = dateOffset(); break;
        case 6: *reinterpret_cast< int*>(_v) = timeOffset(); break;
        case 7: *reinterpret_cast< int*>(_v) = dayOffset(); break;
        case 8: *reinterpret_cast< QColor*>(_v) = digitColor(); break;
        case 9: *reinterpret_cast< QColor*>(_v) = dateColor(); break;
        case 10: *reinterpret_cast< QColor*>(_v) = timeColor(); break;
        case 11: *reinterpret_cast< QColor*>(_v) = dayColor(); break;
        case 12: *reinterpret_cast< QDateTime*>(_v) = dateTime(); break;
        case 13: *reinterpret_cast< bool*>(_v) = showCurrentDateTime(); break;
        }
        _id -= 14;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setDigitFont(*reinterpret_cast< QFont*>(_v)); break;
        case 1: setDateFont(*reinterpret_cast< QFont*>(_v)); break;
        case 2: setTimeFont(*reinterpret_cast< QFont*>(_v)); break;
        case 3: setDayFont(*reinterpret_cast< QFont*>(_v)); break;
        case 4: setDigitOffset(*reinterpret_cast< int*>(_v)); break;
        case 5: setDateOffset(*reinterpret_cast< int*>(_v)); break;
        case 6: setTimeOffset(*reinterpret_cast< int*>(_v)); break;
        case 7: setDayOffset(*reinterpret_cast< int*>(_v)); break;
        case 8: setDigitColor(*reinterpret_cast< QColor*>(_v)); break;
        case 9: setDateColor(*reinterpret_cast< QColor*>(_v)); break;
        case 10: setTimeColor(*reinterpret_cast< QColor*>(_v)); break;
        case 11: setDayColor(*reinterpret_cast< QColor*>(_v)); break;
        case 12: setDateTime(*reinterpret_cast< QDateTime*>(_v)); break;
        case 13: setShowCurrentDateTime(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 14;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
