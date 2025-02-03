#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QSystemTrayIcon>

namespace Ui {
	class StealthApp;
}

class StealthApp : public QMainWindow {
	Q_OBJECT

public:
	explicit StealthApp(QWidget *parent = nullptr);
	~StealthApp() override;

public slots:
	void ShowWindow();

private:
	QSystemTrayIcon *trayIcon;
	struct Impl;
	std::unique_ptr<Impl> d;
};

#endif	// MAINWINDOW_H
