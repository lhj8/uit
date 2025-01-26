#ifndef USERTREEWIDGET_H
#define USERTREEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

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

     
private:
    Ui::UserTreeWidget *ui;
};


#endif // USERTREEWIDGET_H
