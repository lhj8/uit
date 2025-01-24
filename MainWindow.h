#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "UserManager.h"
#include "UserDatabase.h"
#include "User.h"
#include "SessionManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    auto Initialize() -> void;
    auto InitMenuBar() -> void;
    auto SetupEvents(QAction* openAction) -> void;

private:
    Ui::MainWindow *ui;

    struct Impl;
    std::unique_ptr<Impl> d;
};
#endif // MAINWINDOW_H
