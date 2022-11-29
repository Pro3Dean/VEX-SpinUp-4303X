//robot-config.h

#include "vex_optical.h"
using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor_group LeftDrive;
extern motor LeftDriveMotorA;
extern motor LeftDriveMotorB;
extern motor_group RightDrive;
extern motor RightDriveMotorA;
extern motor RightDriveMotorB;
extern motor Intake;
extern motor LeftFlywheel;
extern motor RightFlywheel;
extern motor_group Flywheel;
extern signature Vision__SIG_1;
extern signature Vision__SIG_2;
extern signature Vision__SIG_3;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;
extern distance Distance;
extern inertial Inertial;
extern digital_out Piston;
extern optical Optical;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );