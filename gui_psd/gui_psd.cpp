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
    //rt605 = HRSS();
    //rt605.connectHRSS(HRSS_IP);
    //std::thread open_rtss(&gui_psd::RunICRC_RTSS, this);
    //open_rtss.detach();

    QObject::connect(&timer_scope, &QTimer::timeout, this, &gui_psd::updatedataTable);
    QObject::connect(&timer_scope, &QTimer::timeout, this, &gui_psd::update_sigmaPlot);
    QObject::connect(&timer_scope, &QTimer::timeout, this, &gui_psd::update_scope);
    QObject::connect(&timer_scope, &QTimer::timeout, this, &gui_psd::update_sigmaProgressBar);

    QObject::connect(ui.record_pushButton, &QPushButton::clicked, this, &gui_psd::record_button_clicked);
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

            while (shm_ui->record_filename[0] == 0) {
                Sleep(10);
            }
            char buf[256] = { 0 };
            sprintf_s(buf, "PSD data logger on : % s", shm_ui->record_filename);
            ui.log_textBrowser->append(buf);
            ui.record_pushButton->setText("Recording");
            record_state = true;
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