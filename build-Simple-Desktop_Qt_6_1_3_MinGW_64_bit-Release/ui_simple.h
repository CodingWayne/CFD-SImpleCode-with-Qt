/********************************************************************************
** Form generated from reading UI file 'simple.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLE_H
#define UI_SIMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_Simple
{
public:
    QLabel *label;
    QLineEdit *Lx;
    QLabel *label_2;
    QLineEdit *Ly;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLineEdit *my;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_19;
    QLineEdit *rho;
    QLineEdit *miu;
    QLabel *label_5;
    QLabel *label_20;
    QLineEdit *CFL;
    QLineEdit *mx;
    QLineEdit *u_right;
    QLineEdit *u_top;
    QLineEdit *u_left;
    QLineEdit *u_bottom;
    QLineEdit *v_right;
    QLineEdit *v_bottom;
    QLineEdit *v_left;
    QLineEdit *v_top;
    QLineEdit *save;
    QLabel *label_21;
    QLineEdit *U_relax;
    QLineEdit *P_relax;
    QPushButton *load;
    QTextEdit *text_show;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vLayout;
    QPushButton *pushButton_3;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *dLayout;
    QCustomPlot *customPlot;

    void setupUi(QWidget *Simple)
    {
        if (Simple->objectName().isEmpty())
            Simple->setObjectName(QString::fromUtf8("Simple"));
        Simple->resize(1289, 495);
        label = new QLabel(Simple);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 81, 21));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        Lx = new QLineEdit(Simple);
        Lx->setObjectName(QString::fromUtf8("Lx"));
        Lx->setGeometry(QRect(150, 30, 61, 21));
        Lx->setLayoutDirection(Qt::LeftToRight);
        Lx->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Simple);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 30, 81, 21));
        label_2->setFont(font);
        Ly = new QLineEdit(Simple);
        Ly->setObjectName(QString::fromUtf8("Ly"));
        Ly->setGeometry(QRect(350, 30, 61, 21));
        Ly->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Simple);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 50, 91, 21));
        label_3->setFont(font);
        label_4 = new QLabel(Simple);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(250, 50, 91, 21));
        label_4->setFont(font);
        lineEdit_3 = new QLineEdit(Simple);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(150, 50, 61, 21));
        my = new QLineEdit(Simple);
        my->setObjectName(QString::fromUtf8("my"));
        my->setGeometry(QRect(350, 50, 61, 21));
        my->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(Simple);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 90, 91, 21));
        label_6->setFont(font);
        label_7 = new QLabel(Simple);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 110, 91, 21));
        label_7->setFont(font);
        label_8 = new QLabel(Simple);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(250, 90, 91, 21));
        label_8->setFont(font);
        label_9 = new QLabel(Simple);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 150, 91, 21));
        label_9->setFont(font);
        label_10 = new QLabel(Simple);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(250, 150, 91, 21));
        label_10->setFont(font);
        label_11 = new QLabel(Simple);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 170, 91, 21));
        label_11->setFont(font);
        label_12 = new QLabel(Simple);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(250, 170, 91, 21));
        label_12->setFont(font);
        label_13 = new QLabel(Simple);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 190, 91, 21));
        label_13->setFont(font);
        label_14 = new QLabel(Simple);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(250, 190, 91, 21));
        label_14->setFont(font);
        label_15 = new QLabel(Simple);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 210, 91, 21));
        label_15->setFont(font);
        label_16 = new QLabel(Simple);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(250, 210, 91, 21));
        label_16->setFont(font);
        label_17 = new QLabel(Simple);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(20, 230, 91, 21));
        label_17->setFont(font);
        label_19 = new QLabel(Simple);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(250, 110, 91, 21));
        label_19->setFont(font);
        rho = new QLineEdit(Simple);
        rho->setObjectName(QString::fromUtf8("rho"));
        rho->setGeometry(QRect(150, 90, 61, 21));
        rho->setAlignment(Qt::AlignCenter);
        miu = new QLineEdit(Simple);
        miu->setObjectName(QString::fromUtf8("miu"));
        miu->setGeometry(QRect(150, 110, 61, 21));
        miu->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(Simple);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(22, 10, 391, 20));
        QFont font1;
        font1.setBold(true);
        label_5->setFont(font1);
        label_5->setCursor(QCursor(Qt::ArrowCursor));
        label_20 = new QLabel(Simple);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(20, 70, 391, 20));
        label_20->setFont(font1);
        CFL = new QLineEdit(Simple);
        CFL->setObjectName(QString::fromUtf8("CFL"));
        CFL->setGeometry(QRect(350, 90, 61, 21));
        CFL->setAlignment(Qt::AlignCenter);
        mx = new QLineEdit(Simple);
        mx->setObjectName(QString::fromUtf8("mx"));
        mx->setGeometry(QRect(150, 50, 61, 21));
        mx->setAlignment(Qt::AlignCenter);
        u_right = new QLineEdit(Simple);
        u_right->setObjectName(QString::fromUtf8("u_right"));
        u_right->setGeometry(QRect(150, 190, 61, 21));
        u_right->setAlignment(Qt::AlignCenter);
        u_top = new QLineEdit(Simple);
        u_top->setObjectName(QString::fromUtf8("u_top"));
        u_top->setGeometry(QRect(150, 150, 61, 21));
        u_top->setAlignment(Qt::AlignCenter);
        u_left = new QLineEdit(Simple);
        u_left->setObjectName(QString::fromUtf8("u_left"));
        u_left->setGeometry(QRect(150, 170, 61, 21));
        u_left->setAlignment(Qt::AlignCenter);
        u_bottom = new QLineEdit(Simple);
        u_bottom->setObjectName(QString::fromUtf8("u_bottom"));
        u_bottom->setGeometry(QRect(150, 210, 61, 21));
        u_bottom->setAlignment(Qt::AlignCenter);
        v_right = new QLineEdit(Simple);
        v_right->setObjectName(QString::fromUtf8("v_right"));
        v_right->setGeometry(QRect(350, 190, 61, 21));
        v_right->setAlignment(Qt::AlignCenter);
        v_bottom = new QLineEdit(Simple);
        v_bottom->setObjectName(QString::fromUtf8("v_bottom"));
        v_bottom->setGeometry(QRect(350, 210, 61, 21));
        v_bottom->setAlignment(Qt::AlignCenter);
        v_left = new QLineEdit(Simple);
        v_left->setObjectName(QString::fromUtf8("v_left"));
        v_left->setGeometry(QRect(350, 170, 61, 21));
        v_left->setAlignment(Qt::AlignCenter);
        v_top = new QLineEdit(Simple);
        v_top->setObjectName(QString::fromUtf8("v_top"));
        v_top->setGeometry(QRect(350, 150, 61, 21));
        v_top->setAlignment(Qt::AlignCenter);
        save = new QLineEdit(Simple);
        save->setObjectName(QString::fromUtf8("save"));
        save->setGeometry(QRect(350, 110, 61, 21));
        save->setAlignment(Qt::AlignCenter);
        label_21 = new QLabel(Simple);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(250, 230, 91, 21));
        label_21->setFont(font);
        U_relax = new QLineEdit(Simple);
        U_relax->setObjectName(QString::fromUtf8("U_relax"));
        U_relax->setGeometry(QRect(150, 230, 61, 21));
        U_relax->setAlignment(Qt::AlignCenter);
        P_relax = new QLineEdit(Simple);
        P_relax->setObjectName(QString::fromUtf8("P_relax"));
        P_relax->setGeometry(QRect(350, 230, 61, 21));
        P_relax->setAlignment(Qt::AlignCenter);
        load = new QPushButton(Simple);
        load->setObjectName(QString::fromUtf8("load"));
        load->setGeometry(QRect(20, 260, 75, 24));
        text_show = new QTextEdit(Simple);
        text_show->setObjectName(QString::fromUtf8("text_show"));
        text_show->setGeometry(QRect(20, 300, 391, 181));
        pushButton = new QPushButton(Simple);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(130, 260, 81, 24));
        pushButton_2 = new QPushButton(Simple);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 260, 75, 24));
        verticalLayoutWidget = new QWidget(Simple);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(420, 250, 421, 241));
        vLayout = new QVBoxLayout(verticalLayoutWidget);
        vLayout->setObjectName(QString::fromUtf8("vLayout"));
        vLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(Simple);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(340, 260, 71, 24));
        verticalLayoutWidget_2 = new QWidget(Simple);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(850, 250, 431, 241));
        dLayout = new QVBoxLayout(verticalLayoutWidget_2);
        dLayout->setObjectName(QString::fromUtf8("dLayout"));
        dLayout->setContentsMargins(0, 0, 0, 0);
        customPlot = new QCustomPlot(Simple);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(420, 20, 861, 221));

        retranslateUi(Simple);

        QMetaObject::connectSlotsByName(Simple);
    } // setupUi

    void retranslateUi(QWidget *Simple)
    {
        Simple->setWindowTitle(QCoreApplication::translate("Simple", "Simple", nullptr));
        label->setText(QCoreApplication::translate("Simple", "Length(X):", nullptr));
        Lx->setText(QCoreApplication::translate("Simple", "0.1", nullptr));
        label_2->setText(QCoreApplication::translate("Simple", "Length(Y):", nullptr));
        Ly->setText(QCoreApplication::translate("Simple", "0.01", nullptr));
        label_3->setText(QCoreApplication::translate("Simple", "Mes_num(X):", nullptr));
        label_4->setText(QCoreApplication::translate("Simple", "Mes_num(Y):", nullptr));
        my->setText(QCoreApplication::translate("Simple", "30", nullptr));
        label_6->setText(QCoreApplication::translate("Simple", "Density  :", nullptr));
        label_7->setText(QCoreApplication::translate("Simple", "Viscosity:", nullptr));
        label_8->setText(QCoreApplication::translate("Simple", "CFL:", nullptr));
        label_9->setText(QCoreApplication::translate("Simple", "Top_U:", nullptr));
        label_10->setText(QCoreApplication::translate("Simple", "Top_V:", nullptr));
        label_11->setText(QCoreApplication::translate("Simple", "Left_U:", nullptr));
        label_12->setText(QCoreApplication::translate("Simple", "Left_V:", nullptr));
        label_13->setText(QCoreApplication::translate("Simple", "Right_U:", nullptr));
        label_14->setText(QCoreApplication::translate("Simple", "Right_V:", nullptr));
        label_15->setText(QCoreApplication::translate("Simple", "Bottom_U:", nullptr));
        label_16->setText(QCoreApplication::translate("Simple", "Bottom_V:", nullptr));
        label_17->setText(QCoreApplication::translate("Simple", "U_Relaxation:", nullptr));
        label_19->setText(QCoreApplication::translate("Simple", "Save mode", nullptr));
        rho->setText(QCoreApplication::translate("Simple", "1.205", nullptr));
        miu->setText(QCoreApplication::translate("Simple", "0.0000182", nullptr));
        label_5->setText(QCoreApplication::translate("Simple", "---------------------------------- Mesh------------------------------------------", nullptr));
        label_20->setText(QCoreApplication::translate("Simple", "-----------------------------------Pysics------------------------------------------", nullptr));
        CFL->setText(QCoreApplication::translate("Simple", "1", nullptr));
        mx->setText(QCoreApplication::translate("Simple", "30", nullptr));
        u_right->setText(QCoreApplication::translate("Simple", "0", nullptr));
        u_top->setText(QCoreApplication::translate("Simple", "0", nullptr));
        u_left->setText(QCoreApplication::translate("Simple", "0.01", nullptr));
        u_bottom->setText(QCoreApplication::translate("Simple", "0", nullptr));
        v_right->setText(QCoreApplication::translate("Simple", "0", nullptr));
        v_bottom->setText(QCoreApplication::translate("Simple", "0", nullptr));
        v_left->setText(QCoreApplication::translate("Simple", "0", nullptr));
        v_top->setText(QCoreApplication::translate("Simple", "0", nullptr));
        save->setText(QCoreApplication::translate("Simple", "0", nullptr));
        label_21->setText(QCoreApplication::translate("Simple", "P_Relaxation:", nullptr));
        U_relax->setText(QCoreApplication::translate("Simple", "0.7", nullptr));
        P_relax->setText(QCoreApplication::translate("Simple", "0.01", nullptr));
        load->setText(QCoreApplication::translate("Simple", "Load", nullptr));
        pushButton->setText(QCoreApplication::translate("Simple", "Pause / Run", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Simple", "Output", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Simple", "Reset plot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simple: public Ui_Simple {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLE_H
