//robot-config.cpp

#include "vex.h"
#include "vex_optical.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftDriveMotorA = motor(PORT5, ratio18_1, true);
motor RightDriveMotorA = motor(PORT1, ratio18_1, false);
motor LeftDriveMotorB = motor(PORT9, ratio18_1, true);
motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB);
motor RightDriveMotorB = motor(PORT7, ratio18_1, false);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB);
motor Intake = motor(PORT2, ratio18_1, true);
motor LeftFlywheel = motor(PORT14, ratio18_1, true);
motor RightFlywheel = motor(PORT15, ratio18_1, false);
motor_group Flywheel = motor_group(LeftFlywheel, RightFlywheel);
distance Distance = distance(PORT6);
inertial Inertial = inertial(PORT8);
digital_out Piston = digital_out(Brain.ThreeWirePort.A);
optical Optical = optical(PORT20);
// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}