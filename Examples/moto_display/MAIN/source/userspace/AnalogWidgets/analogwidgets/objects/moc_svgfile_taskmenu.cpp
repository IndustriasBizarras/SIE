/****************************************************************************
** Meta object code from reading C++ file 'svgfile_taskmenu.h'
**
** Created: Thu Dec 1 11:54:19 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../plugins/svgfile_taskmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'svgfile_taskmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SvgFileTaskMenu[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SvgFileTaskMenu[] = {
    "SvgFileTaskMenu\0\0setSvgFile()\0"
};

const QMetaObject SvgFileTaskMenu::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SvgFileTaskMenu,
      qt_meta_data_SvgFileTaskMenu, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SvgFileTaskMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SvgFileTaskMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SvgFileTaskMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SvgFileTaskMenu))
        return static_cast<void*>(const_cast< SvgFileTaskMenu*>(this));
    if (!strcmp(_clname, "QDesignerTaskMenuExtension"))
        return static_cast< QDesignerTaskMenuExtension*>(const_cast< SvgFileTaskMenu*>(this));
    if (!strcmp(_clname, "com.trolltech.Qt.Designer.TaskMenu"))
        return static_cast< QDesignerTaskMenuExtension*>(const_cast< SvgFileTaskMenu*>(this));
    return QObject::qt_metacast(_clname);
}

int SvgFileTaskMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setSvgFile(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_SvgFileTaskMenuFactory[] = {

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

static const char qt_meta_stringdata_SvgFileTaskMenuFactory[] = {
    "SvgFileTaskMenuFactory\0"
};

const QMetaObject SvgFileTaskMenuFactory::staticMetaObject = {
    { &QExtensionFactory::staticMetaObject, qt_meta_stringdata_SvgFileTaskMenuFactory,
      qt_meta_data_SvgFileTaskMenuFactory, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SvgFileTaskMenuFactory::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SvgFileTaskMenuFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SvgFileTaskMenuFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SvgFileTaskMenuFactory))
        return static_cast<void*>(const_cast< SvgFileTaskMenuFactory*>(this));
    return QExtensionFactory::qt_metacast(_clname);
}

int SvgFileTaskMenuFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QExtensionFactory::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
