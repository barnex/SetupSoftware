/****************************************************************************
** Meta object code from reading C++ file 'updateThread.h'
**
** Created: Mon Feb 24 14:29:49 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "updateThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updateThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_updateThread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_updateThread[] = {
    "updateThread\0\0values\0sendValues(float*)\0"
    "timerHit()\0"
};

const QMetaObject updateThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_updateThread,
      qt_meta_data_updateThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &updateThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *updateThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *updateThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_updateThread))
        return static_cast<void*>(const_cast< updateThread*>(this));
    return QThread::qt_metacast(_clname);
}

int updateThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendValues((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 1: timerHit(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void updateThread::sendValues(float * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
