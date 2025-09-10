/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedlabel.h>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout_6;
    QLabel *user_label;
    QLineEdit *user_edit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *email_label;
    QLineEdit *email_edit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *pw_label;
    QLineEdit *pw_edit;
    ClickedLabel *pw_visible;
    QHBoxLayout *horizontalLayout_3;
    QLabel *pwagain_label;
    QLineEdit *pwagain_edit;
    ClickedLabel *pwagain_visible;
    QHBoxLayout *horizontalLayout_2;
    QLabel *verifycode_label;
    QLineEdit *verifycode_edit;
    QPushButton *verifyButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *confirm_button;
    QPushButton *cancel_button;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_5;
    QLabel *return_label;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *return_login;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->resize(400, 600);
        Register->setMinimumSize(QSize(400, 600));
        Register->setMaximumSize(QSize(400, 600));
        verticalLayout = new QVBoxLayout(Register);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(Register);
        stackedWidget->setObjectName("stackedWidget");
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        layoutWidget = new QWidget(page_1);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 381, 581));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        widget = new QWidget(layoutWidget);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 30));
        widget->setMaximumSize(QSize(16777215, 30));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        err_tip = new QLabel(widget);
        err_tip->setObjectName("err_tip");
        err_tip->setMinimumSize(QSize(0, 30));
        err_tip->setMaximumSize(QSize(16777215, 30));
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(err_tip);


        verticalLayout_2->addWidget(widget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(5);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(6, 6, 6, 6);
        user_label = new QLabel(layoutWidget);
        user_label->setObjectName("user_label");
        user_label->setMinimumSize(QSize(75, 25));
        user_label->setMaximumSize(QSize(75, 25));

        horizontalLayout_6->addWidget(user_label);

        user_edit = new QLineEdit(layoutWidget);
        user_edit->setObjectName("user_edit");
        user_edit->setMinimumSize(QSize(0, 25));
        user_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(user_edit);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(5);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(6, 6, 6, 6);
        email_label = new QLabel(layoutWidget);
        email_label->setObjectName("email_label");
        email_label->setMinimumSize(QSize(75, 25));
        email_label->setMaximumSize(QSize(75, 25));

        horizontalLayout_5->addWidget(email_label);

        email_edit = new QLineEdit(layoutWidget);
        email_edit->setObjectName("email_edit");

        horizontalLayout_5->addWidget(email_edit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(6, 6, 6, 6);
        pw_label = new QLabel(layoutWidget);
        pw_label->setObjectName("pw_label");
        pw_label->setMinimumSize(QSize(75, 25));
        pw_label->setMaximumSize(QSize(75, 25));

        horizontalLayout_4->addWidget(pw_label);

        pw_edit = new QLineEdit(layoutWidget);
        pw_edit->setObjectName("pw_edit");

        horizontalLayout_4->addWidget(pw_edit);

        pw_visible = new ClickedLabel(layoutWidget);
        pw_visible->setObjectName("pw_visible");
        pw_visible->setMinimumSize(QSize(30, 20));
        pw_visible->setMaximumSize(QSize(30, 20));

        horizontalLayout_4->addWidget(pw_visible);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(6, 6, 6, 6);
        pwagain_label = new QLabel(layoutWidget);
        pwagain_label->setObjectName("pwagain_label");
        pwagain_label->setMinimumSize(QSize(75, 25));
        pwagain_label->setMaximumSize(QSize(75, 25));

        horizontalLayout_3->addWidget(pwagain_label);

        pwagain_edit = new QLineEdit(layoutWidget);
        pwagain_edit->setObjectName("pwagain_edit");
        pwagain_edit->setMinimumSize(QSize(0, 25));
        pwagain_edit->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(pwagain_edit);

        pwagain_visible = new ClickedLabel(layoutWidget);
        pwagain_visible->setObjectName("pwagain_visible");
        pwagain_visible->setMinimumSize(QSize(30, 20));
        pwagain_visible->setMaximumSize(QSize(30, 20));

        horizontalLayout_3->addWidget(pwagain_visible);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        verifycode_label = new QLabel(layoutWidget);
        verifycode_label->setObjectName("verifycode_label");
        verifycode_label->setMinimumSize(QSize(0, 30));
        verifycode_label->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(verifycode_label);

        verifycode_edit = new QLineEdit(layoutWidget);
        verifycode_edit->setObjectName("verifycode_edit");
        verifycode_edit->setMinimumSize(QSize(0, 30));
        verifycode_edit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(verifycode_edit);

        verifyButton = new QPushButton(layoutWidget);
        verifyButton->setObjectName("verifyButton");
        verifyButton->setMinimumSize(QSize(0, 30));
        verifyButton->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(verifyButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 60, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        confirm_button = new QPushButton(layoutWidget);
        confirm_button->setObjectName("confirm_button");
        confirm_button->setMinimumSize(QSize(0, 30));
        confirm_button->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(confirm_button);

        cancel_button = new QPushButton(layoutWidget);
        cancel_button->setObjectName("cancel_button");
        cancel_button->setMinimumSize(QSize(0, 30));
        cancel_button->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(cancel_button);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayoutWidget = new QWidget(page_2);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(19, 9, 341, 551));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(20, 20, 20, 20);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        return_label = new QLabel(verticalLayoutWidget);
        return_label->setObjectName("return_label");
        return_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(return_label);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(20, 20, 20, 20);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        return_login = new QPushButton(verticalLayoutWidget);
        return_login->setObjectName("return_login");
        return_login->setMinimumSize(QSize(100, 40));
        return_login->setMaximumSize(QSize(100, 40));

        horizontalLayout_7->addWidget(return_login);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_7);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(Register);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QDialog *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Dialog", nullptr));
        err_tip->setText(QCoreApplication::translate("Register", "error_tip", nullptr));
        user_label->setText(QCoreApplication::translate("Register", "username:", nullptr));
        email_label->setText(QCoreApplication::translate("Register", "email:", nullptr));
        pw_label->setText(QCoreApplication::translate("Register", "password:", nullptr));
        pw_visible->setText(QString());
        pwagain_label->setText(QCoreApplication::translate("Register", "again:", nullptr));
        pwagain_visible->setText(QString());
        verifycode_label->setText(QCoreApplication::translate("Register", "verify code:", nullptr));
        verifyButton->setText(QCoreApplication::translate("Register", "GET CODE", nullptr));
        confirm_button->setText(QCoreApplication::translate("Register", "CONFIRM", nullptr));
        cancel_button->setText(QCoreApplication::translate("Register", "CANCEL", nullptr));
        return_label->setText(QCoreApplication::translate("Register", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\2145\347\247\222\345\220\216\350\277\224\345\233\236\347\231\273\351\231\206\347\225\214\351\235\242\343\200\202", nullptr));
        return_login->setText(QCoreApplication::translate("Register", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
