#ifndef REGISTER_H
#define REGISTER_H
#include "global.h"
#include <QDialog>
#include <QTimer>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

    QMap<TipErr, QString> _tip_errs;

    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    void ChangeTipPage();
    void resetToPage1();

private slots:
    void on_verifyButton_clicked();
    void slot_reg_mod_finish(ReqId id, QString res,ErrorCodes err);

    void on_confirm_button_clicked();


    void on_return_login_clicked();

    void on_cancel_button_clicked();

private:
    void initHttpHandlers();
    Ui::Register *ui;
    void showTip(QString str,bool);
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    bool checkUserValid();

    bool checkEmailValid();

    bool checkPWValid();

    bool checkPWagainValid();

    bool checkVerifycodeValid();
    QTimer* _count_timer;
    int _count;
signals:
    void switchLogin();

};



#endif // REGISTER_H
