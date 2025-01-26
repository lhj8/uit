#include "UserDatabase.h"

struct UserDatabase::Impl {
    QString path;
    auto Write(const QList<User::Pointer>& users)->void;
};

namespace Field {
    constexpr char size[] = "SIZE";
    constexpr char id[] = "ID";
    constexpr char password[] = "PW";
    constexpr char privilege[] = "PV";
}

auto ReadField(QSettings& qs, const char key[]) -> QVariant {
    if (!qs.contains(key)) throw std::runtime_error(std::string("Missing key in user database: ") + key);
    return qs.value(key);
}

UserDatabase::UserDatabase() : d{ std::make_unique<Impl>() }  {}
UserDatabase::~UserDatabase() {};

auto UserDatabase::GetInstance() -> Pointer {
    static Pointer theInstance{ new UserDatabase() };
    return theInstance;
}

bool fileExists(const QString &filePath) {
    return QFile::exists(filePath);
}

auto UserDatabase::Load(const QString& path) -> bool {
    d->path = path;

    auto qs = QSettings(path, QSettings::IniFormat);

    fileExists(path) ? qDebug() << "File exists:" << path : qDebug() << "File does not exist:" << path;


    auto manager = UserManager::GetInstance();

    try {
        qs.beginGroup("USER COUNT");
        const int count = qs.value("COUNT").toInt();
        qs.endGroup();

        for(auto i = 0; i < count; ++i) {
            auto user = std::make_shared<User>();
            const QString userI = "User" + QString::number(i);
            qDebug() << "UserI: " << userI;
            qs.beginGroup(userI);
            user->SetUserID(ReadField(qs, Field::id).toString());
            user->SetPassword(ReadField(qs, Field::password).toString());
            user->SetPrivilege(ReadField(qs, Field::privilege).toInt());
            qs.endGroup();

            manager->AddUser(user);
        }
    } catch(std::exception& ex) {
        qDebug() << "It fails to read user database. Error = " << ex.what();
        qs.endArray();
        return false;
    }

    auto finfo = QFileInfo(d->path);
    auto dirPath = finfo.absolutePath();

    return true;
}

