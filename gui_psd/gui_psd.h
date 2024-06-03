#pragma once

//#include<Windows.h>
//#include<vector>
////#include<array>
//#include<string.h>

#include <QtWidgets/QMainWindow>
//#include<QtWidgets/QTableWidget>
//#include<QtWidgets/QTableWidgetItem>
#include "ui_gui_psd.h"

#define UNDER_WINDOWS
//#include <iostream>
//#include "../libs/shared.hpp"
//#include"hrss.h"

#include"qcustomplot.h"
//#include<qDebug>

//#include"Rtapi.h"




#define HRSS_IP "169.254.186.88"
class gui_psd : public QMainWindow
{
    Q_OBJECT

public:
    gui_psd(QWidget *parent = nullptr);
    ~gui_psd();

private:
    Ui::gui_psdClass ui;
};
