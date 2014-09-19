/****************************************************************************
** Meta object code from reading C++ file 'QMwParameterWidgetColorAlpha.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Editor/Source/QMwWidgets/ParameterWidgets/QMwParameterWidgetColorAlpha.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMwParameterWidgetColorAlpha.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QMwParameterWidgetColorAlpha_t {
    QByteArrayData data[3];
    char stringdata[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QMwParameterWidgetColorAlpha_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QMwParameterWidgetColorAlpha_t qt_meta_stringdata_QMwParameterWidgetColorAlpha = {
    {
QT_MOC_LITERAL(0, 0, 28),
QT_MOC_LITERAL(1, 29, 14),
QT_MOC_LITERAL(2, 44, 0)
    },
    "QMwParameterWidgetColorAlpha\0"
    "OnValueChanged\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMwParameterWidgetColorAlpha[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void QMwParameterWidgetColorAlpha::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMwParameterWidgetColorAlpha *_t = static_cast<QMwParameterWidgetColorAlpha *>(_o);
        switch (_id) {
        case 0: _t->OnValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QMwParameterWidgetColorAlpha::staticMetaObject = {
    { &QDoubleSpinBox::staticMetaObject, qt_meta_stringdata_QMwParameterWidgetColorAlpha.data,
      qt_meta_data_QMwParameterWidgetColorAlpha,  qt_static_metacall, 0, 0}
};


const QMetaObject *QMwParameterWidgetColorAlpha::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMwParameterWidgetColorAlpha::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QMwParameterWidgetColorAlpha.stringdata))
        return static_cast<void*>(const_cast< QMwParameterWidgetColorAlpha*>(this));
    if (!strcmp(_clname, "QMwParameterWidget"))
        return static_cast< QMwParameterWidget*>(const_cast< QMwParameterWidgetColorAlpha*>(this));
    return QDoubleSpinBox::qt_metacast(_clname);
}

int QMwParameterWidgetColorAlpha::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDoubleSpinBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
