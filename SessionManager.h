#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "user.h"

class SessionManager
{
public:
    typedef std::shared_ptr<SessionManager> Pointer;

private:
    SessionManager();

public:
    ~SessionManager();

    static auto GetInstance()->Pointer;

    auto Login(const User::Pointer& user) -> void;
    auto Logout() -> void;
    auto LoggedIn() const -> bool;

    auto GetID() const -> QString;
    auto GetPrivilege() const -> uint8_t;

private:
    struct Impl;
    std::unique_ptr<Impl> d;
};


#endif // SESSIONMANAGER_H
