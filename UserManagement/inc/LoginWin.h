#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QWidget>
#include <QDialog>
#include <QObject>
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>

// #include "UserManagementExport.h"


QT_BEGIN_NAMESPACE
namespace Ui {
    class LoginWin;
}
QT_END_NAMESPACE

class LoginWin : public QDialog {
	Q_OBJECT

public:
    explicit LoginWin(QWidget *parent = nullptr);
    ~LoginWin();
    auto InitGui() -> void;
    // auto SetupEvents() -> void;

private:
	struct Impl;
	std::unique_ptr<Impl> d;

private slots:
    // auto OnSubmitClicked() -> void;
};

#endif // LOGINWIDGET_H
