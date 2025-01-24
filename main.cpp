#include <QApplication>
#include <QSystemTrayIcon>
#include <QDialog>
#include <QDir>

#include "MainWindow.h"
#include "loginwidget.h"
#include "SessionManager.h"

void CreateTrayIcon() {
    QSystemTrayIcon trayIcon;

    trayIcon.setIcon(QIcon(":/logo.png"));
    trayIcon.setVisible(true);
}

int main(int argc, char *argv[])
{
    QString currentDir = QDir::currentPath();
    qDebug() << "Current working directory: " << currentDir;

    QApplication a(argc, argv);
    LoginWidget *l = new LoginWidget();
    MainWindow *w = new MainWindow();

    if (l->exec() == QDialog::Accepted) {
        w->show();
    }

    return a.exec();
}
