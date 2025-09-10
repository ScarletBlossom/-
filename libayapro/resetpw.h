#ifndef RESETPW_H
#define RESETPW_H

#include <QDialog>
#include <QTimer>
#include "global.h"
namespace Ui {
class resetpw;
}

class resetpw : public QDialog
{
    Q_OBJECT

public:
    explicit resetpw(QWidget *parent = nullptr);
    ~resetpw();
    void ChangeTipPage();
    void initHttpHandlers();
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    void resetToPage1();

signals:
    void switchLogin();
private slots:
    void on_cancel_button_clicked();

    void on_return_button_clicked();
    void slot_changepw_mod_finish(ReqId id, QString res, ErrorCodes err);

    void on_verifycode_button_clicked();

    void on_confirm_button_clicked();

private:
    Ui::resetpw *ui;

    bool checkUserValid();

    bool checkEmailValid();

    bool checkPWValid();

    bool checkPWagainValid();

    bool checkVerifycodeValid();

    QTimer *_count_timer;
    int _count;
    void showTip(QString str,bool);
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr, QString> _tip_errs;

};

#endif // RESETPW_H
