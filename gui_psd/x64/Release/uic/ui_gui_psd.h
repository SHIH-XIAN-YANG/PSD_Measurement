/********************************************************************************
** Form generated from reading UI file 'gui_psd.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_PSD_H
#define UI_GUI_PSD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_gui_psdClass
{
public:
    QWidget *centralWidget;
    QCustomPlot *xy_plot_1;
    QCustomPlot *xy_plot_2;
    QCustomPlot *sigma1_plot;
    QCustomPlot *sigma2_plot;
    QPushButton *record_pushButton;
    QProgressBar *sigma1_progressBar;
    QProgressBar *sigma2_progressBar;
    QTableWidget *data_table;
    QTextBrowser *log_textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *gui_psdClass)
    {
        if (gui_psdClass->objectName().isEmpty())
            gui_psdClass->setObjectName("gui_psdClass");
        gui_psdClass->resize(1416, 866);
        centralWidget = new QWidget(gui_psdClass);
        centralWidget->setObjectName("centralWidget");
        xy_plot_1 = new QCustomPlot(centralWidget);
        xy_plot_1->setObjectName("xy_plot_1");
        xy_plot_1->setGeometry(QRect(10, 10, 500, 500));
        xy_plot_2 = new QCustomPlot(centralWidget);
        xy_plot_2->setObjectName("xy_plot_2");
        xy_plot_2->setGeometry(QRect(530, 10, 500, 500));
        sigma1_plot = new QCustomPlot(centralWidget);
        sigma1_plot->setObjectName("sigma1_plot");
        sigma1_plot->setGeometry(QRect(10, 549, 500, 231));
        sigma2_plot = new QCustomPlot(centralWidget);
        sigma2_plot->setObjectName("sigma2_plot");
        sigma2_plot->setGeometry(QRect(530, 550, 500, 231));
        record_pushButton = new QPushButton(centralWidget);
        record_pushButton->setObjectName("record_pushButton");
        record_pushButton->setGeometry(QRect(1140, 190, 171, 71));
        sigma1_progressBar = new QProgressBar(centralWidget);
        sigma1_progressBar->setObjectName("sigma1_progressBar");
        sigma1_progressBar->setGeometry(QRect(10, 520, 501, 23));
        sigma1_progressBar->setValue(0);
        sigma1_progressBar->setTextVisible(false);
        sigma2_progressBar = new QProgressBar(centralWidget);
        sigma2_progressBar->setObjectName("sigma2_progressBar");
        sigma2_progressBar->setGeometry(QRect(530, 520, 501, 23));
        sigma2_progressBar->setValue(0);
        sigma2_progressBar->setTextVisible(false);
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
        data_table->setGeometry(QRect(1060, 20, 351, 131));
        log_textBrowser = new QTextBrowser(centralWidget);
        log_textBrowser->setObjectName("log_textBrowser");
        log_textBrowser->setGeometry(QRect(1060, 280, 351, 531));
        gui_psdClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(gui_psdClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1416, 21));
        gui_psdClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(gui_psdClass);
        mainToolBar->setObjectName("mainToolBar");
        gui_psdClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(gui_psdClass);
        statusBar->setObjectName("statusBar");
        gui_psdClass->setStatusBar(statusBar);

        retranslateUi(gui_psdClass);

        QMetaObject::connectSlotsByName(gui_psdClass);
    } // setupUi

    void retranslateUi(QMainWindow *gui_psdClass)
    {
        gui_psdClass->setWindowTitle(QCoreApplication::translate("gui_psdClass", "gui_psd", nullptr));
        record_pushButton->setText(QCoreApplication::translate("gui_psdClass", "Record", nullptr));
        QTableWidgetItem *___qtablewidgetitem = data_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("gui_psdClass", "PSD 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = data_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("gui_psdClass", "PSD 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = data_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("gui_psdClass", "Unit", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = data_table->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("gui_psdClass", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = data_table->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("gui_psdClass", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = data_table->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("gui_psdClass", "Sigma", nullptr));

        const bool __sortingEnabled = data_table->isSortingEnabled();
        data_table->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = data_table->item(0, 2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("gui_psdClass", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = data_table->item(1, 2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("gui_psdClass", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = data_table->item(2, 2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("gui_psdClass", "V", nullptr));
        data_table->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class gui_psdClass: public Ui_gui_psdClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_PSD_H
