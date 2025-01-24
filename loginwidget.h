#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QApplication>
#include <QMessageBox>
#include "UserManager.h"
#include "SessionManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class LoginWidget;
}
QT_END_NAMESPACE

class LoginWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    auto SetupEvents() -> void;

private:
    Ui::LoginWidget *ui;

private slots:
    auto OnSubmitClicked() -> void;
};

#endif // LOGINWIDGET_H
