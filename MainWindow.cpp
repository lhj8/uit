#include "MainWindow.h"
#include "./ui_MainWindow.h"

#define SUPERVISOR 0
#define ENGINEER 1
#define OPERATOR 2

struct MainWindow::Impl {
    UserManager::Pointer userManager{ nullptr };
    UserDatabase::Pointer userDataBase{ nullptr };
    SessionManager::Pointer sessionManager{ nullptr };
    MainWindow* p{ nullptr };
    Ui::MainWindow ui;

    //MainWindowControl *control;
  //   LiveView* liveView{ nullptr };
  //   OperationView* operationView{ nullptr };
  //   NavigationView* navigationView{ nullptr };
    Impl(MainWindow* p) : p{ p } {}

    auto Finalize() -> void;
    // auto ChangeViewMode(ViewMode& mode) -> void;
    auto ConfirmToExit() -> bool;
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), d{ std::make_unique<Impl>(this) }
{
    d->ui.setupUi(this);
    d->userDataBase = UserDatabase::GetInstance();
    d->userManager = UserManager::GetInstance();
    d->sessionManager = SessionManager::GetInstance();
    d->userDataBase->Load("C:/Users/HyungjoonLee/Desktop/usermanage/usrlist.ini");

    Initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

auto MainWindow::Initialize() -> void {
    setWindowTitle(QString("%1").arg("Tomo Pilot"));
    setMinimumSize(1024, 900);
    InitMenuBar();
}

auto MainWindow::InitMenuBar() -> void {
    QMenuBar *menuBar = this->menuBar();

    QMenu *fileMenu = menuBar->addMenu("File");
    QMenu *viewMenu = menuBar->addMenu("View");
    QMenu *systemMenu = menuBar->addMenu("System");
    QMenu *toolsMenu = menuBar->addMenu("Tools");
    QMenu *userMenu = menuBar->addMenu("User");
    QMenu *helpMenu = menuBar->addMenu("Help");

    QAction *openAction = new QAction("Manage", this);


    // "User" 메뉴에 Manage 액션 추가
    userMenu->addAction(openAction);
    this->SetupEvents(openAction);
}

auto MainWindow::SetupEvents(QAction* openAction) -> void {
    connect(openAction, &QAction::triggered, this, []() {
        
        if (SessionManager::GetInstance()->GetPrivilege() == SUPERVISOR) {
            qDebug() << "Supervisor Mode";
            
        }
        else if (SessionManager::GetInstance()->GetPrivilege() == ENGINEER) {
            qDebug() << "Engineer Mode";
        }
        else {
            qDebug() << "Operator Mode";
        }
        qDebug() << "User Manage 메뉴 선택됨";
    });
}



