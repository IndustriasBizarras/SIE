/****************************************************************************
** Meta object code from reading C++ file 'chart.h'
**
** Created: Thu Dec 1 11:16:31 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../analogwidgets/chart.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Chart[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
      19,  174, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    7,    6,    6, 0x05,
      26,    7,    6,    6, 0x05,
      46,    7,    6,    6, 0x05,
      67,    7,    6,    6, 0x05,
      91,    6,    6,    6, 0x05,
     118,  116,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
     155,    7,    6,    6, 0x0a,
     175,    7,    6,    6, 0x0a,
     192,    7,    6,    6, 0x0a,
     208,    7,    6,    6, 0x0a,
     221,    7,    6,    6, 0x0a,
     247,    7,    6,    6, 0x0a,
     273,    7,    6,    6, 0x0a,
     297,    7,    6,    6, 0x0a,
     321,    7,    6,    6, 0x0a,
     337,    7,    6,    6, 0x0a,
     351,    7,    6,    6, 0x0a,
     365,    7,    6,    6, 0x0a,
     382,    7,    6,    6, 0x0a,
     399,    7,    6,    6, 0x0a,
     425,    7,    6,    6, 0x0a,
     449,    7,    6,    6, 0x0a,
     468,    7,    6,    6, 0x0a,
     486,    7,    6,    6, 0x0a,
     506,    7,    6,    6, 0x0a,
     528,    7,    6,    6, 0x0a,
     545,  543,    6,    6, 0x0a,
     575,  543,    6,    6, 0x0a,
     607,  543,    6,    6, 0x0a,
     635,  628,    6,    6, 0x0a,
     651,    6,    6,    6, 0x09,
     668,  666,    6,    6, 0x09,

 // properties: name, type, flags
     709,  705, 0x02095103,
     717,  705, 0x02095103,
     733,  726, 0x06095103,
     738,  726, 0x06095103,
     743,  705, 0x02095103,
     749,  705, 0x02095103,
     755,  705, 0x02095103,
     764,  705, 0x02095103,
     773,  726, 0x06095103,
     788,  726, 0x06095103,
     808,  803, 0x01095103,
     825,  803, 0x01095103,
     847,  840, 0x43095103,
     868,  860, 0x0a095103,
     880,  803, 0x01095103,
     889,  803, 0x01095103,
     899,  803, 0x01095103,
     910,  803, 0x01095103,
     929,  923, 0x40095103,

       0        // eod
};

static const char qt_meta_stringdata_Chart[] = {
    "Chart\0\0i\0sizeChanged(int)\0sizeChanged(double)\0"
    "positionChanged(int)\0positionChanged(double)\0"
    "curPosChanged(QPolygonF)\0,\0"
    "curRangeChanged(QPolygonF,QPolygonF)\0"
    "setPosition(double)\0setPosition(int)\0"
    "setSize(double)\0setSize(int)\0"
    "setChannelMinimum(double)\0"
    "setChannelMaximum(double)\0"
    "setChannelColor(QColor)\0setChannelName(QString)\0"
    "setChannel(int)\0setYMesh(int)\0"
    "setXMesh(int)\0setYSubMesh(int)\0"
    "setXSubMesh(int)\0setChannelShowScale(bool)\0"
    "setChannelVisible(bool)\0setShowScale(bool)\0"
    "setShowGrid(bool)\0setShowLegend(bool)\0"
    "setAntialiasing(bool)\0setFont(QFont)\0"
    "c\0setTopBackgroundColor(QColor)\0"
    "setBottomBackgrounColor(QColor)\0"
    "setGridColor(QColor)\0factor\0setZoom(double)\0"
    "setPaintOver()\0a\0contextMenuActionTriggered(QAction*)\0"
    "int\0channel\0position\0double\0size\0zoom\0"
    "xMesh\0yMesh\0xSubMesh\0ySubMesh\0"
    "channelMinimum\0channelMaximum\0bool\0"
    "channelShowScale\0channelVisible\0QColor\0"
    "channelColor\0QString\0channelName\0"
    "showGrid\0showScale\0showLegend\0"
    "antialiasing\0QFont\0font\0"
};

const QMetaObject Chart::staticMetaObject = {
    { &WidgetWithBackground::staticMetaObject, qt_meta_stringdata_Chart,
      qt_meta_data_Chart, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Chart::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Chart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Chart::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Chart))
        return static_cast<void*>(const_cast< Chart*>(this));
    return WidgetWithBackground::qt_metacast(_clname);
}

int Chart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WidgetWithBackground::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: sizeChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: positionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: positionChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: curPosChanged((*reinterpret_cast< const QPolygonF(*)>(_a[1]))); break;
        case 5: curRangeChanged((*reinterpret_cast< const QPolygonF(*)>(_a[1])),(*reinterpret_cast< const QPolygonF(*)>(_a[2]))); break;
        case 6: setPosition((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: setPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setSize((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: setSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: setChannelMinimum((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: setChannelMaximum((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: setChannelColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 13: setChannelName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: setChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: setYMesh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: setXMesh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: setYSubMesh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: setXSubMesh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: setChannelShowScale((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: setChannelVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: setShowScale((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: setShowGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: setShowLegend((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: setAntialiasing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: setFont((*reinterpret_cast< QFont(*)>(_a[1]))); break;
        case 26: setTopBackgroundColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 27: setBottomBackgrounColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 28: setGridColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 29: setZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: setPaintOver(); break;
        case 31: contextMenuActionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 32;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = channel(); break;
        case 1: *reinterpret_cast< int*>(_v) = position(); break;
        case 2: *reinterpret_cast< double*>(_v) = size(); break;
        case 3: *reinterpret_cast< double*>(_v) = zoom(); break;
        case 4: *reinterpret_cast< int*>(_v) = xMesh(); break;
        case 5: *reinterpret_cast< int*>(_v) = yMesh(); break;
        case 6: *reinterpret_cast< int*>(_v) = xSubMesh(); break;
        case 7: *reinterpret_cast< int*>(_v) = ySubMesh(); break;
        case 8: *reinterpret_cast< double*>(_v) = channelMinimum(); break;
        case 9: *reinterpret_cast< double*>(_v) = channelMaximum(); break;
        case 10: *reinterpret_cast< bool*>(_v) = channelShowScale(); break;
        case 11: *reinterpret_cast< bool*>(_v) = channelVisible(); break;
        case 12: *reinterpret_cast< QColor*>(_v) = channelColor(); break;
        case 13: *reinterpret_cast< QString*>(_v) = channelName(); break;
        case 14: *reinterpret_cast< bool*>(_v) = showGrid(); break;
        case 15: *reinterpret_cast< bool*>(_v) = showScale(); break;
        case 16: *reinterpret_cast< bool*>(_v) = showLegend(); break;
        case 17: *reinterpret_cast< bool*>(_v) = antialiasing(); break;
        case 18: *reinterpret_cast< QFont*>(_v) = font(); break;
        }
        _id -= 19;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setChannel(*reinterpret_cast< int*>(_v)); break;
        case 1: setPosition(*reinterpret_cast< int*>(_v)); break;
        case 2: setSize(*reinterpret_cast< double*>(_v)); break;
        case 3: setZoom(*reinterpret_cast< double*>(_v)); break;
        case 4: setXMesh(*reinterpret_cast< int*>(_v)); break;
        case 5: setYMesh(*reinterpret_cast< int*>(_v)); break;
        case 6: setXSubMesh(*reinterpret_cast< int*>(_v)); break;
        case 7: setYSubMesh(*reinterpret_cast< int*>(_v)); break;
        case 8: setChannelMinimum(*reinterpret_cast< double*>(_v)); break;
        case 9: setChannelMaximum(*reinterpret_cast< double*>(_v)); break;
        case 10: setChannelShowScale(*reinterpret_cast< bool*>(_v)); break;
        case 11: setChannelVisible(*reinterpret_cast< bool*>(_v)); break;
        case 12: setChannelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 13: setChannelName(*reinterpret_cast< QString*>(_v)); break;
        case 14: setShowGrid(*reinterpret_cast< bool*>(_v)); break;
        case 15: setShowScale(*reinterpret_cast< bool*>(_v)); break;
        case 16: setShowLegend(*reinterpret_cast< bool*>(_v)); break;
        case 17: setAntialiasing(*reinterpret_cast< bool*>(_v)); break;
        case 18: setFont(*reinterpret_cast< QFont*>(_v)); break;
        }
        _id -= 19;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 19;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 19;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Chart::sizeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Chart::sizeChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Chart::positionChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Chart::positionChanged(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Chart::curPosChanged(const QPolygonF & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Chart::curRangeChanged(const QPolygonF & _t1, const QPolygonF & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
