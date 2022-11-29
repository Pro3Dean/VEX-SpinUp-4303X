// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FrontDrive           motor_group   1, 10           
// RearDrive            motor_group   2, 9            
// Intake               motor         3               
// Flywheel             motor_group   4, 7            
// Vision               vision        5               
// Distance             distance      6               
// Inertial             inertial      8               
// Piston               digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "stdio.h"
#include "vex.h"
#include "VisionSensor.h"
#include "Functions.h"
#include "PID.h"
#include "vex_units.h"

using namespace vex;

// A global instance of competition
competition Competition;

void drawVision(){
  while(pageSelect ==5){
    Brain.Screen.clearScreen();
    Brain.Screen.setOrigin(1, 1);
    Brain.Screen.drawRectangle(0, 0, 316, 212);

    Vision.takeSnapshot(BLUEGOAL);

    if(Vision.largestObject.exists){
      Brain.Screen.drawRectangle(Vision.largestObject.originX, Vision.largestObject.originY, Vision.largestObject.width, Vision.largestObject.height, color::blue);
    }
    
    task::sleep(200);

  }
}

//Functions and/or Variables//
#define TARGET 150

void VisionBlue(){
  while(1){
  if(Vision.installed() == true){
    int numberObjects = Vision.takeSnapshot(BLUEGOAL);
    if (numberObjects > 0){
      vex::vision::object obj = Vision.objects[0];
      if(obj.centerY != 0 && obj.width > 20 && obj.height > 20/*Vision.objects[0].centerX && Vision.objects[0].centerX < 165*/){
        int error = obj.centerY - TARGET;

        //simple P (in PID) Control
        int drive = error;
        if(drive > 50) drive = 50;
        if(drive < -50) drive = -50;

        //once object found and centered
        if(obj.centerY > (TARGET-15) && obj.centerY < (TARGET+15)){
          RightDrive.stop(brakeType::hold);
          LeftDrive.stop(brakeType::hold);
          return;
        }else{
          LeftDrive.spin(directionType::fwd, drive, velocityUnits::rpm);
          RightDrive.spin(directionType::rev, drive, velocityUnits::rpm);
        }
      }
    }else{
      LeftDrive.spin(directionType::fwd, 50, velocityUnits::rpm);
      RightDrive.spin(directionType::rev, 50, velocityUnits::rpm);
    }
    if(Controller1.ButtonX.pressing()){
      LeftDrive.stop(brakeType::brake);
      RightDrive.stop(brakeType::brake);
      return;
    }

    vex::this_thread::sleep_for(50);
    }
  }
}

//............................................................................//
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Calibrating");
 
  flywheelPct = 75;
  autonSelect = 0;
  pageSelect = 0;
  manVelocity = 1000;
  double screenKP = 0;
  double screenKI = 0;
  double screenKD = 0;
  double screenTurnKP = 0.98;
  double screenTurnKI = 0.001;
  double screenTurnKD = 5.5;

  Piston.set(true);
  pistonOutOn = false;
  Piston.set(false);
  pistonOutOn = true;
  Inertial.calibrate(2000);
  task::sleep(2000);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Flywheel Vel");
  Controller1.Screen.setCursor(1, 10);
  Controller1.Screen.print(static_cast<int>(manVelocity));

  Flywheel.setVelocity(flywheelPct, velocityUnits::pct);
  RightFlywheel.setBrake(brakeType::coast);
  LeftFlywheel.setBrake(brakeType::coast);
  Intake.setBrake(brakeType::coast);
  RightDriveMotorA.setBrake(brakeType::brake);
  RightDriveMotorB.setBrake(brakeType::brake);
  LeftDriveMotorA.setBrake(brakeType::brake);
  LeftDriveMotorB.setBrake(brakeType::brake);
 
 drawMenuScreen();
     while(true){
 waitUntil(Brain.Screen.pressing());

 if(pageSelect == 0){
  if(Brain.Screen.xPosition() < 440 && Brain.Screen.xPosition() > 335 && Brain.Screen.yPosition() < 100 && Brain.Screen.yPosition() > 20){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();   //blue
    drawAutoSelect();
    pageSelect = 1;
  }else if(Brain.Screen.xPosition() < 155 && Brain.Screen.xPosition() > 50 && Brain.Screen.yPosition() < 100 && Brain.Screen.yPosition() > 20){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();   //red
    drawAutoSelect();
    pageSelect = 1;
  }if(Brain.Screen.xPosition() < 155 && Brain.Screen.xPosition() > 50 && Brain.Screen.yPosition() < 200 && Brain.Screen.yPosition() > 120){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();   //skills
    drawSkills();
    pageSelect = 2;
  }if(Brain.Screen.xPosition() < 440 && Brain.Screen.xPosition() > 335 && Brain.Screen.yPosition() < 200 && Brain.Screen.yPosition() > 120){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();   //flywheel
    drawFlywheelControl();
    pageSelect = 3;
  }if(Brain.Screen.xPosition() < 305 && Brain.Screen.xPosition() > 185 && Brain.Screen.yPosition() < 160 && Brain.Screen.yPosition() > 40){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();   //variable
    drawVariableControl();
    pageSelect = 4;
  }
 }
 if(pageSelect == 1){ //Red or Blue
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 0;
  if(Brain.Screen.xPosition() < 240 && Brain.Screen.xPosition() > 135){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawAutoSelect();
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 1;
  }if(Brain.Screen.xPosition() < 355 && Brain.Screen.xPosition() > 250){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawAutoSelect();
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 2;
  }if(Brain.Screen.xPosition() < 470 && Brain.Screen.xPosition() > 365){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawAutoSelect();
    Brain.Screen.setFillColor(yellow);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 3;
  }if(Brain.Screen.xPosition() < 305 && Brain.Screen.xPosition() > 200 && Brain.Screen.yPosition() > 115){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawMenuScreen();
    pageSelect = 0;
  }
 }
 if(pageSelect == 2){
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 0;
  if(Brain.Screen.xPosition() < 240 && Brain.Screen.xPosition() > 135){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawSkills();
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 1;
  }if(Brain.Screen.xPosition() < 355 && Brain.Screen.xPosition() > 250){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawSkills();
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 2;
  }if(Brain.Screen.xPosition() < 305 && Brain.Screen.xPosition() > 200 && Brain.Screen.yPosition() > 115){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawMenuScreen();
    pageSelect = 0;
  }
}
if(pageSelect == 3){
  if(Brain.Screen.xPosition() < 125 && Brain.Screen.xPosition() > 20){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawMenuScreen();
    pageSelect = 0;
  }if(Brain.Screen.xPosition() < 250 && Brain.Screen.xPosition() > 200 && Brain.Screen.yPosition() < 100){
      if(flywheelPct >= 100){
        flywheelPct = 100;
      }else{
      wait(250, timeUnits::msec);
      flywheelPct += 5;
      Brain.Screen.clearScreen();
      drawFlywheelControl();
      Brain.Screen.setPenColor(black);
      Brain.Screen.setCursor(2, 23);
      Brain.Screen.print(static_cast<int>(flywheelPct));
      }
  }if(Brain.Screen.xPosition() < 250 && Brain.Screen.xPosition() > 200 && Brain.Screen.yPosition() > 190){
      if(flywheelPct <= 0){
        flywheelPct = 0;
      }else{
        wait(250, timeUnits::msec);
        flywheelPct -= 5;
        Brain.Screen.clearScreen();
        drawFlywheelControl();
        Brain.Screen.setPenColor(black);
        Brain.Screen.setCursor(2, 23);
        Brain.Screen.print(static_cast<int>(flywheelPct));
      }
  }if(Brain.Screen.xPosition() < 470 && Brain.Screen.xPosition() > 365 && Brain.Screen.yPosition() < 100){
    wait(250, timeUnits::msec);
    Brain.Screen.setCursor(8, 35);
    Brain.Screen.print("SPINNING!");
    Flywheel.spin(directionType::fwd, flywheelPct, percentUnits::pct);
    if((Flywheel.velocity(velocityUnits::pct) +- 2.5) == flywheelPct){
      wait(2.5, timeUnits::sec);
      Flywheel.spin(directionType::fwd, flywheelPct, percentUnits::pct);
      Brain.Screen.clearLine(8);
      Brain.Screen.setCursor(8, 35);
      Brain.Screen.print("FIRING!!!");
      wait(5, timeUnits::sec);
      Piston.set(true);
      pistonOutOn = false;
      wait(100, timeUnits::msec);
      Piston.set(false);
      pistonOutOn = true;
    }if(pistonOutOn == true){
      wait(250, timeUnits::msec);
      Flywheel.stop(brakeType::coast);
      Brain.Screen.clearScreen();
      drawFlywheelControl();
      Brain.Screen.setPenColor(black);
      Brain.Screen.setCursor(2, 23);
      Brain.Screen.print(static_cast<int>(flywheelPct));
    }
  }
}
if(pageSelect == 4){
   if(Brain.Screen.xPosition() < 85 && Brain.Screen.xPosition() > 5 && Brain.Screen.yPosition() < 45 && Brain.Screen.yPosition() > 5){
      wait(250, timeUnits::msec);
      Brain.Screen.clearScreen();
      drawMenuScreen();
      pageSelect = 0;
  }if(Brain.Screen.xPosition() < 65 && Brain.Screen.xPosition() > 25 && Brain.Screen.yPosition() < 125 && Brain.Screen.yPosition() > 85){
      wait(250, timeUnits::msec);
      screenKP += 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 65 && Brain.Screen.xPosition() > 25 && Brain.Screen.yPosition() < 215 && Brain.Screen.yPosition() > 175){
      wait(250, timeUnits::msec);
      screenKP -= 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 135 && Brain.Screen.xPosition() > 95 && Brain.Screen.yPosition() < 125 && Brain.Screen.yPosition() > 85){
      wait(250, timeUnits::msec);
      screenKI += 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 135 && Brain.Screen.xPosition() > 95 && Brain.Screen.yPosition() < 215 && Brain.Screen.yPosition() > 175){
      wait(250, timeUnits::msec);
      screenKI -= 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 205 && Brain.Screen.xPosition() > 165 && Brain.Screen.yPosition() < 125 && Brain.Screen.yPosition() > 85){
      wait(250, timeUnits::msec);
      screenKD += 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 205 && Brain.Screen.xPosition() > 165 && Brain.Screen.yPosition() < 215 && Brain.Screen.yPosition() > 175){
      wait(250, timeUnits::msec);
      screenKD -= 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 270 && Brain.Screen.xPosition() > 230 && Brain.Screen.yPosition() < 125 && Brain.Screen.yPosition() > 85){
      wait(250, timeUnits::msec);
      screenTurnKP += 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 270 && Brain.Screen.xPosition() > 230 && Brain.Screen.yPosition() < 215 && Brain.Screen.yPosition() > 175){
      wait(250, timeUnits::msec);
      screenTurnKP -= 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 335 && Brain.Screen.xPosition() > 295 && Brain.Screen.yPosition() < 125 && Brain.Screen.yPosition() > 85){
      wait(250, timeUnits::msec);
      screenTurnKI += 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 335 && Brain.Screen.xPosition() > 295 && Brain.Screen.yPosition() < 215 && Brain.Screen.yPosition() > 175){
      wait(250, timeUnits::msec);
      screenTurnKI -= 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 405 && Brain.Screen.xPosition() > 365 && Brain.Screen.yPosition() < 125 && Brain.Screen.yPosition() > 85){
      wait(250, timeUnits::msec);
      screenTurnKD += 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 405 && Brain.Screen.xPosition() > 365 && Brain.Screen.yPosition() < 215 && Brain.Screen.yPosition() > 175){
      wait(250, timeUnits::msec);
      screenTurnKD -= 0.05;
      Brain.Screen.clearScreen();
      drawVariableControl();
  }if(Brain.Screen.xPosition() < 320 && Brain.Screen.xPosition() > 215 && Brain.Screen.yPosition() < 45 && Brain.Screen.yPosition() > 5){
      wait(250, timeUnits::msec);
      Brain.Screen.clearScreen();
      pageSelect = 5;
  }if(Brain.Screen.xPosition() < 435 && Brain.Screen.xPosition() > 330 && Brain.Screen.yPosition() < 45 && Brain.Screen.yPosition() > 5){
      wait(250, timeUnits::msec);
      Brain.Screen.clearScreen();
      drawVariableTest();
      pageSelect = 6;
  }
}if(pageSelect == 5){
  drawVariableMenu();
  while(pageSelect ==5){
    Brain.Screen.clearScreen();
    Brain.Screen.setOrigin(1, 1);
    Brain.Screen.drawRectangle(0, 0, 316, 212);

    Vision.takeSnapshot(BLUEGOAL);

    if(Vision.largestObject.exists){
      Brain.Screen.drawRectangle(Vision.largestObject.originX, Vision.largestObject.originY, Vision.largestObject.width, Vision.largestObject.height, color::blue);
    }
    
    task::sleep(200);

  }
}if(pageSelect == 6){
    drawVariableMenu();
    Brain.Screen.setFillColor(white);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 0;
  if(Brain.Screen.xPosition() < 240 && Brain.Screen.xPosition() > 135){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawVariableMenu();
    drawVariableTest();
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 1;
  }if(Brain.Screen.xPosition() < 355 && Brain.Screen.xPosition() > 250){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawVariableMenu();
    drawVariableTest();
    Brain.Screen.setFillColor(blue);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 2;
  }if(Brain.Screen.xPosition() < 470 && Brain.Screen.xPosition() > 365){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawVariableMenu();
    drawVariableTest();
    Brain.Screen.setFillColor(yellow);
    Brain.Screen.drawRectangle(20, 200, 440, 10);
    autonSelect = 3;
  }if(Brain.Screen.xPosition() < 305 && Brain.Screen.xPosition() > 200 && Brain.Screen.yPosition() > 135){
    wait(250, timeUnits::msec);
    Brain.Screen.clearScreen();
    drawMenuScreen();
    pageSelect = 0;
  }if(Brain.Screen.xPosition() < 110 && Brain.Screen.xPosition() > 5 && Brain.Screen.yPosition() < 100 && Brain.Screen.yPosition() > 20){
    wait(250, timeUnits::msec);
    if(pageSelect == 6){
      if(autonSelect == 1){
        kP = screenKP;
        kI = screenKI;
        kD = screenKD;
        drivePID(15, 0, false);
      }if(autonSelect == 2){
        turnKP = screenTurnKP;
        turnKI = screenTurnKI;
        turnKD = screenTurnKD;
        gyroPID(90);
      }if(autonSelect == 3){
        kP = screenKP;
        kI = screenKI;
        kD = screenKD;
        turnKP = screenTurnKP;
        turnKI = screenTurnKI;
        turnKD = screenTurnKD;
        drivePID(15, 90, true);
      }
    }
  }
}
}
}


void autonomous(void) {
  /*if(pageSelect == 1){
    if(autonSelect == 0){
      
    }else if(autonSelect == 1){

    }else if(autonSelect == 2){
      drivePID(-20, 0);
      wait(100, timeUnits::msec);
        if(Optical.color() == vex::color::red){
          Intake.spin(directionType::fwd);
        }else{
          Intake.stop(brakeType::brake);
        }
      wait(100, timeUnits::msec);
      drivePID(20, 35, true);
      wait(100, timeUnits::msec);
      Intake.spin(directionType::fwd);
      drivePID(50, 90);
      wait(100, timeUnits::msec);
      Intake.stop(brakeType::brake);
      LeftDrive.stop(brakeType::brake);
      RightDrive.stop(brakeType::brake);
      VisionBlue();
      velocityChange();
      Flywheel.spin(directionType::fwd);
      Piston.set(true);
      pistonOutOn = false;
      wait(100, timeUnits::msec);
      Piston.set(false);
      pistonOutOn = true;
        if(pistonOutOn == true){
          wait(250, timeUnits::msec);
          Flywheel.stop(brakeType::coast);
        }
    }
  }*/
  drivePID(20, 35, false);
}


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Flywheel Vel");
  Controller1.Screen.setCursor(1, 10);
    Controller1.Screen.print(static_cast<int>(manVelocity));
    Flywheel.setVelocity(100, percentUnits::pct);                                           //Flywheel will always be set to a velocity of 100%

    LeftDrive.spin(directionType::fwd, Controller1.Axis2.position(), velocityUnits::pct);
    RightDrive.spin(directionType::fwd, Controller1.Axis3.position(), velocityUnits::pct);   //Using Tank drive control
    
    if(Controller1.ButtonUp.pressing()){                                                    //Control Intakes
      Intake.spin(directionType::fwd);
    }else if(Controller1.ButtonDown.pressing()){
      Intake.spin(directionType::rev);
    }else{
      Intake.stop(brakeType::coast);
    }

    if(Controller1.ButtonRight.pressing()){                                                //Allow us to change the speed of the flywheel by an increment of +- 100
      manVelocity = manVelocity + 100;
      Flywheel.setVelocity((manVelocity/6), velocityUnits::rpm);
    }if(Controller1.ButtonLeft.pressing()){
      manVelocity = manVelocity - 100;
      Flywheel.setVelocity((manVelocity/6), velocityUnits::rpm);
    }

    if(Controller1.ButtonA.pressing()){
      Flywheel.spin(directionType::fwd);
    }

    Controller1.ButtonX.pressed(VisionBlue);
    if(Controller1.ButtonA.pressing()){   
      Flywheel.spin(directionType::fwd);                                                  //Once button is pressed, the flywheel will start to rev up
        if(pistonOutOn == true && ((Flywheel.velocity(velocityUnits::pct) == (manVelocity +- 5)))){        
          for(int i = 0; i < 3; i++){                                                     //Once the flywheel has hit 100% speed, it will shot the disc 3 times every 0.5 seconds
            Piston.set(true); 
            pistonOutOn = false;
            wait(0.25, timeUnits::sec);
            Piston.set(false);
            pistonOutOn = true;
            wait(0.25, timeUnits::sec);
          }
        }else{
          Flywheel.stop(brakeType::coast);                                                  //the flywheel will slowly come to a halt to ensure the flywheel motor does not burn out from the pressure
          Piston.set(false);
          pistonOutOn = true;
          wait(0.5, timeUnits::sec);
        } 
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
