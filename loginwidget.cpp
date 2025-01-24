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
    const auto storedID = userManager->GetUser(id)->GetUserID();
    const auto storedPW = userManager->GetUser(id)->GetPassword();
    const auto storedPV = userManager->GetUser(id)->GetPrivilege();

    sessionManager->Login(userManager->GetUser(id));

    QMap<uint8_t, QString> qm;
    qm.insert(0, "Supervisor");
    qm.insert(1, "Enineer");
    qm.insert(2, "Operator");

    if (id == storedID && password == storedPW) {
        QMessageBox::information(nullptr, "Authenticated", QString("Welcome %1!").arg(qm[storedPV]));
        this->accept();
    }
    else {
        QMessageBox::warning(this, tr("User Login"), tr("Password Wrong or User Not found"));
    }
}
