#include "gui_psd.h"

gui_psd::gui_psd(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //setupDataTable();
    setupScopes();
    setupSigmaProgressBar();
    record_state = false;


    ui_handler = RtCreateSharedMemory(0, 0, sizeof(Shm_UI), L"SHM_UI", (void**)&shm_ui);
    if (ui_handler == NULL || shm_ui == nullptr) {
        ui.log_textBrowser->append("Failed to create or access shared memory");
    }
    rt605 = HRSS();
    rt605.connectHRSS(HRSS_IP);
    std::thread open_rtss(&gui_psd::RunICRC_RTSS, this);
    open_rtss.detach();

    QObject::connect(&timer_scope, &QTimer::timeout, this, &gui_psd::updatedataTable);
    QObject::connect(&timer_scope, &QTimer::timeout, this, &gui_psd::update_sigmaPlot);
    QObject::connect(&timer_scope, &QTimer::timeout, this, &gui_psd::update_scope);
    QObject::connect(&timer_scope, &QTimer::timeout, this, &gui_psd::update_sigmaProgressBar);
    

    QObject::connect(ui.record_pushButton, &QPushButton::clicked, this, &gui_psd::record_button_clicked);
    QObject::connect(ui.runHRSS_pushButton, &QPushButton::clicked, this, &gui_psd::runHRSS_button_clicked);
    current_time = 0.0;
    timer_scope.start(1);
    ui.log_textBrowser->append("RTX STARTING");
}



gui_psd::~gui_psd() {
    timer_scope.stop();
    shm_ui->run = false;
}


void gui_psd::setupDataTable(void) {
    int row = ui.data_table->rowCount();
    int col = ui.data_table->columnCount();
    // read only:
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            ui.data_table->item(r, c)->setFlags(ui.data_table->item(r, c)->flags() & ~Qt::ItemIsEditable);
        }
    }
}

void gui_psd::setupScopes(void) {
    ui.xy_plot_1->addGraph();
    ui.xy_plot_1->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui.xy_plot_1->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui.xy_plot_1->xAxis->setLabel("x (mm)");
    ui.xy_plot_1->yAxis->setLabel("y (mm)");
    ui.xy_plot_1->xAxis->setRange(-2.25, 2.25);
    ui.xy_plot_1->yAxis->setRange(-2.25, 2.25);
    ui.xy_plot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);

    ui.xy_plot_2->addGraph();
    ui.xy_plot_2->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui.xy_plot_2->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui.xy_plot_2->xAxis->setLabel("x (mm)");
    ui.xy_plot_2->yAxis->setLabel("y (mm)");
    ui.xy_plot_2->xAxis->setRange(-2.25, 2.25);
    ui.xy_plot_2->yAxis->setRange(-2.25, 2.25);
    ui.xy_plot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);

    ui.sigma1_plot->addGraph();
    ui.sigma1_plot->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui.sigma1_plot->xAxis->setRange(0, 6);
    ui.sigma1_plot->xAxis->setLabel("time(s)");
    ui.sigma1_plot->yAxis->setRange(-10, 0);
    ui.sigma1_plot->yAxis->setLabel("Sigma(V)");
    ui.sigma2_plot->xAxis->setRange(0, 6);
    ui.sigma2_plot->xAxis->setLabel("time(s)");
    ui.sigma2_plot->yAxis->setRange(-10, 0);
    ui.sigma2_plot->yAxis->setLabel("Sigma(V)");

    x1.reserve(250);
    y1.reserve(250);
    x2.reserve(250);
    y2.reserve(250);
    x1.resize(250);
    y1.resize(250);
    x2.resize(250);
    y2.resize(250);
}

void gui_psd::setupSigmaProgressBar(void) {
    ui.sigma1_progressBar->setValue(0);
    ui.sigma2_progressBar->setValue(0);
}

void gui_psd::updatedataTable(void) {
    if (shm_ui) {
        ui.data_table->item(0, 0)->setText(QString::number(shm_ui->x1));
        ui.data_table->item(1, 0)->setText(QString::number(shm_ui->y1));
        ui.data_table->item(2, 0)->setText(QString::number(shm_ui->sigma1));
        ui.data_table->item(0, 1)->setText(QString::number(shm_ui->x2));
        ui.data_table->item(1, 1)->setText(QString::number(shm_ui->y2));
        ui.data_table->item(2, 1)->setText(QString::number(shm_ui->sigma2)); 

    }
}

void gui_psd::update_scope(void) {
    if (shm_ui) {
        static unsigned int index = 0;
        x1[index] = shm_ui->x1;
        x2[index] = shm_ui->x2;
        y1[index] = shm_ui->y1;
        y2[index] = shm_ui->y2;

        ui.xy_plot_1->graph(0)->setData(x1, y1);
        ui.xy_plot_2->graph(0)->setData(x2, y2);
        ui.xy_plot_1->replot();
        ui.xy_plot_2->replot();
        if (++index == 250) {
            index = 0;
        }
    }
    
}

void gui_psd::record_button_clicked(void) {
    if (shm_ui) {
        if (!record_state) {
            shm_ui->file_create = true;
            ui.record_pushButton->setEnabled(false);
            while (shm_ui->record_filename[0] == 0) {
                Sleep(10);
            }
            char buf[256] = { 0 };
            sprintf_s(buf, "PSD data logger on : % s", shm_ui->record_filename);
            ui.log_textBrowser->append(buf);
            ui.record_pushButton->setText("Recording");
            record_state = true;
            ui.record_pushButton->setEnabled(true);
        }
        else {
            shm_ui->file_close = true;
            ui.log_textBrowser->append("log off");
            ui.record_pushButton->setText("Record");
            record_state = false;
            memset(shm_ui->record_filename, 0, sizeof(shm_ui->record_filename));
        }
    }
    
}

void gui_psd::runHRSS_button_clicked(void) {
    ui.runHRSS_pushButton->setEnabled(false);
    switch (ui.HRSS_task_comboBox.currentIndex())
    {
    case 0:
        // Calibration - Black PSD
        double current_pos[6] = { 0 };
        
        rt605.return_home();
        rt605.set_base(10);
        rt605.set_tool(2);
        rt605.print_current_pos();
        rt605.set_speed(500); // 500mm/s

        // start points trajectory
        double x_inc[6] = { 10,0,0,0,0,0 };
        double x_dec[6] = { -10,0,0,0,0,0 };
        double z_dec[6] = { 0,0,-10,0,0,0 };
        ui.log_textBrowser.append("Calibration - Black PSD - Trajectory using HRSDK RUNNING");
        // std::cout << "Points Trajectory using HRSDK RUNNING" << std::endl;
        rt605.GetRobotPosition(ui->robot_pos);
        ui->log = true;
        Sleep(100);
        ui->log = false;
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                if (i % 2 == 0) {
                    rt605.lin_rel(x_inc);
                }
                else {
                    rt605.lin_rel(x_dec);
                }
                while (rt605.get_robot_state() != 1) {
                    Sleep(10);
                }

                rt605.GetRobotPosition(ui->robot_pos);
                rt605.print_current_pos();
                ui->log = true;
                Sleep(100);
                ui->log = false;

            }
            rt605.lin_rel(z_dec);
            while (rt605.get_robot_state() != 1) {
                Sleep(10);
            }

            rt605.GetRobotPosition(ui->robot_pos);
            rt605.print_current_pos();
            ui->log = true;
            Sleep(100);
            ui->log = false;
        }

        rt605.return_home();
        ui.log_textBrowser.append("HRSS Task Finished");
        break;
    case 1:
        // Calibration - White PSD
        rt605.return_home();
        rt605.set_base(10);
        rt605.set_tool(2);
        rt605.print_current_pos();
        rt605.set_speed(500); // 500mm/s

        // PSD 1 moving range from p1 to p2
        double p1[6] = { 84.169, 316.065, 273.597, 0, 0, 0 };
        double p2[6] = { 304.169, 316.065, 93.597, 0, 0, 0 };

        double p3[6] = { 144.118, 316.065, 275.939, 0, 0, 0 };
        double p4[6] = { 324.118, 316.065, 55.939, 0, 0, 0 };

        // start points trajectory
        double x_inc[6] = { 10,0,0,0,0,0 };
        double x_dec[6] = { -10,0,0,0,0,0 };
        double z_dec[6] = { 0,0,-10,0,0,0 };

        rt605.p2p(p1);
        ui.log_textBrowser.append("Points Trajectory using HRSDK RUNNING");
        //std::cout << "Points Trajectory using HRSDK RUNNING" << std::endl;
        rt605.GetRobotPosition(ui->robot_pos);
        ui->log = true;
        Sleep(100);
        ui->log = false;
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 22; j++) {
                if (i % 2 == 0) {
                    rt605.lin_rel(x_inc);
                }
                else {
                    rt605.lin_rel(x_dec);
                }
                while (rt605.get_robot_state() != 1) {
                    Sleep(10);
                }

                rt605.GetRobotPosition(ui->robot_pos);
                rt605.print_current_pos();
                ui->log = true;
                Sleep(100);
                ui->log = false;

            }
            rt605.lin_rel(z_dec);
            while (rt605.get_robot_state() != 1) {
                Sleep(10);
            }

            rt605.GetRobotPosition(ui->robot_pos);
            rt605.print_current_pos();
            ui->log = true;
            Sleep(100);
            ui->log = false;
        }

        rt605.return_home();
        ui.log_textBrowser.append("HRSS Task Finished");
        //std::cout << "Finished" << std::endl;
        break;
    case 2:
        // Distortion calibration - Black PSD
        rt605.return_home();
        rt605.set_base(10);
        rt605.set_tool(2);
        rt605.print_current_pos();
        rt605.set_speed(500); // 500mm/s

        double p1[6] = { 144.118, 316.065, 275.939, 0, 0, 0 };
        double p2[6] = { 324.118, 316.065, 55.939, 0, 0, 0 };

        // start points trajectory
        double x_inc[6] = { 10,0,0,0,0,0 };
        double x_dec[6] = { -10,0,0,0,0,0 };
        double z_dec[6] = { 0,0,-10,0,0,0 };

        rt605.p2p(p1);
        ui.log_textBrowser.append("Distortion calibration - Black PSD HRSS Task Start");
        //std::cout << "Points Trajectory using HRSDK RUNNING" << std::endl;
        rt605.GetRobotPosition(ui->robot_pos);
        ui->log = true;
        Sleep(100);
        ui->log = false;
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 18; j++) {
                if (i % 2 == 0) {
                    rt605.lin_rel(x_inc);
                }
                else {
                    rt605.lin_rel(x_dec);
                }
                while (rt605.get_robot_state() != 1) {
                    Sleep(10);
                }

                rt605.GetRobotPosition(ui->robot_pos);
                rt605.print_current_pos();
                ui->log = true;
                Sleep(100);
                ui->log = false;

            }
            rt605.lin_rel(z_dec);
            while (rt605.get_robot_state() != 1) {
                Sleep(10);
            }

            rt605.GetRobotPosition(ui->robot_pos);
            rt605.print_current_pos();
            ui->log = true;
            Sleep(100);
            ui->log = false;
        }

        rt605.return_home();
        ui.log_textBrowser.append("HRSS Task Finished");
        break;
    case 3:
        // Distortion calibration - Black PSD
        ui.log_textBrowser.append("Not Yet Implemented");
        break;
    case 4:
        // TEST2006.hrb
        rt605.StartProgram("TEST1006.hrb");
        while (rt605.get_robot_state() != 1) {
            Sleep(10);
        }
        
        break;
    default:
        break;
    }
    ui.runHRSS_pushButton->setEnabled(true);
}

void gui_psd::update_sigmaPlot(void){
    if (shm_ui) {
        current_time += 0.001;
        ui.sigma1_plot->graph(0)->addData(current_time, shm_ui->sigma1);
        ui.sigma2_plot->graph(0)->addData(current_time, shm_ui->sigma2);

        if (current_time > 5) {
            ui.sigma1_plot->xAxis->setRange(current_time - 5, current_time + 1);
            ui.sigma2_plot->xAxis->setRange(current_time - 5, current_time + 1);
        }
        ui.sigma1_plot->replot();
        ui.sigma2_plot->replot();
    }
    
}
void gui_psd::update_sigmaProgressBar(void) {
    if (shm_ui) {
        int sigma1 = static_cast<int>(abs(shm_ui->sigma1) * 10);
        int sigma2 = static_cast<int>(abs(shm_ui->sigma2) * 10);
        if (sigma1 < 10 || sigma1>90) {
            ui.sigma1_progressBar->setStyleSheet(
                "QProgressBar::chunk {"
                "background-color: red;"
                "}"
            );
        }
        else {
            ui.sigma1_progressBar->setStyleSheet(
                "QProgressBar::chunk {"
                "background-color: green;"
                "}"
            );
        }

        if (sigma2 < 10 || sigma2>90) {
            ui.sigma2_progressBar->setStyleSheet(
                "QProgressBar::chunk {"
                "background-color: red;"
                "}"
            );
        }
        else {
            ui.sigma2_progressBar->setStyleSheet(
                "QProgressBar::chunk {"
                "background-color: green;"
                "}"
            );
        }

        ui.sigma1_progressBar->setValue(sigma1);
        ui.sigma2_progressBar->setValue(sigma2);
    }
    
}

void gui_psd::RunICRC_RTSS(void) {
    wchar_t app_directory[128];
    DWORD len = GetCurrentDirectory(128, app_directory);
    wchar_t PathStr[128] = L"\"";
    lstrcat(PathStr, app_directory);

    HINSTANCE nRet = ShellExecute(NULL, NULL, L"C:\\Program Files\\IntervalZero\\RTX64\\bin\\RTSSRUN", \
        L"E:\\samuel\\PSD_Measurement\\x64\\RtssDebug\\rt_psd.rtss", NULL, SW_HIDE);
}