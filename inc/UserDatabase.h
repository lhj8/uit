#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QList>
#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include <memory>
#include "User.h"
#include "UserManager.h"

class UserDatabase
{
public:
    using Pointer = std::shared_ptr<UserDatabase>;

public:
    UserDatabase();
    ~UserDatabase();

    auto Load(const QString& path)->bool;
    static auto GetInstance()->Pointer;

private:
    struct Impl;
    std::unique_ptr<Impl> d;
};
#endif // USERDATABASE_H
