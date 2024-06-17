/****************************************************************************
** Meta object code from reading C++ file 'gui_psd.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../gui_psd.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_psd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
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
struct qt_meta_stringdata_CLASSgui_psdENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSgui_psdENDCLASS = QtMocHelpers::stringData(
    "gui_psd",
    "updatedataTable",
    "",
    "update_scope",
    "update_sigmaPlot",
    "update_sigmaProgressBar",
    "record_button_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSgui_psdENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[8];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[17];
    char stringdata5[24];
    char stringdata6[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSgui_psdENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSgui_psdENDCLASS_t qt_meta_stringdata_CLASSgui_psdENDCLASS = {
    {
        QT_MOC_LITERAL(0, 7),  // "gui_psd"
        QT_MOC_LITERAL(8, 15),  // "updatedataTable"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 12),  // "update_scope"
        QT_MOC_LITERAL(38, 16),  // "update_sigmaPlot"
        QT_MOC_LITERAL(55, 23),  // "update_sigmaProgressBar"
        QT_MOC_LITERAL(79, 21)   // "record_button_clicked"
    },
    "gui_psd",
    "updatedataTable",
    "",
    "update_scope",
    "update_sigmaPlot",
    "update_sigmaProgressBar",
    "record_button_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSgui_psdENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    0,   46,    2, 0x0a,    3 /* Public */,
       5,    0,   47,    2, 0x0a,    4 /* Public */,
       6,    0,   48,    2, 0x0a,    5 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject gui_psd::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSgui_psdENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSgui_psdENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSgui_psdENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<gui_psd, std::true_type>,
        // method 'updatedataTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'update_scope'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'update_sigmaPlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'update_sigmaProgressBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'record_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void gui_psd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<gui_psd *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updatedataTable(); break;
        case 1: _t->update_scope(); break;
        case 2: _t->update_sigmaPlot(); break;
        case 3: _t->update_sigmaProgressBar(); break;
        case 4: _t->record_button_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *gui_psd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gui_psd::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSgui_psdENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int gui_psd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
