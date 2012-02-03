/****************************************************************************
** Meta object code from reading C++ file 'patientcarecontroller.h'
**
** Created: Mon Nov 14 21:08:39 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "patientcarecontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'patientcarecontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PatientCareController[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   23,   22,   22, 0x0a,
      57,   48,   22,   22, 0x0a,
      87,   48,   22,   22, 0x0a,
     117,   23,   22,   22, 0x0a,
     141,   22,   22,   22, 0x0a,
     159,   48,   22,   22, 0x0a,
     190,   48,   22,   22, 0x0a,
     221,   23,   22,   22, 0x0a,
     242,   22,   22,   22, 0x0a,
     268,  261,   22,   22, 0x0a,
     291,   22,   22,   22, 0x0a,
     301,   22,   22,   22, 0x0a,
     312,   22,   22,   22, 0x0a,
     322,   22,   22,   22, 0x0a,
     333,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PatientCareController[] = {
    "PatientCareController\0\0value\0"
    "setMedication(int)\0exceeded\0"
    "maximumDripRateExceeded(bool)\0"
    "minimumDripRateExceeded(bool)\0"
    "updateMedicineFlow(int)\0updateFlowRange()\0"
    "maximumHeartRateExceeded(bool)\0"
    "minimumHeartRateExceeded(bool)\0"
    "updateHeartRate(int)\0updatePulseRange()\0"
    "enable\0enableMedication(bool)\0zoomXIn()\0"
    "zoomXOut()\0zoomYIn()\0zoomYOut()\0"
    "resetZoom()\0"
};

const QMetaObject PatientCareController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PatientCareController,
      qt_meta_data_PatientCareController, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PatientCareController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PatientCareController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PatientCareController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PatientCareController))
        return static_cast<void*>(const_cast< PatientCareController*>(this));
    return QObject::qt_metacast(_clname);
}

int PatientCareController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setMedication((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: maximumDripRateExceeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: minimumDripRateExceeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: updateMedicineFlow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: updateFlowRange(); break;
        case 5: maximumHeartRateExceeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: minimumHeartRateExceeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: updateHeartRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: updatePulseRange(); break;
        case 9: enableMedication((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: zoomXIn(); break;
        case 11: zoomXOut(); break;
        case 12: zoomYIn(); break;
        case 13: zoomYOut(); break;
        case 14: resetZoom(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
