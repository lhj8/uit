#include "UserTreeWidget.h"
#include "ui_UserTreeWidget.h"

UserTreeWidget::UserTreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserTreeWidget)
{
    ui->setupUi(this);   
}

UserTreeWidget::~UserTreeWidget() {
    delete ui;
}
