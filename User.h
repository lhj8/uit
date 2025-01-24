#ifndef USER_H
#define USER_H

#include <QString>
#include <memory>

class User
{
public:
    typedef std::shared_ptr<User> Pointer;

public:
    User();
    User(const User& other);
    virtual ~User();

    auto operator=(const User& other) ->User&;
    auto operator==(const User& other) const->bool;

    auto SetUserID(QString id) -> void;
    auto GetUserID() const -> QString;

    auto SetPassword(const QString& name) -> void;
    auto GetPassword() const -> QString;

    auto SetPrivilege(uint8_t privilege) -> void;
    auto GetPrivilege() const -> uint8_t;

private:
    struct Impl;
    std::unique_ptr<Impl> d;
};

#endif // USER_H
