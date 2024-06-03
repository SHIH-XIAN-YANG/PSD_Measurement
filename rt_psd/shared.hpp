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

#ifdef UNDER_RTSS
#include <rtssapi.h>  // RTX64 APIs that can only be used in real-time applications.
#endif // UNDER_RTSS



struct Shm_UI {
	bool run;
	int cmd;
	double x1, y1, sigma1;
	double x2, y2, sigma2;

	Shm_UI(void) {
		cmd = 0;
		x1 = y1 = sigma1 = 0;
		x2 = y2 = sigma2 = 0;
		run = true;
	}
};


#endif