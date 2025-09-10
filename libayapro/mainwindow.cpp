#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建界面
    _login_dlg = new Login(this);
    _register_dlg = new Register(this);
    _resetpw_dlg = new resetpw(this);

    // 设置窗口样式
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _register_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    // 创建堆叠窗口
    _stack = new QStackedWidget(this);
    _stack->addWidget(_login_dlg);     // index 0
    _stack->addWidget(_register_dlg);  // index 1
    _stack->addWidget(_resetpw_dlg);
    setCentralWidget(_stack);

    // 信号槽绑定
    connect(_login_dlg, &Login::switchRegister, this, &MainWindow::SlotSwitchReg);
    connect(_login_dlg, &Login::switchResetpw, this, &MainWindow::SlotSwitchReset);
    connect(_login_dlg, &Login::switchChat, this, &MainWindow::SlotSwitchChat);
    connect(_register_dlg, &Register::switchLogin, this, &MainWindow::SlotSwitchLog);
    connect(_resetpw_dlg, &resetpw::switchLogin, this, &MainWindow::SlotSwitchLog);


    // 初始显示登录界面
    _stack->setCurrentWidget(_login_dlg);
}

void MainWindow::SlotSwitchReg()
{
    _stack->setCurrentWidget(_register_dlg);
    _register_dlg->resetToPage1();
}

void MainWindow::SlotSwitchLog()
{
    _stack->setCurrentWidget(_login_dlg);
}

void MainWindow::SlotSwitchReset()
{
    _stack->setCurrentWidget(_resetpw_dlg);
    _resetpw_dlg->resetToPage1();
}

void MainWindow::SlotSwitchChat()
{

}



MainWindow::~MainWindow()
{
    delete ui;
}

