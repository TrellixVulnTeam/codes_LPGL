/****************************************************************************
** Meta object code from reading C++ file 'mouthth.h'
**
** Created: Mon May 31 17:01:06 2010
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mouthth.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mouthth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MouthTh[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_MouthTh[] = {
    "MouthTh\0\0openmouth()\0"
};

const QMetaObject MouthTh::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MouthTh,
      qt_meta_data_MouthTh, 0 }
};

const QMetaObject *MouthTh::metaObject() const
{
    return &staticMetaObject;
}

void *MouthTh::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MouthTh))
        return static_cast<void*>(const_cast< MouthTh*>(this));
    return QThread::qt_metacast(_clname);
}

int MouthTh::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openmouth(); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MouthTh::openmouth()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
