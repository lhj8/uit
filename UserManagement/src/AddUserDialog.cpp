#include "AddUserDialog.h"
#include "UserTreeWidget.h"
#include "./ui_AddUserDialog.h"

#define SUPERVISOR 0
#define ENGINEER 1
#define OPERATOR 2

AddUserDialog::AddUserDialog(QWidget *parent) 
    : QDialog(parent), ui(new Ui::AddUserDialog) 
{
    ui->setupUi(this);
    InitGui();
    SetUpEvent();
}

AddUserDialog::~AddUserDialog() {
    delete ui;
}

auto AddUserDialog::InitGui() -> void {
    ui->idLineEdit->setPlaceholderText("Enter User Name");
    ui->passwordLineEdit->setPlaceholderText("Enter Password");
    ui->privilegeComboBox->addItem("Supervisor");
    ui->privilegeComboBox->addItem("Engineer");
    ui->privilegeComboBox->addItem("Operator");
}

auto AddUserDialog::Submit() -> void {
    auto userManager = UserManager::GetInstance();

    QString userId = ui->idLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    uint8_t privilege = ui->privilegeComboBox->currentIndex();

    if (userId.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please fill all fields");
    }

    if (userManager->GetUser(userId) != nullptr) {
        QMessageBox::warning(this, "Warning", "User already exists");
    }
    else {
        auto user = std::make_shared<User>();
        user->SetUserID(userId);
        user->SetPassword(password);
        user->SetPrivilege(privilege);
        userManager->AddUser(user);
        
        // QTreeWidget 추가 로직
        UserTreeWidget* parentWidget = qobject_cast<UserTreeWidget*>(parent());
        if (parentWidget) {
            QTreeWidgetItem *groupItem  = parentWidget->GetGroup(privilege);

            if (groupItem) {
                QTreeWidgetItem *userItem = new QTreeWidgetItem(groupItem);
                userItem->setText(0, userId); 
            }
        }       
        QMessageBox::information(this, "Success", "User added successfully");
        this->accept();
    }
}

auto AddUserDialog::SetUpEvent() -> void {
    connect(ui->submitBtn, &QPushButton::clicked, this, &AddUserDialog::Submit);
}
