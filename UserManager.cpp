#include "UserManager.h"

struct UserManager::Impl {
private:
    QMap<QString, User::Pointer> users;
    QStringList builtInAccounts{};

public:
    auto Contains(const User::Pointer& user)->bool;
    auto AddUser(const User::Pointer& user)->void;
    auto GetUser(QString id)->User::Pointer;
    auto RemoveUser(QString id)->void;
    auto GetUsers() const -> QList<User::Pointer>;
    auto CreateDefault()->void;
    auto IsBuiltInAccount(const QString& id) const->bool;
};

auto UserManager::Impl::Contains(const User::Pointer& user) -> bool {
    return users.contains(user->GetUserID().toUpper());
}

auto UserManager::Impl::AddUser(const User::Pointer& user) -> void {
    users[user->GetUserID().toUpper()] = user;
}

auto UserManager::Impl::GetUser(QString id) -> User::Pointer {
    auto itr = users.find(id.toUpper());
    if(itr == users.end()) return nullptr;
    return *itr;
}

auto UserManager::Impl::RemoveUser(QString id) -> void {
    users.remove(id.toUpper());
}

auto UserManager::Impl::GetUsers() const -> QList<User::Pointer> {
    return users.values();
}

auto UserManager::Impl::CreateDefault() -> void {
    // auto user = std::make_shared<User>();
    // user->SetUserID("Default");
    // user->SetName("Default User");
    // user->SetProfile(AppEntity::Profile::Operator);
    // builtInAccounts.append(user->GetUserID());
    // users[user->GetUserID().toUpper()] = user;

    // user = std::make_shared<AppEntity::User>();
    // user->SetUserID("Service");
    // user->SetName("Service Engineer");
    // user->SetProfile(AppEntity::Profile::ServiceEngineer);
    // builtInAccounts.append(user->GetUserID());
    // users[user->GetUserID().toUpper()] = user;
}

auto UserManager::Impl::IsBuiltInAccount(const QString& id) const -> bool {
    return builtInAccounts.contains(id, Qt::CaseInsensitive);
}

UserManager::UserManager() : d{ std::make_unique<Impl>() } {
}

UserManager::~UserManager() {
}

auto UserManager::GetInstance() -> Pointer {
    static Pointer theInstance{ new UserManager() };
    return theInstance;
}

auto UserManager::AddUser(const User::Pointer user) -> bool {
    if(d->Contains(user)) return false;
    d->AddUser(user);
    return true;
}

auto UserManager::GetUser(QString id) const -> User::Pointer {
    return d->GetUser(id);
}

auto UserManager::GetUsers() const -> QList<User::Pointer> {
    return d->GetUsers();
}

auto UserManager::DeleteUser(QString id) -> void {
    d->RemoveUser(id);
}

auto UserManager::IsBuiltInAccount(const QString& id) const -> bool {
    return d->IsBuiltInAccount(id);
}
