/****************************************************************************
** Meta object code from reading C++ file 'scriptwidget.h'
**
** Created: Thu Dec 1 11:16:42 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../analogwidgets/scriptwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scriptwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScriptWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       3,   69, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   25,   13,   13, 0x0a,
      51,   46,   13,   13, 0x0a,
      76,   71,   13,   13, 0x0a,
      93,   13,   13,   13, 0x0a,
     106,   46,   13,   13, 0x0a,
     127,   71,   13,   13, 0x0a,
     145,   13,   13,   13, 0x0a,
     160,   13,   13,   13, 0x0a,
     178,   13,   13,   13, 0x0a,
     197,   13,   13,   13, 0x0a,

 // properties: name, type, flags
     225,  217, 0x0a095103,
     241,  232, 0xff084103,
     248,  217, 0x0a084103,

       0        // eod
};

static const char qt_meta_stringdata_ScriptWidget[] = {
    "ScriptWidget\0\0evaluate()\0s\0"
    "setScript(QString)\0file\0setSvgFile(QString)\0"
    "name\0addItem(QString)\0resetItems()\0"
    "loadSvgFile(QString)\0setPName(QString)\0"
    "setPValue(int)\0setPValue(double)\0"
    "setPValue(QString)\0setPValue(QVariant)\0"
    "QString\0script\0QVariant\0PValue\0PName\0"
};

const QMetaObject ScriptWidget::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_ScriptWidget,
      qt_meta_data_ScriptWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScriptWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScriptWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScriptWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScriptWidget))
        return static_cast<void*>(const_cast< ScriptWidget*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int ScriptWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: evaluate(); break;
        case 1: setScript((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: setSvgFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: addItem((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: resetItems(); break;
        case 5: loadSvgFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: setPName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: setPValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setPValue((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: setPValue((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: setPValue((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = script(); break;
        case 1: *reinterpret_cast< QVariant*>(_v) = getPValue(); break;
        case 2: *reinterpret_cast< QString*>(_v) = getPName(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setScript(*reinterpret_cast< QString*>(_v)); break;
        case 1: setPValue(*reinterpret_cast< QVariant*>(_v)); break;
        case 2: setPName(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ScriptWidget::evaluate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
