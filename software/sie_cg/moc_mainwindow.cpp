/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Aug 17 14:35:49 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      54,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   12,   11,   11, 0x08,
      69,   66,   11,   11, 0x08,
      93,   11,   11,   11, 0x08,
     110,   11,   11,   11, 0x08,
     123,   66,   11,   11, 0x08,
     148,   11,   11,   11, 0x08,
     163,   11,   11,   11, 0x08,
     181,  176,   11,   11, 0x08,
     208,  176,   11,   11, 0x08,
     246,  241,   11,   11, 0x08,
     277,  272,   11,   11, 0x08,
     308,  302,   11,   11, 0x08,
     335,   11,   11,   11, 0x08,
     354,   11,   11,   11, 0x08,
     373,   11,   11,   11, 0x08,
     392,   11,   11,   11, 0x08,
     414,   11,   11,   11, 0x08,
     436,   11,   11,   11, 0x08,
     458,   11,   11,   11, 0x08,
     477,   11,   11,   11, 0x08,
     498,  489,  485,   11, 0x08,
     518,   11,  485,   11, 0x28,
     531,   11,  485,   11, 0x08,
     545,   11,  485,   11, 0x08,
     559,   11,  485,   11, 0x08,
     575,   11,  485,   11, 0x08,
     591,   11,   11,   11, 0x08,
     605,   11,   11,   11, 0x08,
     619,   11,   11,   11, 0x08,
     634,   11,  485,   11, 0x08,
     648,   11,   11,   11, 0x08,
     661,   11,   11,   11, 0x08,
     674,   11,   11,   11, 0x08,
     688,   11,   11,   11, 0x08,
     702,   11,   11,   11, 0x08,
     714,   11,  485,   11, 0x08,
     728,   11,   11,   11, 0x08,
     746,   11,   11,   11, 0x08,
     760,   11,   11,   11, 0x08,
     776,   11,   11,   11, 0x08,
     793,   11,  485,   11, 0x08,
     804,   11,   11,   11, 0x08,
     817,   11,   11,   11, 0x08,
     829,   11,   11,   11, 0x08,
     839,   11,   11,   11, 0x08,
     853,   11,   11,   11, 0x08,
     870,   11,   11,   11, 0x08,
     886,   11,   11,   11, 0x08,
     900,   11,   11,   11, 0x08,
     913,   11,   11,   11, 0x08,
     924,   11,   11,   11, 0x08,
     940,   11,   11,   11, 0x08,
     954,   11,   11,   11, 0x08,
     962,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0button\0"
    "backgroundButtonGroupClicked(QAbstractButton*)\0"
    "id\0buttonGroupClicked(int)\0cgGroupClicked()\0"
    "deleteItem()\0pointerGroupClicked(int)\0"
    "bringToFront()\0sendToBack()\0item\0"
    "itemInserted(DiagramItem*)\0"
    "textInserted(QGraphicsTextItem*)\0font\0"
    "currentFontChanged(QFont)\0size\0"
    "fontSizeChanged(QString)\0scale\0"
    "sceneScaleChanged(QString)\0"
    "textColorChanged()\0itemColorChanged()\0"
    "lineColorChanged()\0textButtonTriggered()\0"
    "fillButtonTriggered()\0lineButtonTriggered()\0"
    "handleFontChange()\0about()\0int\0pathFile\0"
    "newDiagram(QString)\0newDiagram()\0"
    "openDiagram()\0saveDiagram()\0saveAsDiagram()\0"
    "exportDiagram()\0undoDiagram()\0"
    "redoDiagram()\0setGridState()\0libraryForm()\0"
    "addLibPath()\0delLibPath()\0editLibPath()\0"
    "downLibPath()\0upLibPath()\0optionsForm()\0"
    "editTemplateDir()\0editWorkDir()\0"
    "editToolChain()\0editFPGABinary()\0"
    "codeForm()\0executeSSH()\0finishSSH()\0"
    "readSSH()\0sendCommand()\0executeCompile()\0"
    "finishCompile()\0readCompile()\0"
    "configFPGA()\0exeOnSie()\0saveTemplates()\0"
    "killProcess()\0lcdOn()\0lcdOff()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: backgroundButtonGroupClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 1: buttonGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: cgGroupClicked(); break;
        case 3: deleteItem(); break;
        case 4: pointerGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: bringToFront(); break;
        case 6: sendToBack(); break;
        case 7: itemInserted((*reinterpret_cast< DiagramItem*(*)>(_a[1]))); break;
        case 8: textInserted((*reinterpret_cast< QGraphicsTextItem*(*)>(_a[1]))); break;
        case 9: currentFontChanged((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 10: fontSizeChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: sceneScaleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: textColorChanged(); break;
        case 13: itemColorChanged(); break;
        case 14: lineColorChanged(); break;
        case 15: textButtonTriggered(); break;
        case 16: fillButtonTriggered(); break;
        case 17: lineButtonTriggered(); break;
        case 18: handleFontChange(); break;
        case 19: about(); break;
        case 20: { int _r = newDiagram((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 21: { int _r = newDiagram();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 22: { int _r = openDiagram();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 23: { int _r = saveDiagram();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 24: { int _r = saveAsDiagram();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 25: { int _r = exportDiagram();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 26: undoDiagram(); break;
        case 27: redoDiagram(); break;
        case 28: setGridState(); break;
        case 29: { int _r = libraryForm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 30: addLibPath(); break;
        case 31: delLibPath(); break;
        case 32: editLibPath(); break;
        case 33: downLibPath(); break;
        case 34: upLibPath(); break;
        case 35: { int _r = optionsForm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 36: editTemplateDir(); break;
        case 37: editWorkDir(); break;
        case 38: editToolChain(); break;
        case 39: editFPGABinary(); break;
        case 40: { int _r = codeForm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 41: executeSSH(); break;
        case 42: finishSSH(); break;
        case 43: readSSH(); break;
        case 44: sendCommand(); break;
        case 45: executeCompile(); break;
        case 46: finishCompile(); break;
        case 47: readCompile(); break;
        case 48: configFPGA(); break;
        case 49: exeOnSie(); break;
        case 50: saveTemplates(); break;
        case 51: killProcess(); break;
        case 52: lcdOn(); break;
        case 53: lcdOff(); break;
        default: ;
        }
        _id -= 54;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
