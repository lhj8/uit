#include "loginwidget.h"
#include "./ui_LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    SetupEvents();
}

LoginWidget::~LoginWidget() {
    delete ui;
}


auto LoginWidget::SetupEvents() -> void {
    connect(ui->SubmitBtn, &QPushButton::clicked, this, &LoginWidget::OnSubmitClicked);
}


auto LoginWidget::OnSubmitClicked() -> void {
    const auto userManager = UserManager::GetInstance();
    const auto sessionManager = SessionManager::GetInstance();

    const auto id = ui->inputID->text();
    const auto password = ui->inputPassword->text();

    const auto user = userManager->GetUser(id);

    if (id.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, tr("User Login"), tr("Please fill all fields"));
        return;
    }
    
    if (user == nullptr) {  // user가 nullptr일 경우 처리
        QMessageBox::warning(this, tr("User Login"), tr("User Not found"));
        return; 
    }

    const auto storedID = user->GetUserID();
    const auto storedPW = user->GetPassword();
    const auto storedPV = user->GetPrivilege();

    sessionManager->Login(user);

    QMap<uint8_t, QString> qm;
    qm.insert(0, "Supervisor");
    qm.insert(1, "Engineer");
    qm.insert(2, "Operator");

    if (id == storedID && password == storedPW) {
        QMessageBox::information(nullptr, "Authenticated", QString("Welcome %1!").arg(qm[storedPV]));
        this->accept();
    } else {
        QMessageBox::warning(this, tr("User Login"), tr("Wrong Password"));
        return;
    }
}

