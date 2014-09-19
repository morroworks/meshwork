/****************************************************************************
** Meta object code from reading C++ file 'QMwScriptPropertiesWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Editor/Source/QMwWidgets/QMwScriptPropertiesWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMwScriptPropertiesWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QMwScriptPropertiesWidget_t {
    QByteArrayData data[8];
    char stringdata[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QMwScriptPropertiesWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QMwScriptPropertiesWidget_t qt_meta_stringdata_QMwScriptPropertiesWidget = {
    {
QT_MOC_LITERAL(0, 0, 25),
QT_MOC_LITERAL(1, 26, 18),
QT_MOC_LITERAL(2, 45, 0),
QT_MOC_LITERAL(3, 46, 18),
QT_MOC_LITERAL(4, 65, 13),
QT_MOC_LITERAL(5, 79, 16),
QT_MOC_LITERAL(6, 96, 16),
QT_MOC_LITERAL(7, 113, 5)
    },
    "QMwScriptPropertiesWidget\0DeleteLayerClicked\0"
    "\0AppendLayerClicked\0LayerSelected\0"
    "LayerNameChanged\0LayerTypeChanged\0"
    "index\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMwScriptPropertiesWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a,
       3,    0,   40,    2, 0x0a,
       4,    0,   41,    2, 0x0a,
       5,    0,   42,    2, 0x0a,
       6,    1,   43,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void QMwScriptPropertiesWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMwScriptPropertiesWidget *_t = static_cast<QMwScriptPropertiesWidget *>(_o);
        switch (_id) {
        case 0: _t->DeleteLayerClicked(); break;
        case 1: _t->AppendLayerClicked(); break;
        case 2: _t->LayerSelected(); break;
        case 3: _t->LayerNameChanged(); break;
        case 4: _t->LayerTypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QMwScriptPropertiesWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QMwScriptPropertiesWidget.data,
      qt_meta_data_QMwScriptPropertiesWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *QMwScriptPropertiesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMwScriptPropertiesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QMwScriptPropertiesWidget.stringdata))
        return static_cast<void*>(const_cast< QMwScriptPropertiesWidget*>(this));
    if (!strcmp(_clname, "QMwEditorWidget"))
        return static_cast< QMwEditorWidget*>(const_cast< QMwScriptPropertiesWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QMwScriptPropertiesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
