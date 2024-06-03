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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui_psdClass
{
public:
    QWidget *centralWidget;
    QProgressBar *sigma1_progressbar;
    QProgressBar *sigma1_progressbar_2;
    QTableWidget *tableWidget;
    QPushButton *record_pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *gui_psdClass)
    {
        if (gui_psdClass->objectName().isEmpty())
            gui_psdClass->setObjectName("gui_psdClass");
        gui_psdClass->resize(1408, 835);
        centralWidget = new QWidget(gui_psdClass);
        centralWidget->setObjectName("centralWidget");
        sigma1_progressbar = new QProgressBar(centralWidget);
        sigma1_progressbar->setObjectName("sigma1_progressbar");
        sigma1_progressbar->setGeometry(QRect(10, 530, 501, 23));
        sigma1_progressbar->setValue(24);
        sigma1_progressbar_2 = new QProgressBar(centralWidget);
        sigma1_progressbar_2->setObjectName("sigma1_progressbar_2");
        sigma1_progressbar_2->setGeometry(QRect(520, 530, 501, 23));
        sigma1_progressbar_2->setValue(24);
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem8);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(1040, 30, 351, 121));
        record_pushButton = new QPushButton(centralWidget);
        record_pushButton->setObjectName("record_pushButton");
        record_pushButton->setGeometry(QRect(1120, 170, 201, 51));
        gui_psdClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(gui_psdClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1408, 21));
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
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("gui_psdClass", "PDS 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("gui_psdClass", "PSD 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("gui_psdClass", "Unit", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("gui_psdClass", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("gui_psdClass", "Y", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("gui_psdClass", "Sigma", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("gui_psdClass", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(1, 2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("gui_psdClass", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(2, 2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("gui_psdClass", "V", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        record_pushButton->setText(QCoreApplication::translate("gui_psdClass", "Record", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui_psdClass: public Ui_gui_psdClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_PSD_H
