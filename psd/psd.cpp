// psd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#ifdef x64
//#pragma comment(lib, "../libs/HRSDK_3.0.9/HRSDK_3.0.9/lib/x64/HRSDK.lib")
//#else
//#pragma comment(lib, "../libs/HRSDK_3.0.9/HRSDK_3.0.9/lib/x86/HRSDK.lib")
//#endif
#pragma once
#include <iostream>
#include "../libs/shared.hpp"
#include "hrss.h"
#include <cstdlib>
#include<thread>

extern FILE* sys_log_fs;


void show_ui_menu(void);
void RunICRC_RTSS(void);

int main()
{
    
    struct Shm_UI* ui;
    HANDLE ui_handler = RtCreateSharedMemory(0, 0, sizeof(Shm_UI), L"SHM_UI", (void**)&ui);
    std::cout << "start" << std::endl;
    ui->run = true;

    //  connect to rt605
	HRSS rt605 = HRSS();
	rt605.connectHRSS("169.254.186.88");
    
    // open rtss:
    std::thread open_rtss(RunICRC_RTSS);
    open_rtss.detach();

    while (ui->run) {
        show_ui_menu();
        std::cin>> ui->cmd;
        if (ui->cmd == 0) {
            rt605.disconnectHRSS();
            ui->run = 0;
        }
        else if (ui->cmd == 1) {
            ui->log = true;
            std::cout << "Start data logger" << std::endl;
        }
        else if (ui->cmd == 2) {
            ui->log = false;
            std::cout << "End data logger" << std::endl;
		}
		else if (ui->cmd == 3) { // run external task
            std::cout << "Run points.hrb" << std::endl;
			rt605.StartProgram("points.hrb");
            Sleep(500);
            ui->log = false;
			ui->run = 1;
        }
        else if (ui->cmd == 4) { // tune on IRED
            ui->IRED_EN = !ui->IRED_EN;
            if (ui->IRED_EN) {
                std::cout << "IRED ENABLED" << std::endl;
            }
            else {
                std::cout << "IRED DISABLED" << std::endl;
            }
        }
        else if (ui->cmd == 5) {
            std::cout << "TEST Trajectory 1006" << std::endl;
            rt605.StartProgram("TEST1006.hrb");
            Sleep(500);
            ui->log = false;
            ui->run = 1;
        }
        else if (ui->cmd == 6) {
            double current_pos[6] = { 0 };
            std::cout << "point trajectory using HRSDK" << std::endl;

            // back to home
            
            rt605.return_home();
            rt605.set_base(10);
            rt605.set_tool(2);
            rt605.print_current_pos();
            rt605.set_speed(500); // 500mm/s

            // start points trajectory
            double x_inc[6] = { 10,0,0,0,0,0 };
            double x_dec[6] = { -10,0,0,0,0,0 };
            double z_dec[6] = { 0,0,-10,0,0,0 };
            std::cout << "Points Trajectory using HRSDK RUNNING" << std::endl;
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
                while(rt605.get_robot_state() != 1){
                    Sleep(10);
                }
                
                rt605.GetRobotPosition(ui->robot_pos);
                rt605.print_current_pos();
                ui->log = true;
                Sleep(100);
                ui->log = false;
            }
            
            rt605.return_home();
            std::cout << "Finished" << std::endl;
        }else if(ui->cmd==7){
            //for white PSD
            rt605.return_home();
            rt605.set_base(10);
            rt605.set_tool(2);
            rt605.print_current_pos();
            rt605.set_speed(500); // 500mm/s

            // PSD 1 moving range from p1 to p2
            double p1[6] = {84.169, 316.065, 273.597, 0, 0, 0};
            double p2[6] = {304.169, 316.065, 93.597, 0, 0, 0};

            double p3[6] = {144.118, 316.065, 275.939, 0, 0, 0};
            double p4[6] = {324.118, 316.065, 55.939, 0, 0, 0};

            // start points trajectory
            double x_inc[6] = { 10,0,0,0,0,0 };
            double x_dec[6] = { -10,0,0,0,0,0 };
            double z_dec[6] = { 0,0,-10,0,0,0 };

            rt605.p2p(p1);

            std::cout << "Points Trajectory using HRSDK RUNNING" << std::endl;
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
                while(rt605.get_robot_state() != 1){
                    Sleep(10);
                }
                
                rt605.GetRobotPosition(ui->robot_pos);
                rt605.print_current_pos();
                ui->log = true;
                Sleep(100);
                ui->log = false;
            }
            
            rt605.return_home();
            std::cout << "Finished" << std::endl;

        }else if(ui->cmd==8){
            //for black PSD
            // PSD 2 moving range from p1 to p2
            rt605.return_home();
            rt605.set_base(10);
            rt605.set_tool(2);
            rt605.print_current_pos();
            rt605.set_speed(500); // 500mm/s

            double p1[6] = {144.118, 316.065, 275.939, 0, 0, 0};
            double p2[6] = {324.118, 316.065, 55.939, 0, 0, 0};

            // start points trajectory
            double x_inc[6] = { 10,0,0,0,0,0 };
            double x_dec[6] = { -10,0,0,0,0,0 };
            double z_dec[6] = { 0,0,-10,0,0,0 };

            rt605.p2p(p1);

            std::cout << "Points Trajectory using HRSDK RUNNING" << std::endl;
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
                while(rt605.get_robot_state() != 1){
                    Sleep(10);
                }
                
                rt605.GetRobotPosition(ui->robot_pos);
                rt605.print_current_pos();
                ui->log = true;
                Sleep(100);
                ui->log = false;
            }
            
            rt605.return_home();
            std::cout << "Finished" << std::endl;
        }
        else {
            std::cout << "Wrong command!!" << std::endl;
        }
       
    }
    std::cout << "terminated\n";
}


void show_ui_menu(void) {
    std::cout << "UI Menu:" << std::endl;
    std::cout << "0: Exit" << std::endl;
    std::cout << "1: Start logger" << std::endl;
    std::cout << "2: End logger" << std::endl;
	std::cout << "3: Run RT605 remotely: points.hrb" << std::endl;
    std::cout << "4: Toggle IRED" << std::endl;
    std::cout << "5: Run RT605 test: TEST2006.hrb" << std::endl;
    std::cout << "6: Run points trajectory usin HRSDK" << std::endl;
    std::cout << "7: Calibration the white PSD" << std::endl;
    std::cout << "8: Calibtracking the black PSD" << std::endl;
    std::cout << "Enter command:";
}
void RunICRC_RTSS(void) {
    wchar_t app_directory[128];
    DWORD len = GetCurrentDirectory(128, app_directory);
    wchar_t PathStr[128] = L"\"";
    lstrcat(PathStr, app_directory);

    HINSTANCE nRet = ShellExecute(NULL, NULL, L"C:\\Program Files\\IntervalZero\\RTX64\\bin\\RTSSRUN", \
        L"D:\\PSD_Measurement\\x64\\RtssDebug\\rt_psd.rtss", NULL, SW_HIDE);
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
