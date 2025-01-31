#include "UserTreeWidget.h"
#include "ui_UserTreeWidget.h"
#include <QDebug>

#define SUPERVISOR 0
#define ENGINEER 1
#define OPERATOR 2

UserTreeWidget::UserTreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserTreeWidget)
{
    ui->setupUi(this); 
    InitGui();  
}

UserTreeWidget::~UserTreeWidget() {
    delete ui;
}

auto UserTreeWidget::InitGui() -> void {
    InitTreeWidgetGroups();
    LoadUsers();
    SetUpEvent();
}

auto UserTreeWidget::InitTreeWidgetGroups() -> void {
    ui->userTreeWidget->setHeaderLabels({"Group"}); 
    
    supervisorGroup = new QTreeWidgetItem(ui->userTreeWidget);
    supervisorGroup->setText(0, "Supervisor");

    engineerGroup = new QTreeWidgetItem(ui->userTreeWidget);
    engineerGroup->setText(0, "Engineer");

    operatorGroup = new QTreeWidgetItem(ui->userTreeWidget);
    operatorGroup->setText(0, "Operator");
}


auto UserTreeWidget::LoadUsers() -> void {    
    auto userManager = UserManager::GetInstance();
    auto users = userManager->GetUsers();

    for (const auto &user : users) {
        QString userId = user->GetUserID();
        uint8_t privilege = user->GetPrivilege();
        qm.insert(userId, user);
        QTreeWidgetItem *groupItem = nullptr;

        switch (privilege) {
            case SUPERVISOR:
                groupItem = supervisorGroup;
                break;
            case ENGINEER:
                groupItem = engineerGroup;
                break;
            case OPERATOR:
                groupItem = operatorGroup;
                break;
            default:
                groupItem = nullptr;
                break;
        }

        if (groupItem) {
            QTreeWidgetItem *userItem = new QTreeWidgetItem(groupItem);
            userItem->setText(0, userId);  
        }
    }
}

auto UserTreeWidget::GetGroup(uint8_t privilege) const -> QTreeWidgetItem* {
    switch (privilege) {
        case SUPERVISOR:
            return supervisorGroup;
        case ENGINEER:
            return engineerGroup;
        case OPERATOR:
            return operatorGroup;
        default:
            return nullptr;
    }
}

auto UserTreeWidget::SetUpEvent() -> void {
    connect(ui->addBtn, &QPushButton::clicked, this, [this]() {
        AddUserDialog *addUserDialog = new AddUserDialog(this);
        addUserDialog->exec();
    });

    connect(ui->deleteBtn, &QPushButton::clicked, this, [this]() {
        auto selectedItems = ui->userTreeWidget->selectedItems();
        if (selectedItems.size() == 0) {
            QMessageBox::warning(this, "Delete User", "Please select a user to delete.");
            return;
        }

        QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete User", 
                                                                  "Are you sure you want to delete the selected user(s)?", 
                                                                  QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            auto userManager = UserManager::GetInstance();
            for (const auto &item : selectedItems) {
                QString userId = item->text(0);  
                userManager->DeleteUser(userId);
                delete item;  // 선택된 항목을 트리에서 삭제
            }

            QMessageBox::information(this, "Success", "Selected user(s) have been deleted.");
        }
    });

    connect(ui->saveBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Save User", "Would you like to save?", 
                                                              QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // 사용자가 'Yes'를 클릭한 경우: 저장
            SaveUsersToIni();
            QMessageBox::information(this, "Success", "Successfully saved,.", QMessageBox::Yes);
            this->close();
        } else {
            // 사용자가 'No'를 클릭한 경우: 아무 동작 안 함
        }
    });
}

auto UserTreeWidget::SaveUsersToIni() -> void {
    const auto userManager = UserManager::GetInstance();
    const auto users = userManager->GetUsers();
    const int userCount = users.size();
    
    QSettings qs("C:/Users/HyungjoonLee/Desktop/usermanage/usrlist.ini", QSettings::IniFormat);
    qs.clear();

    qs.setValue("USER COUNT/COUNT", userCount);

    for (int i = 0; i < userCount; ++i) {
        QString id = users[i]->GetUserID();
        QString password = users[i]->GetPassword();
        uint8_t privilege = users[i]->GetPrivilege();

        qs.setValue(QString("User%1/ID").arg(i), id);
        qs.setValue(QString("User%1/PW").arg(i), password);
        qs.setValue(QString("User%1/PV").arg(i), privilege);
    }
}

