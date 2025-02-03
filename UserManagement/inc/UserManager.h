#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QList>
#include <QString>
#include "User.h"

#include <QMap>

class UserManager
{
public:
    typedef std::shared_ptr<UserManager> Pointer;

private:
    UserManager();

public:
    ~UserManager();

    static auto GetInstance()->Pointer;

    auto AddUser(const User::Pointer user)->bool;
    auto GetUser(QString id) const->User::Pointer;
    auto GetUsers() const->QList<User::Pointer>;

    auto DeleteUser(QString id)->void;

    auto IsBuiltInAccount(const QString& id) const->bool;

private:
    struct Impl;
    std::unique_ptr<Impl> d;
};

#endif // USERMANAGER_H
