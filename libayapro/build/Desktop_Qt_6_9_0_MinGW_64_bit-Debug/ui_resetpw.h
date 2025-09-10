/********************************************************************************
** Form generated from reading UI file 'resetpw.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETPW_H
#define UI_RESETPW_H

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

QT_BEGIN_NAMESPACE

class Ui_resetpw
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page_1;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout;
    QLabel *user_label;
    QLineEdit *user_edit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *email_label;
    QLineEdit *email_edit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *verifycode_label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *verifycode_edit;
    QPushButton *verifycode_button;
    QHBoxLayout *horizontalLayout_5;
    QLabel *pw_label;
    QLineEdit *pw_edit;
    QHBoxLayout *horizontalLayout_11;
    QLabel *pwagain_label;
    QLineEdit *pwagain_edit;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *confirm_button;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *cancel_button;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QWidget *page_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *tip_label;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *return_button;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QDialog *resetpw)
    {
        if (resetpw->objectName().isEmpty())
            resetpw->setObjectName("resetpw");
        resetpw->resize(400, 600);
        resetpw->setMinimumSize(QSize(400, 600));
        resetpw->setMaximumSize(QSize(400, 600));
        stackedWidget = new QStackedWidget(resetpw);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 381, 531));
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        verticalLayoutWidget = new QWidget(page_1);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 378, 531));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        verticalSpacer_2 = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);

        err_tip = new QLabel(verticalLayoutWidget);
        err_tip->setObjectName("err_tip");
        err_tip->setMinimumSize(QSize(0, 40));
        err_tip->setMaximumSize(QSize(16777215, 40));
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(err_tip);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        user_label = new QLabel(verticalLayoutWidget);
        user_label->setObjectName("user_label");
        user_label->setMinimumSize(QSize(45, 25));
        user_label->setMaximumSize(QSize(45, 25));

        horizontalLayout->addWidget(user_label);

        user_edit = new QLineEdit(verticalLayoutWidget);
        user_edit->setObjectName("user_edit");

        horizontalLayout->addWidget(user_edit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(6, 6, 6, 6);
        email_label = new QLabel(verticalLayoutWidget);
        email_label->setObjectName("email_label");
        email_label->setMinimumSize(QSize(45, 25));
        email_label->setMaximumSize(QSize(45, 25));

        horizontalLayout_4->addWidget(email_label);

        email_edit = new QLineEdit(verticalLayoutWidget);
        email_edit->setObjectName("email_edit");

        horizontalLayout_4->addWidget(email_edit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(6, 6, 6, 6);
        verifycode_label = new QLabel(verticalLayoutWidget);
        verifycode_label->setObjectName("verifycode_label");
        verifycode_label->setMinimumSize(QSize(45, 25));

        horizontalLayout_10->addWidget(verifycode_label);

        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer);

        verifycode_edit = new QLineEdit(verticalLayoutWidget);
        verifycode_edit->setObjectName("verifycode_edit");

        horizontalLayout_10->addWidget(verifycode_edit);

        verifycode_button = new QPushButton(verticalLayoutWidget);
        verifycode_button->setObjectName("verifycode_button");

        horizontalLayout_10->addWidget(verifycode_button);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(6, 6, 6, 6);
        pw_label = new QLabel(verticalLayoutWidget);
        pw_label->setObjectName("pw_label");
        pw_label->setMinimumSize(QSize(45, 25));

        horizontalLayout_5->addWidget(pw_label);

        pw_edit = new QLineEdit(verticalLayoutWidget);
        pw_edit->setObjectName("pw_edit");

        horizontalLayout_5->addWidget(pw_edit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setContentsMargins(6, 6, 6, 6);
        pwagain_label = new QLabel(verticalLayoutWidget);
        pwagain_label->setObjectName("pwagain_label");
        pwagain_label->setMinimumSize(QSize(45, 25));

        horizontalLayout_11->addWidget(pwagain_label);

        pwagain_edit = new QLineEdit(verticalLayoutWidget);
        pwagain_edit->setObjectName("pwagain_edit");

        horizontalLayout_11->addWidget(pwagain_edit);


        verticalLayout->addLayout(horizontalLayout_11);

        verticalSpacer_3 = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        confirm_button = new QPushButton(verticalLayoutWidget);
        confirm_button->setObjectName("confirm_button");

        horizontalLayout_6->addWidget(confirm_button);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        cancel_button = new QPushButton(verticalLayoutWidget);
        cancel_button->setObjectName("cancel_button");

        horizontalLayout_6->addWidget(cancel_button);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayoutWidget_2 = new QWidget(page_2);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(9, 9, 371, 521));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        tip_label = new QLabel(verticalLayoutWidget_2);
        tip_label->setObjectName("tip_label");
        tip_label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(tip_label);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_2);

        return_button = new QPushButton(verticalLayoutWidget_2);
        return_button->setObjectName("return_button");

        horizontalLayout_12->addWidget(return_button);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_12);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_5);

        stackedWidget->addWidget(page_2);

        retranslateUi(resetpw);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(resetpw);
    } // setupUi

    void retranslateUi(QDialog *resetpw)
    {
        resetpw->setWindowTitle(QCoreApplication::translate("resetpw", "Dialog", nullptr));
        err_tip->setText(QCoreApplication::translate("resetpw", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        user_label->setText(QCoreApplication::translate("resetpw", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        email_label->setText(QCoreApplication::translate("resetpw", "\351\202\256\347\256\261\357\274\232", nullptr));
        verifycode_label->setText(QCoreApplication::translate("resetpw", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        verifycode_button->setText(QCoreApplication::translate("resetpw", "\350\216\267\345\217\226", nullptr));
        pw_label->setText(QCoreApplication::translate("resetpw", "\346\226\260\345\257\206\347\240\201\357\274\232", nullptr));
        pwagain_label->setText(QCoreApplication::translate("resetpw", "\347\241\256\350\256\244\357\274\232", nullptr));
        confirm_button->setText(QCoreApplication::translate("resetpw", "\347\241\256\350\256\244", nullptr));
        cancel_button->setText(QCoreApplication::translate("resetpw", "\350\277\224\345\233\236", nullptr));
        tip_label->setText(QCoreApplication::translate("resetpw", "\345\257\206\347\240\201\351\207\215\347\275\256\346\210\220\345\212\237\357\274\2015\347\247\222\345\220\216\350\277\224\345\233\236\347\231\273\351\231\206\347\225\214\351\235\242", nullptr));
        return_button->setText(QCoreApplication::translate("resetpw", "\350\277\224\345\233\236\347\231\273\351\231\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class resetpw: public Ui_resetpw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETPW_H
