#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QMessageBox>

#include "UserManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class AddUserDialog;
}
QT_END_NAMESPACE

class AddUserDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();

    auto InitGui() -> void;
    auto SetUpEvent() -> void;
    auto AddUserDialog::Submit() -> void;

private:
    Ui::AddUserDialog *ui;

signals:
    void userAdded();

};

#endif // ADDUSERDIALOG_H
