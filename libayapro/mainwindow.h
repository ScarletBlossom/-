#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "register.h"
#include "resetpw.h"
#include <QStackedWidget>
/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      XXXX Function
 *
 * @author     Libaya
 * @date       2025/05/26
 * @history
 *****************************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void SlotSwitchReg();
    void SlotSwitchLog();
    void SlotSwitchReset();
    void SlotSwitchChat();

private:
    Ui::MainWindow *ui;
    Login * _login_dlg;
    Register * _register_dlg;
    QStackedWidget * _stack;
    resetpw * _resetpw_dlg;

};
#endif // MAINWINDOW_H
