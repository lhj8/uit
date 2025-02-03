#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QSystemTrayIcon>
// #include <LoginWin.h>

namespace Ui {
	class StealthApp;
}

class StealthApp : public QMainWindow {
	Q_OBJECT

public:
	explicit StealthApp(QWidget *parent = nullptr);
	~StealthApp() override;

private:
	QSystemTrayIcon *trayIcon;
	struct Impl;
	std::unique_ptr<Impl> d;
};

#endif	// MAINWINDOW_H
