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
    ui->userTreeWidget->setHeaderLabels({"Group"}); 
    
    supervisorGroup = new QTreeWidgetItem(ui->userTreeWidget);
    supervisorGroup->setText(0, "Supervisor");

    engineerGroup = new QTreeWidgetItem(ui->userTreeWidget);
    engineerGroup->setText(0, "Engineer");

    operatorGroup = new QTreeWidgetItem(ui->userTreeWidget);
    operatorGroup->setText(0, "Operator");
    
    LoadUsers();
}


auto UserTreeWidget::LoadUsers() -> void {
    auto userManager = UserManager::GetInstance();
    auto users = userManager->GetUsers();

    for (const auto &user : users) {
        QString userId = user->GetUserID();
        uint8_t privilege = user->GetPrivilege();
        qDebug() << "User ID: " << userId << " Privilege: " << privilege;   

        // 해당 Privilege에 맞는 그룹에 사용자 추가
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

