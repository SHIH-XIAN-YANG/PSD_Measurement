#pragma once



#include<Windows.h>
#include<vector>
#include<array>
#include<string.h>

#include <QtWidgets/QMainWindow>
#include<QtWidgets/QTableWidget>
#include<QtWidgets/QTableWidgetItem>
#include "ui_gui_psd.h"
#define UNDER_WINDOWS
#include <iostream>
#include "../libs/shared.hpp"
#include"hrss.h"
#include "qcustomplot.h"
#include<qDebug>
#include<thread>

#include"Rtapi.h"


#define HRSS_IP "169.254.186.88"

class gui_psd : public QMainWindow
{
    Q_OBJECT

public:
    gui_psd(QWidget *parent = nullptr);
    ~gui_psd();
    void setupDataTable(void);
    void setupScopes(void);
    void setupSigmaProgressBar(void);
    void RunICRC_RTSS(void);

public slots:
    void updatedataTable(void);
    void update_scope(void);
    void update_sigmaPlot(void);
    void update_sigmaProgressBar(void);
    void record_button_clicked(void);
    void runHRSS_button_clicked(void);

private:
    Ui::gui_psdClass ui;
    QTimer timer_scope;
    double current_time;

    struct Shm_UI* shm_ui;
    HANDLE ui_handler;
    HRSS rt605;
    QVector<double> x1, y1, x2, y2;
    double sigma1, sigma2;
    bool record_state;
    char filename[256];
};
