/****************************************************************************
** Meta object code from reading C++ file 'piezocontrol.h'
**
** Created: Fri Feb 28 11:03:55 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "piezocontrol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'piezocontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PiezoControl[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      34,   13,   13,   13, 0x0a,
      49,   13,   13,   13, 0x0a,
      66,   13,   13,   13, 0x0a,
      88,   13,   13,   13, 0x0a,
     110,   13,   13,   13, 0x0a,
     127,   13,   13,   13, 0x0a,
     145,   13,   13,   13, 0x0a,
     168,   13,   13,   13, 0x0a,
     188,   13,   13,   13, 0x0a,
     203,   13,   13,   13, 0x0a,
     220,   13,   13,   13, 0x0a,
     242,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PiezoControl[] = {
    "PiezoControl\0\0x_up_fast_clicked()\0"
    "x_up_clicked()\0x_down_clicked()\0"
    "x_down_fast_clicked()\0y_left_fast_clicked()\0"
    "y_left_clicked()\0y_right_clicked()\0"
    "y_right_fast_clicked()\0z_up_fast_clicked()\0"
    "z_up_clicked()\0z_down_clicked()\0"
    "z_down_fast_clicked()\0abort_clicked()\0"
};

const QMetaObject PiezoControl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PiezoControl,
      qt_meta_data_PiezoControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PiezoControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PiezoControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PiezoControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PiezoControl))
        return static_cast<void*>(const_cast< PiezoControl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PiezoControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: x_up_fast_clicked(); break;
        case 1: x_up_clicked(); break;
        case 2: x_down_clicked(); break;
        case 3: x_down_fast_clicked(); break;
        case 4: y_left_fast_clicked(); break;
        case 5: y_left_clicked(); break;
        case 6: y_right_clicked(); break;
        case 7: y_right_fast_clicked(); break;
        case 8: z_up_fast_clicked(); break;
        case 9: z_up_clicked(); break;
        case 10: z_down_clicked(); break;
        case 11: z_down_fast_clicked(); break;
        case 12: abort_clicked(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
