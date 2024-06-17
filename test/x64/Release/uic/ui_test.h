/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_testClass
{
public:
    QWidget *centralWidget;
    QCustomPlot *xy_plot_1;
    QCustomPlot *xy_plot_2;
    QCustomPlot *sigma1_plot;
    QCustomPlot *sigma2_plot;
    QProgressBar *progressBar_1;
    QProgressBar *progressBar_2;
    QTableWidget *data_table;
    QPushButton *record_pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *testClass)
    {
        if (testClass->objectName().isEmpty())
            testClass->setObjectName("testClass");
        testClass->resize(1513, 878);
        centralWidget = new QWidget(testClass);
        centralWidget->setObjectName("centralWidget");
        xy_plot_1 = new QCustomPlot(centralWidget);
        xy_plot_1->setObjectName("xy_plot_1");
        xy_plot_1->setGeometry(QRect(20, 20, 500, 500));
        xy_plot_2 = new QCustomPlot(centralWidget);
        xy_plot_2->setObjectName("xy_plot_2");
        xy_plot_2->setGeometry(QRect(540, 20, 500, 500));
        sigma1_plot = new QCustomPlot(centralWidget);
        sigma1_plot->setObjectName("sigma1_plot");
        sigma1_plot->setGeometry(QRect(20, 560, 500, 211));
        sigma2_plot = new QCustomPlot(centralWidget);
        sigma2_plot->setObjectName("sigma2_plot");
        sigma2_plot->setGeometry(QRect(540, 560, 500, 211));
        progressBar_1 = new QProgressBar(centralWidget);
        progressBar_1->setObjectName("progressBar_1");
        progressBar_1->setGeometry(QRect(20, 530, 501, 23));
        progressBar_1->setValue(24);
        progressBar_2 = new QProgressBar(centralWidget);
        progressBar_2->setObjectName("progressBar_2");
        progressBar_2->setGeometry(QRect(540, 530, 501, 23));
        progressBar_2->setValue(24);
        data_table = new QTableWidget(centralWidget);
        if (data_table->columnCount() < 3)
            data_table->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        data_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        data_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        data_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (data_table->rowCount() < 3)
            data_table->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        data_table->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        data_table->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        data_table->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        data_table->setItem(0, 2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        data_table->setItem(1, 2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        data_table->setItem(2, 2, __qtablewidgetitem8);
        data_table->setObjectName("data_table");
        data_table->setGeometry(QRect(1060, 30, 381, 192));
        record_pushButton = new QPushButton(centralWidget);
        record_pushButton->setObjectName("record_pushButton");
        record_pushButton->setGeometry(QRect(1170, 250, 181, 61));
        testClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(testClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1513, 21));
        testClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(testClass);
        mainToolBar->setObjectName("mainToolBar");
        testClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(testClass);
        statusBar->setObjectName("statusBar");
        testClass->setStatusBar(statusBar);

        retranslateUi(testClass);

        QMetaObject::connectSlotsByName(testClass);
    } // setupUi

    void retranslateUi(QMainWindow *testClass)
    {
        testClass->setWindowTitle(QCoreApplication::translate("testClass", "test", nullptr));
        QTableWidgetItem *___qtablewidgetitem = data_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("testClass", "PSD 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = data_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("testClass", "PSD 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = data_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("testClass", "Unit", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = data_table->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("testClass", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = data_table->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("testClass", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = data_table->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("testClass", "Sigma", nullptr));

        const bool __sortingEnabled = data_table->isSortingEnabled();
        data_table->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = data_table->item(0, 2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("testClass", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = data_table->item(1, 2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("testClass", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = data_table->item(2, 2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("testClass", "V", nullptr));
        data_table->setSortingEnabled(__sortingEnabled);

        record_pushButton->setText(QCoreApplication::translate("testClass", "Record", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testClass: public Ui_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
