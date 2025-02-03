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
	this->hide();  // 윈도우를 숨김

	QIcon icon("C:/Users/HyungjoonLee/Desktop/usermanage/logo.png");
	if (icon.isNull()) {
		qDebug() << "Failed to load icon";
	} else {
		qDebug() << "Icon loaded successfully";
	}

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(icon);
	trayIcon->setVisible(true);

	// 트레이 메뉴를 만듭니다.
	QMenu *trayMenu = new QMenu(this);
	QAction *showAction = new QAction("Show", this);
	QAction *quitAction = new QAction("Quit", this);
	trayMenu->addAction(showAction);
	trayMenu->addAction(quitAction);

	// 메뉴를 트레이 아이콘에 연결합니다.
	trayIcon->setContextMenu(trayMenu);

	// 'Show' 액션에 대한 슬롯 연결
	connect(showAction, &QAction::triggered, this, &StealthApp::ShowWindow);
	connect(quitAction, &QAction::triggered, this, &QApplication::quit);
}

StealthApp::~StealthApp() {
}

void StealthApp::ShowWindow() {
	this->show();
	this->raise();
	this->activateWindow();	 
}
