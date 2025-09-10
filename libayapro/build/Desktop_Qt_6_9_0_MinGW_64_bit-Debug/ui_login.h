/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout_7;
    QWidget *widget;
    QLabel *head_label;
    QHBoxLayout *horizontalLayout;
    QLabel *user_label;
    QLineEdit *user_edit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *pw_label;
    QLineEdit *pw_edit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *forgetButton;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *login_Button;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *RegisterButton;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->setEnabled(true);
        Login->resize(400, 600);
        Login->setMinimumSize(QSize(400, 600));
        Login->setMaximumSize(QSize(400, 600));
        verticalLayout_2 = new QVBoxLayout(Login);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        err_tip = new QLabel(Login);
        err_tip->setObjectName("err_tip");
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(err_tip);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        widget = new QWidget(Login);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(300, 300));
        widget->setMaximumSize(QSize(300, 300));
        widget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        head_label = new QLabel(widget);
        head_label->setObjectName("head_label");
        head_label->setGeometry(QRect(50, 40, 200, 200));
        head_label->setMinimumSize(QSize(200, 200));
        head_label->setMaximumSize(QSize(200, 200));
        head_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_7->addWidget(widget);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        user_label = new QLabel(Login);
        user_label->setObjectName("user_label");
        user_label->setMinimumSize(QSize(0, 25));
        user_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_label);

        user_edit = new QLineEdit(Login);
        user_edit->setObjectName("user_edit");
        user_edit->setMinimumSize(QSize(0, 25));
        user_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_edit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        pw_label = new QLabel(Login);
        pw_label->setObjectName("pw_label");
        pw_label->setMinimumSize(QSize(0, 25));
        pw_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(pw_label);

        pw_edit = new QLineEdit(Login);
        pw_edit->setObjectName("pw_edit");
        pw_edit->setMinimumSize(QSize(0, 25));
        pw_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(pw_edit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(6, 0, 6, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        forgetButton = new QPushButton(Login);
        forgetButton->setObjectName("forgetButton");
        forgetButton->setMinimumSize(QSize(125, 25));
        forgetButton->setMaximumSize(QSize(125, 25));

        horizontalLayout_3->addWidget(forgetButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(6, 6, 6, 6);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        login_Button = new QPushButton(Login);
        login_Button->setObjectName("login_Button");
        login_Button->setMinimumSize(QSize(100, 30));
        login_Button->setMaximumSize(QSize(100, 30));

        horizontalLayout_4->addWidget(login_Button);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(5);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(6, 6, 6, 6);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        RegisterButton = new QPushButton(Login);
        RegisterButton->setObjectName("RegisterButton");
        RegisterButton->setMinimumSize(QSize(100, 30));
        RegisterButton->setMaximumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(RegisterButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        err_tip->setText(QCoreApplication::translate("Login", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        head_label->setText(QString());
        user_label->setText(QCoreApplication::translate("Login", "username:", nullptr));
        pw_label->setText(QCoreApplication::translate("Login", "password:", nullptr));
        forgetButton->setText(QCoreApplication::translate("Login", "Forget Password?", nullptr));
        login_Button->setText(QCoreApplication::translate("Login", "Login", nullptr));
        RegisterButton->setText(QCoreApplication::translate("Login", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
