//////////////////////////////////////////////////////////////////
//
// rt_psd.cpp - cpp file
//
// This file was generated using the RTX64 Application Template for Visual Studio.
//
// Created: 4/16/2024 4:25:46 PM 
// User: User
//
//////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include "rt_psd.h"

#define FEEDBACK_CYCLE 0.5 // 0.5ms (unit: ms)
#define ETHERCAT_CYCLE CycleTime::cycle500
   
void ksm_intitial(void);

LARGE_INTEGER glb_cpuFreq;
LARGE_INTEGER glb_tick_begin;
LARGE_INTEGER glb_tick_now;
FILE *fs;


struct PsdData psd_data;


int _tmain(int argc, _TCHAR * argv[])
{ 
	
	
	// shared memory:
	struct Shm_UI* ui;
	HANDLE ui_handler = RtCreateSharedMemory(0, 0, sizeof(Shm_UI), L"SHM_UI", (void**)&(psd_data.ui));
	psd_data.ui->rt_state = KSM_INITIALIZING;
	ksm_intitial();
	psd_data.ui->rt_state = KSM_INIRIALZED;



	QueryPerformanceFrequency(&glb_cpuFreq);
	QueryPerformanceCounter(&glb_tick_begin);
  
	//set up timer
	LARGE_INTEGER liPeriod_feedback;
	HANDLE hTimer_feedback = RtCreateTimer(NULL, 0, RtMeasurementRoutine, (void*)&psd_data, RT_PRIORITY_MAX, CLOCK_FASTEST);	//create timer
	liPeriod_feedback.QuadPart = static_cast<LONGLONG>(FEEDBACK_CYCLE * 10000.0);												//timer setting
	RtSetTimerRelative(hTimer_feedback, &liPeriod_feedback, &liPeriod_feedback);
	
	////log data - write to file
	//wchar_t *dir = L"D:\\PSD_Measurement\\";
	//wchar_t wcspath[256];
	//wchar_t* dump_c = wcsrchr(dir, '\\');
	//if (dump_c != NULL)
	//	*dump_c = '\0';

	//wcscpy_s(wcspath, dir);

	//char path[256];
	//wcstombs(path, wcspath, 256);

	//SYSTEMTIME LocalTime;
	//GetLocalTime(&LocalTime); // generate file name
	//char fileName[MAX_PATH] = {};
	//int n = sprintf_s(fileName, sizeof(fileName), "\\data_log\\%d_%d_%d_%d_%d.csv", LocalTime.wYear,
	//	LocalTime.wMonth,
	//	LocalTime.wDay,
	//	LocalTime.wHour,
	//	LocalTime.wMinute );
	//strcat_s(path, fileName);
	//RtPrintf("PSD data logger on: %s\n", path);
	//if (fs != nullptr)
	//	fs = nullptr;
	//fopen_s(&fs, path, "w+");
	//if (fs != nullptr) {
	//	fprintf_s(fs, "time(ms), Vx1_1(V), Vx2_1(V), Vy1_1(V), Vy2_1(V), x1(mm), y1(mm), sigma1(V), dx1(V), dy1(V), Vx1_2(V), Vx2_2(V), Vy1_2(V), Vy2_2(V) , x2(mm), y2(mm), sigma2(V),dx2(V),dy2(V), x(mm), y(mm),z(mm)\n");
	//	psd_data.ui->rt_state = RT_READY2WRITE_DATA;
	//}else {
	//	RtPrintf("open file faled...\n");
	//	RtCancelTimer(hTimer_feedback, &liPeriod_feedback);
	//	RtCloseHandle(hTimer_feedback);
	//	StopLink();
	//	RtPrintf("Terminate the .rtss process.\n");
	//	//RtPrintf("terminated\n");
	//	return 0;
	//}

	// start IRED trigger
	WriteOutputBit(5, 0, 1);
	RtPrintf("IRED on\n");

	psd_data.ui->rt_state = RT_RUNNING;
	while (psd_data.ui->run) {
		//busy waiting
		if (psd_data.ui->file_create) {
			const wchar_t* dir = L"E:\\samuel\\PSD_Measurement\\data_log\\";
			wchar_t wcspath[256];
			wcscpy_s(wcspath, dir);  // Ensure wcspath is large enough
			char path[256] = { 0 };
			// Convert wide char path to multibyte char path
			size_t convertedChars = 0;
			wcstombs_s(&convertedChars, path, wcspath, 256);

			SYSTEMTIME LocalTime;
			GetLocalTime(&LocalTime); // Generate file name

			char fileName[MAX_PATH] = {};
			int n = sprintf_s(fileName, sizeof(fileName), "%d_%d_%d_%d_%d.csv",
				LocalTime.wYear, LocalTime.wMonth, LocalTime.wDay,
				LocalTime.wHour, LocalTime.wMinute);


			strcat_s(path, fileName);

			if (fs != nullptr) {
				fs = nullptr;
			}

			errno_t err = fopen_s(&fs, path, "w+");
			fprintf_s(fs, "time(ms),Vx1_1(V),Vx2_1(V),Vy1_1(V),Vy2_1(V),x1(mm),y1(mm),sigma1(V),dx1(V),dy1(V)," \
				"Vx1_2(V),Vx2_2(V),Vy1_2(V),Vy2_2(V),x2(mm),y2(mm),sigma2(V),dx2(V),dy2(V),x(mm),y(mm),z(mm)\n");
			RtPrintf("PSD data logger on: %s", path);
			strcpy_s(psd_data.ui->record_filename, path);
			psd_data.ui->log = true;
			psd_data.ui->file_create = false;
		}
		if (psd_data.ui->file_close) {
			//close file
			fflush(fs);
			if (fs != nullptr) {
				fclose(fs);
				fs = nullptr;
			}
			psd_data.ui->log = false;
			psd_data.ui->file_close = false;
			RtPrintf("log off");
		}

		RtSleep(10); // sleep 1 second
	}
	psd_data.ui->rt_state = RT_TERMINATING;


	WriteOutputBit(5, 0, 0);
	RtPrintf("IRED off\n");

	fflush(fs);
	if(fs!=nullptr)
		fclose(fs);

	RtCancelTimer(hTimer_feedback, &liPeriod_feedback);
	RtCloseHandle(hTimer_feedback);
	StopLink();
	RtPrintf("Terminate the .rtss process.\n");
	//RtPrintf("terminated\n");
    return 0;
}

void ksm_intitial(void) {
	int Ret{ 0 };
	unsigned short retry{ 20 };
#pragma region initialize_ksm_and_EtherCAT
	if (!Initialized()) {
		Ret = InitializeLink(0);
		//RtSleep(1000); // wait for 0.5 seconds
		//if (--retry)// send error code.
		//	break;
	}
	retry = 20;
	if (Initialized()) {
		RtPrintf("\n-Initializing ......\n");
		if (!Created()) {
			Ret = CreateLink();
			//RtSleep(1000); // wait for 0.5 seconds
			//if (--retry)// send error code.
			//	break;
		}
	}
	retry = 20;
	if (Created()) {
		RtPrintf("-Created.\n");
		Ret = SetAccessMode(accessVelPos);
		Ret = SetInterpolation(ETHERCAT_CYCLE);
		Ret = EnableDcCheck(TRUE);
		Ret = EnableSynchronizedControlMode(TRUE);
		Ret = EnableTorqueControl(TRUE);
		Ret = EnableServoOutputAccess(TRUE);
		//Ret = ConfigureIoCount(1);
		if (!Started())
			Ret = StartLink();
		RtPrintf(" \n- Waiting for 30 secconds .......\n");
		RtSleep(30000);
	}
	//if (Started()) {
	//	RtPrintf("\n-Started.\n");
	//	RtPrintf("Set servo control mode: modeMasterIntPos\n");
	//	for (int i = 0; i < 6; ++i) {
	//		Ret = SetServoControlMode(i, modeMasterIntPos);
	//		Ret = SetServoInterpolation(i, 500);
	//	}
	//}

	unsigned char CH0_EN[2] = { 1,0 };
	unsigned char CH1_EN[2] = { 1,0 };
	unsigned char CH2_EN[2] = { 1,0 };
	unsigned char CH3_EN[2] = { 1,0 };

	unsigned char sampling_rate[2] = { 1,0 }; // 100KHz
	unsigned char range_mode[2] = { 1,0 };    // -5~5V

	// Device initialize: PSD #1
	WriteSdoObject(7, 0x2002, 1, CH0_EN, 2); 
	WriteSdoObject(7, 0x2002, 2, CH1_EN, 2);
	WriteSdoObject(7, 0x2002, 3, CH2_EN, 2);
	WriteSdoObject(7, 0x2002, 4, CH3_EN, 2);

	WriteSdoObject(7, 0x2000, 0, sampling_rate, 2);
	WriteSdoObject(7, 0x2001, 0, range_mode, 2);

	// Device initialize: PSD #2
	WriteSdoObject(8, 0x2002, 1, CH0_EN, 2);
	WriteSdoObject(8, 0x2002, 2, CH1_EN, 2);
	WriteSdoObject(8, 0x2002, 3, CH2_EN, 2);
	WriteSdoObject(8, 0x2002, 4, CH3_EN, 2);

	WriteSdoObject(8, 0x2000, 0, sampling_rate, 2);
	WriteSdoObject(8, 0x2001, 0, range_mode, 2);
#pragma endregion initialize_ksm_and_EtherCAT
}