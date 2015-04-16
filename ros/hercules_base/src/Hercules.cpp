#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include <ros/ros.h>
#include <ros/console.h>
#include "Hercules.h"

using namespace std;

//#define CMD_DRIVE "D%c%c"
#define CMD_DRIVE "D%d,%d,%d,%d,"

#define MAX_LEVEL	100
#define MAX_SPEED	10.0		// 10 m/s

Hercules::Hercules()
{
}

Hercules::~Hercules() {
	if (mSerialPtr) {
		delete mSerialPtr;
	}
}

void Hercules::reconnect() {
	mSerialPtr->Open(SerialPort::BAUD_19200,
				SerialPort::CHAR_SIZE_8,
				SerialPort::PARITY_DEFAULT,
				SerialPort::STOP_BITS_DEFAULT,
				SerialPort::FLOW_CONTROL_DEFAULT);
}

void Hercules::connect(const string &port) {
	mPort = port;
	mSerialPtr = new SerialPort(port);
	reconnect();
}

void Hercules::configureLimits(double max_speed, double max_accel) {

}

void Hercules::controlSpeed(double speed_left, double speed_right,
		double accel_left, double accel_right) {
	int signL = speed_left < 0 ? 0x80 : 0;
	int signR = speed_right < 0 ? 0x80 : 0;

	speed_left = fabs(speed_left);
	speed_right = fabs(speed_right);

	int lspeed = speedToLevel(speed_left);
	int rspeed = speedToLevel(speed_right);
        ROS_DEBUG("Hercules int lspeed=%d, rspeed=%d", lspeed, rspeed);
	sendDriveCmd(lspeed, signL, rspeed, signR);
}

void Hercules::sendDriveCmd(int leftSpeed, int leftDir, int rightSpeed, int rightDir) {
	char buf[20];
	snprintf(buf, sizeof(buf), CMD_DRIVE, leftSpeed, rightSpeed, leftDir, rightDir);
	mSerialPtr->Write(buf);
        ROS_DEBUG("Hercules string buf:%s \n", buf);
}

int Hercules::speedToLevel(double speed) {
        int level = speed * MAX_LEVEL;
        if (level >=100 ) level = 99;
        return level;
}