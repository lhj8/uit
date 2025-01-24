#include "User.h"

struct User::Impl {
    QString id;
    QString pw;
    uint8_t pv;

    auto operator=(const Impl& other)->Impl&;
    auto operator==(const Impl& other)->bool;
};

auto User::Impl::operator=(const Impl& other) -> Impl& {
    id = other.id;
    pw = other.pw;
    pv = other.pv;
    return (*this);
}

auto User::Impl::operator==(const Impl& other) -> bool {
    return id == other.id && pw == other.pw && pv == other.pv;
}

User::User() : d{ std::make_unique<Impl>() } {
}

User::User(const User& other) :d{ std::make_unique<Impl>() } {
    *d = *other.d;
}

User::~User() {
}

auto User::operator=(const User& other) -> User& {
    *d = *other.d;
    return (*this);
}

auto User::operator==(const User& other) const -> bool {
    return (*d == *other.d);
}

auto User::SetUserID(QString id) -> void {
    d->id = id;
}

auto User::GetUserID() const -> QString {
    return d->id;
}

auto User::SetPassword(const QString& password) -> void {
    d->pw = password;
}

auto User::GetPassword() const -> QString {
    return d->pw;
}

auto User::SetPrivilege(uint8_t privilege) -> void {
    d->pv = privilege;
}

auto User::GetPrivilege() const -> uint8_t {
    return d->pv;
}

