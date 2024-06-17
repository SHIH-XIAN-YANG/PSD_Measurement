#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test.h"
#include "qcustomplot.h"
#include<Windows.h>
#include<vector>
#include<array>
#include<string.h>

#include <QtWidgets/QMainWindow>
#include<QtWidgets/QTableWidget>
#include<QtWidgets/QTableWidgetItem>

#define UNDER_WINDOWS
#include <iostream>
#include "../libs/shared.hpp"
#include"hrss.h"

#include<qDebug>

#include"Rtapi.h"


#define HRSS_IP "169.254.186.88"

class test : public QMainWindow
{
    Q_OBJECT

public:
    test(QWidget *parent = nullptr);
    ~test();

public slots:
    void updatedataTable(void);

private:
    Ui::testClass ui;
};
