#ifndef USERTREEWIDGET_H
#define USERTREEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

#include "AddUserDialog.h"
#include "UserManager.h"
#include "UserDatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class UserTreeWidget;
}
QT_END_NAMESPACE

class UserTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserTreeWidget(QWidget *parent = nullptr);
    ~UserTreeWidget();

    auto InitGui() -> void;
    auto InitTreeWidgetGroups() -> void;
    auto LoadUsers() -> void;
    auto SetUpEvent() -> void;
    auto GetGroup(uint8_t privilege) const -> QTreeWidgetItem*;
    auto SaveUsersToIni() -> void;
private:
    Ui::UserTreeWidget *ui;
    QTreeWidgetItem *supervisorGroup;
    QTreeWidgetItem *engineerGroup;
    QTreeWidgetItem *operatorGroup;
};


#endif // USERTREEWIDGET_H
