/****************************************************************************
** Meta object code from reading C++ file 'QMwMaterialLayersWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Editor/Source/QMwWidgets/QMwMaterialLayersWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMwMaterialLayersWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QMwMaterialLayersWidget_t {
    QByteArrayData data[11];
    char stringdata[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QMwMaterialLayersWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QMwMaterialLayersWidget_t qt_meta_stringdata_QMwMaterialLayersWidget = {
    {
QT_MOC_LITERAL(0, 0, 23),
QT_MOC_LITERAL(1, 24, 18),
QT_MOC_LITERAL(2, 43, 0),
QT_MOC_LITERAL(3, 44, 20),
QT_MOC_LITERAL(4, 65, 18),
QT_MOC_LITERAL(5, 84, 18),
QT_MOC_LITERAL(6, 103, 18),
QT_MOC_LITERAL(7, 122, 13),
QT_MOC_LITERAL(8, 136, 27),
QT_MOC_LITERAL(9, 164, 5),
QT_MOC_LITERAL(10, 170, 26)
    },
    "QMwMaterialLayersWidget\0DeleteLayerClicked\0"
    "\0MoveLayerDownClicked\0MoveLayerUpClicked\0"
    "InsertLayerClicked\0AppendLayerClicked\0"
    "LayerSelected\0LayerShaderOperationChanged\0"
    "index\0LayerColorOperationChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMwMaterialLayersWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a,
       3,    0,   55,    2, 0x0a,
       4,    0,   56,    2, 0x0a,
       5,    0,   57,    2, 0x0a,
       6,    0,   58,    2, 0x0a,
       7,    0,   59,    2, 0x0a,
       8,    1,   60,    2, 0x0a,
      10,    1,   63,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void QMwMaterialLayersWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMwMaterialLayersWidget *_t = static_cast<QMwMaterialLayersWidget *>(_o);
        switch (_id) {
        case 0: _t->DeleteLayerClicked(); break;
        case 1: _t->MoveLayerDownClicked(); break;
        case 2: _t->MoveLayerUpClicked(); break;
        case 3: _t->InsertLayerClicked(); break;
        case 4: _t->AppendLayerClicked(); break;
        case 5: _t->LayerSelected(); break;
        case 6: _t->LayerShaderOperationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->LayerColorOperationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QMwMaterialLayersWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QMwMaterialLayersWidget.data,
      qt_meta_data_QMwMaterialLayersWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *QMwMaterialLayersWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMwMaterialLayersWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QMwMaterialLayersWidget.stringdata))
        return static_cast<void*>(const_cast< QMwMaterialLayersWidget*>(this));
    if (!strcmp(_clname, "QMwEditorWidget"))
        return static_cast< QMwEditorWidget*>(const_cast< QMwMaterialLayersWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QMwMaterialLayersWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
