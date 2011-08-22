/****************************************************************************
** Meta object code from reading C++ file 'callapp.h'
**
** Created: Wed Aug 17 14:35:56 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "callapp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'callapp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_callApp[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      19,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,    8,    8,    8, 0x0a,
      43,    8,    8,    8, 0x0a,
      55,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_callApp[] = {
    "callApp\0\0newData()\0appClosed()\0"
    "newStderr()\0newStdout()\0deleteProcess()\0"
};

const QMetaObject callApp::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_callApp,
      qt_meta_data_callApp, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &callApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *callApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *callApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_callApp))
        return static_cast<void*>(const_cast< callApp*>(this));
    return QWidget::qt_metacast(_clname);
}

int callApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newData(); break;
        case 1: appClosed(); break;
        case 2: newStderr(); break;
        case 3: newStdout(); break;
        case 4: deleteProcess(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void callApp::newData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void callApp::appClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
