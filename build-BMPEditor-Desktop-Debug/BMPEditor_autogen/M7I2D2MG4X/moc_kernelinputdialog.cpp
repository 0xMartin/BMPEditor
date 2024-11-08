/****************************************************************************
** Meta object code from reading C++ file 'kernelinputdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../BMPEditor/Dialog/kernelinputdialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kernelinputdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KernelInputDialog_t {
    const uint offsetsAndSize[16];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_KernelInputDialog_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_KernelInputDialog_t qt_meta_stringdata_KernelInputDialog = {
    {
QT_MOC_LITERAL(0, 17), // "KernelInputDialog"
QT_MOC_LITERAL(18, 13), // "kernelEntered"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 29), // "std::vector<std::vector<int>>"
QT_MOC_LITERAL(63, 6), // "kernel"
QT_MOC_LITERAL(70, 8), // "canceled"
QT_MOC_LITERAL(79, 11), // "onOkClicked"
QT_MOC_LITERAL(91, 15) // "onCancelClicked"

    },
    "KernelInputDialog\0kernelEntered\0\0"
    "std::vector<std::vector<int>>\0kernel\0"
    "canceled\0onOkClicked\0onCancelClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KernelInputDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       5,    0,   41,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   42,    2, 0x08,    4 /* Private */,
       7,    0,   43,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KernelInputDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KernelInputDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->kernelEntered((*reinterpret_cast< std::add_pointer_t<std::vector<std::vector<int>>>>(_a[1]))); break;
        case 1: _t->canceled(); break;
        case 2: _t->onOkClicked(); break;
        case 3: _t->onCancelClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KernelInputDialog::*)(const std::vector<std::vector<int>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KernelInputDialog::kernelEntered)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (KernelInputDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KernelInputDialog::canceled)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject KernelInputDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_KernelInputDialog.offsetsAndSize,
    qt_meta_data_KernelInputDialog,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_KernelInputDialog_t
, QtPrivate::TypeAndForceComplete<KernelInputDialog, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const std::vector<std::vector<int>> &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *KernelInputDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KernelInputDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KernelInputDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int KernelInputDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void KernelInputDialog::kernelEntered(const std::vector<std::vector<int>> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KernelInputDialog::canceled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
