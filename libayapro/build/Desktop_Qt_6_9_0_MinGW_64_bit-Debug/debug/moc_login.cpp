/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../login.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
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
struct qt_meta_tag_ZN5LoginE_t {};
} // unnamed namespace

template <> constexpr inline auto Login::qt_create_metaobjectdata<qt_meta_tag_ZN5LoginE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Login",
        "switchRegister",
        "",
        "switchResetpw",
        "switchChat",
        "sig_tcp_connect",
        "ServerInfo",
        "sig_send_data",
        "ReqId",
        "slot_http_finish",
        "id",
        "res",
        "ErrorCodes",
        "err",
        "slot_tcp_finish",
        "success",
        "slot_login_finish",
        "len",
        "on_login_Button_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'switchRegister'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'switchResetpw'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'switchChat'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_tcp_connect'
        QtMocHelpers::SignalData<void(ServerInfo)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 2 },
        }}),
        // Signal 'sig_send_data'
        QtMocHelpers::SignalData<void(ReqId, QByteArray)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 2 }, { QMetaType::QByteArray, 2 },
        }}),
        // Slot 'slot_http_finish'
        QtMocHelpers::SlotData<void(ReqId, QString, ErrorCodes)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 10 }, { QMetaType::QString, 11 }, { 0x80000000 | 12, 13 },
        }}),
        // Slot 'slot_tcp_finish'
        QtMocHelpers::SlotData<void(bool)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 15 },
        }}),
        // Slot 'slot_login_finish'
        QtMocHelpers::SlotData<void(ReqId, int, QByteArray)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 8, 10 }, { QMetaType::Int, 17 }, { QMetaType::QByteArray, 11 },
        }}),
        // Slot 'on_login_Button_clicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Login, qt_meta_tag_ZN5LoginE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Login::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5LoginE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5LoginE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5LoginE_t>.metaTypes,
    nullptr
} };

void Login::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Login *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->switchRegister(); break;
        case 1: _t->switchResetpw(); break;
        case 2: _t->switchChat(); break;
        case 3: _t->sig_tcp_connect((*reinterpret_cast< std::add_pointer_t<ServerInfo>>(_a[1]))); break;
        case 4: _t->sig_send_data((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2]))); break;
        case 5: _t->slot_http_finish((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<ErrorCodes>>(_a[3]))); break;
        case 6: _t->slot_tcp_finish((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->slot_login_finish((*reinterpret_cast< std::add_pointer_t<ReqId>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[3]))); break;
        case 8: _t->on_login_Button_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Login::*)()>(_a, &Login::switchRegister, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Login::*)()>(_a, &Login::switchResetpw, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Login::*)()>(_a, &Login::switchChat, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Login::*)(ServerInfo )>(_a, &Login::sig_tcp_connect, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Login::*)(ReqId , QByteArray )>(_a, &Login::sig_send_data, 4))
            return;
    }
}

const QMetaObject *Login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Login::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5LoginE_t>.strings))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Login::switchRegister()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Login::switchResetpw()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Login::switchChat()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Login::sig_tcp_connect(ServerInfo _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Login::sig_send_data(ReqId _t1, QByteArray _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}
QT_WARNING_POP
