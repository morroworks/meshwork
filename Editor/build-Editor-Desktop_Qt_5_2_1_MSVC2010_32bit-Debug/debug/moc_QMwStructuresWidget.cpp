/****************************************************************************
** Meta object code from reading C++ file 'QMwStructuresWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Editor/Source/QMwWidgets/QMwStructuresWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMwStructuresWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QMwStructuresWidget_t {
    QByteArrayData data[10];
    char stringdata[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QMwStructuresWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QMwStructuresWidget_t qt_meta_stringdata_QMwStructuresWidget = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 18),
QT_MOC_LITERAL(2, 39, 0),
QT_MOC_LITERAL(3, 40, 16),
QT_MOC_LITERAL(4, 57, 7),
QT_MOC_LITERAL(5, 65, 8),
QT_MOC_LITERAL(6, 74, 20),
QT_MOC_LITERAL(7, 95, 3),
QT_MOC_LITERAL(8, 99, 26),
QT_MOC_LITERAL(9, 126, 35)
    },
    "QMwStructuresWidget\0CurrentItemChanged\0"
    "\0QTreeWidgetItem*\0current\0previous\0"
    "ContextMenuRequested\0pos\0"
    "ContextMenuDeleteTriggered\0"
    "ContextMenuWrapInEntitySetTriggered\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMwStructuresWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a,
       6,    1,   39,    2, 0x0a,
       8,    0,   42,    2, 0x0a,
       9,    0,   43,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::QPoint,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QMwStructuresWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QMwStructuresWidget *_t = static_cast<QMwStructuresWidget *>(_o);
        switch (_id) {
        case 0: _t->CurrentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 1: _t->ContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->ContextMenuDeleteTriggered(); break;
        case 3: _t->ContextMenuWrapInEntitySetTriggered(); break;
        default: ;
        }
    }
}

const QMetaObject QMwStructuresWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_QMwStructuresWidget.data,
      qt_meta_data_QMwStructuresWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *QMwStructuresWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMwStructuresWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QMwStructuresWidget.stringdata))
        return static_cast<void*>(const_cast< QMwStructuresWidget*>(this));
    if (!strcmp(_clname, "QMwEditorWidget"))
        return static_cast< QMwEditorWidget*>(const_cast< QMwStructuresWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int QMwStructuresWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
