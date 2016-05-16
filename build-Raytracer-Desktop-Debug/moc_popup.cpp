/****************************************************************************
** Meta object code from reading C++ file 'popup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bonus/popup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'popup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MyPopup_t {
    QByteArrayData data[9];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyPopup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyPopup_t qt_meta_stringdata_MyPopup = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MyPopup"
QT_MOC_LITERAL(1, 8, 11), // "setValueObj"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 19), // "cancelButtonPressed"
QT_MOC_LITERAL(4, 41, 19), // "createButtonPressed"
QT_MOC_LITERAL(5, 61, 14), // "editTypeSelect"
QT_MOC_LITERAL(6, 76, 2), // "nb"
QT_MOC_LITERAL(7, 79, 12), // "createSphere"
QT_MOC_LITERAL(8, 92, 14) // "createMaterial"

    },
    "MyPopup\0setValueObj\0\0cancelButtonPressed\0"
    "createButtonPressed\0editTypeSelect\0"
    "nb\0createSphere\0createMaterial"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyPopup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyPopup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyPopup *_t = static_cast<MyPopup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setValueObj(); break;
        case 1: _t->cancelButtonPressed(); break;
        case 2: _t->createButtonPressed(); break;
        case 3: _t->editTypeSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->createSphere(); break;
        case 5: _t->createMaterial(); break;
        default: ;
        }
    }
}

const QMetaObject MyPopup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyPopup.data,
      qt_meta_data_MyPopup,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyPopup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyPopup::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyPopup.stringdata0))
        return static_cast<void*>(const_cast< MyPopup*>(this));
    return QWidget::qt_metacast(_clname);
}

int MyPopup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
