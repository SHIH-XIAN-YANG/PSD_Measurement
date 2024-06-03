#pragma once
#include "HRSDK_3.0.9/include/HRSDK.h"
#include <fstream>

inline void __stdcall callBack(uint16_t, uint16_t, uint16_t*, int);

bool atimer = false;

class HRSS {
	HROBOT __device_id;
	bool is_Run = false;
	double home[6] = { 0,0,0,0,-90,0 };
	double current_pos[6] = { 0,0,0,0,-90,0 };
	//bool aTimer;

public:
	HRSS() : __device_id(1) {}
	~HRSS() {}

	inline HROBOT connectHRSS(const char* device_ip) {
		__device_id = open_connection(device_ip, 1, callBack);
		set_connection_level(__device_id, 1);
		return __device_id;
	}

	inline void disconnectHRSS(void) {
		if (__device_id >= 0) disconnect(__device_id);
	}
	
	inline void GetRobotPosition(double* pos) {
		get_current_position(__device_id, pos);
	}
	//
	inline void GetRobotPositionCommand(double* pos_cmd) {

	}
	inline int get_hrb(char *hrb_file) {
		return download_file(__device_id, hrb_file, hrb_file); //return 0 if success
	}

	inline int upload_hrb(char* hrb_file) {
		std::ifstream file(hrb_file);
		if (file.good()) {
			return send_file(__device_id, hrb_file, hrb_file);
		}
		else {
			std::cout << "file " << hrb_file << " not exist" << std::endl;
		}
	}
	//
	inline int GetConnectionState(void) {
		return __device_id;
	}
	//
	inline int StartProgram(const char *hrb_filename) {
		set_motor_state(__device_id, 1);

		char* task = new char[strlen(hrb_filename) + 1]; // +1 for the null terminator

		// Copy the string literal into the dynamically allocated memory
		strcpy_s(task, strlen(hrb_filename) + 1, hrb_filename);
		while (!is_Run || atimer) {
			if (!is_Run) {
				task_start(__device_id, task);
				std::cout << "Run " << task << std::endl;
				is_Run = true;
			}
			if (atimer) {
				if (get_function_output(__device_id, 1) == 0) {
					std::cout << "Task " << task << " finished" << std::endl;
					atimer = false;
					delete[]task;
				}
			}
			
			Sleep(1000);
		}
		is_Run = false;
		return 0;
	}

	inline void StopProgram(void) {
		motion_abort(__device_id);
	}

	inline int lin_rel(double* p) {
		for (int i = 0; i < 6; i++) {
			if (p[i] > 150 || p[i] < -150) {
				std::cout << "position Error!" << std::endl;
				return -1;
			}
		}
		return lin_rel_pos(__device_id, 0, 0, p); 
	}

	inline int set_speed(int speed) {
		return set_lin_speed(__device_id, speed);
	}

	inline int set_base(int base) {
		return set_base_number(__device_id, base);
	}

	inline int set_tool(int tool) {
		return set_tool_number(__device_id, tool);
	}

	inline void print_current_pos(void) {
		double pos[6] = { 0 };
		get_current_position(__device_id, pos);
		std::cout << "current position: ";
		for (int k = 0; k < 6; k++) {
			std::cout << pos[k] << " ";
		}
		std::cout << std::endl;
	}

	inline void return_home(void) {
		
		set_home_point(__device_id, home);
		jog_home(__device_id);
		while (get_robot_state() != 1) {
			Sleep(10);
		}
	}

	inline int get_robot_state(void) {
		/*
		0�G�ѿE�Ϫ��A
		1�G���ݡB���m���A
		2�G�B�檬�A
		3�G�Ȱ����A
		4�G���𪬺A
		5�G���ʪ��A
		*/
		return get_motion_state(__device_id);
	}

	inline void p2p(double *p){
		ptp_pos(__device_id, 0, p);
		while(get_robot_state() != 1) {
			Sleep(10);
		}
	}
	
};
static void callBack(uint16_t cmd, uint16_t rlt, uint16_t* msg, int len) {
	char* recv = new char[len];
	for (int i = 0; i < len; i++) {
		recv[i] = (char)msg[i];
	}
	std::string info_p(recv);
	if (cmd == 4001) {
		std::cout << "[Notify] Command: " << cmd << "  Result: " << rlt << "  Msg:  " << recv << std::endl;
		switch (rlt) {
		case 4012:
			printf("[Notify] task_start HRSS_TASK_NAME_ERR\n");
			break;
		case 4013:
			printf("[Notify] task_start Alaeady exist.\n");
			break;
		case 4014:
			printf("[Notify] task_start success. Program starts to Run.\n");
			atimer = true;
			break;
		}
	}
	delete[]recv;
}


