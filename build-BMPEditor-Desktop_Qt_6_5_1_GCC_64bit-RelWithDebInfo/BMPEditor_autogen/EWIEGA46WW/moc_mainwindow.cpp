/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BMPEditor/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "imageChanged",
    "",
    "message",
    "asyncJobStart",
    "asyncJobFinished",
    "formatDone",
    "Image*",
    "img",
    "on_actionOpen_triggered",
    "on_actionSave_triggered",
    "on_actionAbout_triggered",
    "on_actionExit_triggered",
    "on_actionZoom_in_triggered",
    "on_actionZoom_out_triggered",
    "on_actionReset_scale_triggered",
    "on_actionUndo_triggered",
    "on_actionRedo_triggered",
    "on_actionRotate_90_plus_triggered",
    "on_actionRotate_90_minus_triggered",
    "on_actionFlip_horizontally_triggered",
    "on_action_Flip_vertically_triggered",
    "on_actionGrayscale_triggered",
    "on_actionInvert_triggered",
    "on_actionSepia_triggered",
    "on_actionBlur_triggered",
    "on_actionBrightness_triggered",
    "on_actionContrast_triggered",
    "on_actionColor_balance_triggered",
    "on_actionConvert_to_1b_BMP_triggered",
    "on_actionConvert_to_4b_BMP_triggered",
    "on_actionConvert_to_8b_BMP_triggered",
    "on_actionConvert_to_24b_BMP_triggered",
    "on_actionWrite_message_triggered",
    "on_actionRead_message_triggered",
    "on_actionClear_message_triggered",
    "on_actionSharpen_triggered",
    "on_actionEdge_Detection_triggered",
    "on_actionEmboss_triggered",
    "on_actionApply_Custom_Kernel_triggered",
    "on_actionImport_as_BMP_24_triggered"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[82];
    char stringdata0[11];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[8];
    char stringdata4[14];
    char stringdata5[17];
    char stringdata6[11];
    char stringdata7[7];
    char stringdata8[4];
    char stringdata9[24];
    char stringdata10[24];
    char stringdata11[25];
    char stringdata12[24];
    char stringdata13[27];
    char stringdata14[28];
    char stringdata15[31];
    char stringdata16[24];
    char stringdata17[24];
    char stringdata18[34];
    char stringdata19[35];
    char stringdata20[37];
    char stringdata21[36];
    char stringdata22[29];
    char stringdata23[26];
    char stringdata24[25];
    char stringdata25[24];
    char stringdata26[30];
    char stringdata27[28];
    char stringdata28[33];
    char stringdata29[37];
    char stringdata30[37];
    char stringdata31[37];
    char stringdata32[38];
    char stringdata33[33];
    char stringdata34[32];
    char stringdata35[33];
    char stringdata36[27];
    char stringdata37[34];
    char stringdata38[26];
    char stringdata39[39];
    char stringdata40[36];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 12),  // "imageChanged"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 7),  // "message"
        QT_MOC_LITERAL(33, 13),  // "asyncJobStart"
        QT_MOC_LITERAL(47, 16),  // "asyncJobFinished"
        QT_MOC_LITERAL(64, 10),  // "formatDone"
        QT_MOC_LITERAL(75, 6),  // "Image*"
        QT_MOC_LITERAL(82, 3),  // "img"
        QT_MOC_LITERAL(86, 23),  // "on_actionOpen_triggered"
        QT_MOC_LITERAL(110, 23),  // "on_actionSave_triggered"
        QT_MOC_LITERAL(134, 24),  // "on_actionAbout_triggered"
        QT_MOC_LITERAL(159, 23),  // "on_actionExit_triggered"
        QT_MOC_LITERAL(183, 26),  // "on_actionZoom_in_triggered"
        QT_MOC_LITERAL(210, 27),  // "on_actionZoom_out_triggered"
        QT_MOC_LITERAL(238, 30),  // "on_actionReset_scale_triggered"
        QT_MOC_LITERAL(269, 23),  // "on_actionUndo_triggered"
        QT_MOC_LITERAL(293, 23),  // "on_actionRedo_triggered"
        QT_MOC_LITERAL(317, 33),  // "on_actionRotate_90_plus_trigg..."
        QT_MOC_LITERAL(351, 34),  // "on_actionRotate_90_minus_trig..."
        QT_MOC_LITERAL(386, 36),  // "on_actionFlip_horizontally_tr..."
        QT_MOC_LITERAL(423, 35),  // "on_action_Flip_vertically_tri..."
        QT_MOC_LITERAL(459, 28),  // "on_actionGrayscale_triggered"
        QT_MOC_LITERAL(488, 25),  // "on_actionInvert_triggered"
        QT_MOC_LITERAL(514, 24),  // "on_actionSepia_triggered"
        QT_MOC_LITERAL(539, 23),  // "on_actionBlur_triggered"
        QT_MOC_LITERAL(563, 29),  // "on_actionBrightness_triggered"
        QT_MOC_LITERAL(593, 27),  // "on_actionContrast_triggered"
        QT_MOC_LITERAL(621, 32),  // "on_actionColor_balance_triggered"
        QT_MOC_LITERAL(654, 36),  // "on_actionConvert_to_1b_BMP_tr..."
        QT_MOC_LITERAL(691, 36),  // "on_actionConvert_to_4b_BMP_tr..."
        QT_MOC_LITERAL(728, 36),  // "on_actionConvert_to_8b_BMP_tr..."
        QT_MOC_LITERAL(765, 37),  // "on_actionConvert_to_24b_BMP_t..."
        QT_MOC_LITERAL(803, 32),  // "on_actionWrite_message_triggered"
        QT_MOC_LITERAL(836, 31),  // "on_actionRead_message_triggered"
        QT_MOC_LITERAL(868, 32),  // "on_actionClear_message_triggered"
        QT_MOC_LITERAL(901, 26),  // "on_actionSharpen_triggered"
        QT_MOC_LITERAL(928, 33),  // "on_actionEdge_Detection_trigg..."
        QT_MOC_LITERAL(962, 25),  // "on_actionEmboss_triggered"
        QT_MOC_LITERAL(988, 38),  // "on_actionApply_Custom_Kernel_..."
        QT_MOC_LITERAL(1027, 35)   // "on_actionImport_as_BMP_24_tri..."
    },
    "MainWindow",
    "imageChanged",
    "",
    "message",
    "asyncJobStart",
    "asyncJobFinished",
    "formatDone",
    "Image*",
    "img",
    "on_actionOpen_triggered",
    "on_actionSave_triggered",
    "on_actionAbout_triggered",
    "on_actionExit_triggered",
    "on_actionZoom_in_triggered",
    "on_actionZoom_out_triggered",
    "on_actionReset_scale_triggered",
    "on_actionUndo_triggered",
    "on_actionRedo_triggered",
    "on_actionRotate_90_plus_triggered",
    "on_actionRotate_90_minus_triggered",
    "on_actionFlip_horizontally_triggered",
    "on_action_Flip_vertically_triggered",
    "on_actionGrayscale_triggered",
    "on_actionInvert_triggered",
    "on_actionSepia_triggered",
    "on_actionBlur_triggered",
    "on_actionBrightness_triggered",
    "on_actionContrast_triggered",
    "on_actionColor_balance_triggered",
    "on_actionConvert_to_1b_BMP_triggered",
    "on_actionConvert_to_4b_BMP_triggered",
    "on_actionConvert_to_8b_BMP_triggered",
    "on_actionConvert_to_24b_BMP_triggered",
    "on_actionWrite_message_triggered",
    "on_actionRead_message_triggered",
    "on_actionClear_message_triggered",
    "on_actionSharpen_triggered",
    "on_actionEdge_Detection_triggered",
    "on_actionEmboss_triggered",
    "on_actionApply_Custom_Kernel_triggered",
    "on_actionImport_as_BMP_24_triggered"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  230,    2, 0x08,    1 /* Private */,
       4,    0,  233,    2, 0x08,    3 /* Private */,
       5,    0,  234,    2, 0x08,    4 /* Private */,
       6,    1,  235,    2, 0x08,    5 /* Private */,
       9,    0,  238,    2, 0x08,    7 /* Private */,
      10,    0,  239,    2, 0x08,    8 /* Private */,
      11,    0,  240,    2, 0x08,    9 /* Private */,
      12,    0,  241,    2, 0x08,   10 /* Private */,
      13,    0,  242,    2, 0x08,   11 /* Private */,
      14,    0,  243,    2, 0x08,   12 /* Private */,
      15,    0,  244,    2, 0x08,   13 /* Private */,
      16,    0,  245,    2, 0x08,   14 /* Private */,
      17,    0,  246,    2, 0x08,   15 /* Private */,
      18,    0,  247,    2, 0x08,   16 /* Private */,
      19,    0,  248,    2, 0x08,   17 /* Private */,
      20,    0,  249,    2, 0x08,   18 /* Private */,
      21,    0,  250,    2, 0x08,   19 /* Private */,
      22,    0,  251,    2, 0x08,   20 /* Private */,
      23,    0,  252,    2, 0x08,   21 /* Private */,
      24,    0,  253,    2, 0x08,   22 /* Private */,
      25,    0,  254,    2, 0x08,   23 /* Private */,
      26,    0,  255,    2, 0x08,   24 /* Private */,
      27,    0,  256,    2, 0x08,   25 /* Private */,
      28,    0,  257,    2, 0x08,   26 /* Private */,
      29,    0,  258,    2, 0x08,   27 /* Private */,
      30,    0,  259,    2, 0x08,   28 /* Private */,
      31,    0,  260,    2, 0x08,   29 /* Private */,
      32,    0,  261,    2, 0x08,   30 /* Private */,
      33,    0,  262,    2, 0x08,   31 /* Private */,
      34,    0,  263,    2, 0x08,   32 /* Private */,
      35,    0,  264,    2, 0x08,   33 /* Private */,
      36,    0,  265,    2, 0x08,   34 /* Private */,
      37,    0,  266,    2, 0x08,   35 /* Private */,
      38,    0,  267,    2, 0x08,   36 /* Private */,
      39,    0,  268,    2, 0x08,   37 /* Private */,
      40,    0,  269,    2, 0x08,   38 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'imageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'asyncJobStart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'asyncJobFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'formatDone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Image *, std::false_type>,
        // method 'on_actionOpen_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionSave_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionAbout_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionExit_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionZoom_in_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionZoom_out_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionReset_scale_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionUndo_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionRedo_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionRotate_90_plus_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionRotate_90_minus_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionFlip_horizontally_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_action_Flip_vertically_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionGrayscale_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionInvert_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionSepia_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionBlur_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionBrightness_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionContrast_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionColor_balance_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionConvert_to_1b_BMP_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionConvert_to_4b_BMP_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionConvert_to_8b_BMP_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionConvert_to_24b_BMP_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionWrite_message_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionRead_message_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionClear_message_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionSharpen_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionEdge_Detection_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionEmboss_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionApply_Custom_Kernel_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_actionImport_as_BMP_24_triggered'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->imageChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->asyncJobStart(); break;
        case 2: _t->asyncJobFinished(); break;
        case 3: _t->formatDone((*reinterpret_cast< std::add_pointer_t<Image*>>(_a[1]))); break;
        case 4: _t->on_actionOpen_triggered(); break;
        case 5: _t->on_actionSave_triggered(); break;
        case 6: _t->on_actionAbout_triggered(); break;
        case 7: _t->on_actionExit_triggered(); break;
        case 8: _t->on_actionZoom_in_triggered(); break;
        case 9: _t->on_actionZoom_out_triggered(); break;
        case 10: _t->on_actionReset_scale_triggered(); break;
        case 11: _t->on_actionUndo_triggered(); break;
        case 12: _t->on_actionRedo_triggered(); break;
        case 13: _t->on_actionRotate_90_plus_triggered(); break;
        case 14: _t->on_actionRotate_90_minus_triggered(); break;
        case 15: _t->on_actionFlip_horizontally_triggered(); break;
        case 16: _t->on_action_Flip_vertically_triggered(); break;
        case 17: _t->on_actionGrayscale_triggered(); break;
        case 18: _t->on_actionInvert_triggered(); break;
        case 19: _t->on_actionSepia_triggered(); break;
        case 20: _t->on_actionBlur_triggered(); break;
        case 21: _t->on_actionBrightness_triggered(); break;
        case 22: _t->on_actionContrast_triggered(); break;
        case 23: _t->on_actionColor_balance_triggered(); break;
        case 24: _t->on_actionConvert_to_1b_BMP_triggered(); break;
        case 25: _t->on_actionConvert_to_4b_BMP_triggered(); break;
        case 26: _t->on_actionConvert_to_8b_BMP_triggered(); break;
        case 27: _t->on_actionConvert_to_24b_BMP_triggered(); break;
        case 28: _t->on_actionWrite_message_triggered(); break;
        case 29: _t->on_actionRead_message_triggered(); break;
        case 30: _t->on_actionClear_message_triggered(); break;
        case 31: _t->on_actionSharpen_triggered(); break;
        case 32: _t->on_actionEdge_Detection_triggered(); break;
        case 33: _t->on_actionEmboss_triggered(); break;
        case 34: _t->on_actionApply_Custom_Kernel_triggered(); break;
        case 35: _t->on_actionImport_as_BMP_24_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 36;
    }
    return _id;
}
QT_WARNING_POP
