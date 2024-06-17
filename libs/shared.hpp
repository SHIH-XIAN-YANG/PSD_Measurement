#ifndef __SHARED_MEMORY_2_H__
#define __SHARED_MEMORY_2_H__

#include<stdlib.h>
#include<string.h>
#include<cstddef> 
#include<cstdint>
#include <windows.h>
#include <tchar.h>
#include <rtapi.h>    // RTX64 APIs that can be used in real-time and Windows applications.

#include<queue>
#include<array>
//#include<utility>
//#include<vector>

#define EXIT 0
#define RUN 1

#ifdef UNDER_RTSS
#include <rtssapi.h>  // RTX64 APIs that can only be used in real-time applications.
#endif // UNDER_RTSS


// define RTX real-time state
#define KSM_INITIALIZING 0
#define KSM_INIRIALZED 1
#define RT_READY2WRITE_DATA 2
#define RT_RUNNING 3
#define RT_TERMINATING 4


struct PsdData {
	double psd1_vx1, psd1_vx2, psd1_vy1, psd1_vy2;
	double psd2_vx1, psd2_vx2, psd2_vy1, psd2_vy2;
	struct Shm_UI* ui;
};

struct Shm_UI {
	bool run;
	bool log;
	int cmd;
	double x1, y1, sigma1;
	double x2, y2, sigma2;
	bool IRED_EN;
	bool IRED_prev_state;

	int rt_state;
	double robot_pos[6] = { 0 };
	char record_filename[256] = { 0 };
	bool file_create;
	bool file_close;

	Shm_UI(void) {
		cmd = 0;
		log = false;
		run = true;
		file_create = false;
		file_close = false;
		x1 = y1 = sigma1 = 0;
		x2 = y2 = sigma2 = 0;
		IRED_EN = true;
		IRED_prev_state = true;
		rt_state = 0;
	}
};

#endif