#include "SessionManager.h"

struct SessionManager::Impl {
    User::Pointer user;
};

SessionManager::SessionManager() : d{ std::make_unique<Impl>() } {
}

SessionManager::~SessionManager() {
}

auto SessionManager::GetInstance() -> Pointer {
    static Pointer theInstance{ new SessionManager() };
    return theInstance;
}

auto SessionManager::Login(const User::Pointer& user) -> void {
    d->user = user;
}

auto SessionManager::Logout() -> void {
    d->user = nullptr;
}

auto SessionManager::LoggedIn() const -> bool {
    return (d->user != nullptr);
}

auto SessionManager::GetID() const -> QString {
    if(d->user == nullptr) return QString();
    return d->user->GetUserID();
}

auto SessionManager::GetPrivilege() const -> uint8_t {
    if(d->user == nullptr) return 2;
    return d->user->GetPrivilege();
}
