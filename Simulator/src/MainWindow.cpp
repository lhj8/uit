#include "MainWindow.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

#include "ui_MainWindow.h"

struct StealthApp::Impl {
	StealthApp *p{ nullptr };
	Ui::StealthApp ui;
	
	Impl(StealthApp *p) : p{ p } {
		ui.setupUi(p);
	}
};

StealthApp::StealthApp(QWidget *parent) : QMainWindow(parent), d{ std::make_unique<Impl>(this) } {
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WA_OpaquePaintEvent);
	this->hide(); 

	QIcon icon("C:/Users/HyungjoonLee/Desktop/usermanage/logo.png");
	if (icon.isNull()) {
		qDebug() << "Failed to load icon";
	} else {
		qDebug() << "Icon loaded successfully";
	}

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(icon);
	trayIcon->setVisible(true);

	// Tray menu
	QMenu *trayMenu = new QMenu(this);
	QAction *manageAction = new QAction("Manage User", this);
	trayMenu->addAction(manageAction);
	trayIcon->setContextMenu(trayMenu);

	// 'Manage User' Action
	connect(manageAction, &QAction::triggered, this, [this]() {
		LoginWin *loginWin = new LoginWin(this);
		loginWin->show();
	});
}

StealthApp::~StealthApp() {
}

