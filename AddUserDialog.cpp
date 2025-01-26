#include "AddUserDialog.h"
#include "./ui_AddUserDialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) 
    : QDialog(parent), ui(new Ui::AddUserDialog) 
{
    ui->setupUi(this);
    InitGui();
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
