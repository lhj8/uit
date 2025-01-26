#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QWidget>

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


private:
    Ui::AddUserDialog *ui;

};

#endif // ADDUSERDIALOG_H
