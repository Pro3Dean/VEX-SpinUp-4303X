#include "vex.h"
#include "vex_vision.h"
using namespace vex;
#include "Functions.h"
#include "PID.h"

int autonSelect = 0;
int pageSelect = 0;  //pageSelect 0 is menu, 1 is red and blue, 2 is skills, 3 is flywheel, 4 is variables, 5 is vision, 6 is variable test
int flywheelPct = 75;

void drawMenuScreen(){
  Brain.Screen.setPenColor(color::white);

  Brain.Screen.setFillColor(color::red);
  Brain.Screen.drawRectangle(50, 20, 105, 80);
  Brain.Screen.setCursor(4, 10);
  Brain.Screen.print("Red");

  Brain.Screen.setFillColor(color::blue);
  Brain.Screen.drawRectangle(335, 20, 105, 80);
  Brain.Screen.setCursor(4, 37);
  Brain.Screen.print("Blue");

  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(50, 120, 105, 80);
  Brain.Screen.setCursor(8, 8);
  Brain.Screen.print("Skills");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(335, 120, 105, 80);
  Brain.Screen.setCursor(8, 36);
  Brain.Screen.print("Flywheel");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawCircle(245, 100, 60);
  Brain.Screen.setCursor(6, 21);
  Brain.Screen.print("Variables");
}

void drawVariableTest(){
  Brain.Screen.setFillColor(red);
  
  Brain.Screen.drawRectangle(135, 50, 105, 80);
  Brain.Screen.setCursor(3, 16);
  Brain.Screen.print("drivePID");
  
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(250, 50, 105, 80);
  Brain.Screen.setCursor(3, 28);
  Brain.Screen.print("gyroPID");

  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(365, 50, 105, 80);
  Brain.Screen.setCursor(3, 38);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print("turnWhileDrive");

  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(200, 135, 105, 60);
  Brain.Screen.setCursor(8, 24);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print("Back");

  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(5, 20, 105, 80);
  Brain.Screen.setCursor(3, 38);
  Brain.Screen.print("PLAY");
}

void drawVariableMenu(){
  Brain.Screen.setPenColor(color::white);

  Brain.Screen.setFillColor(color::red);
  Brain.Screen.drawRectangle(100, 5, 105, 40);
  Brain.Screen.setCursor(2, 12);
  Brain.Screen.print("Variables");
  
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(215, 5, 105, 40);
  Brain.Screen.setCursor(2, 25);
  Brain.Screen.print("Vision");

  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(330, 5, 105, 40);
  Brain.Screen.setCursor(2, 37);
  Brain.Screen.print("Test");
}

void drawFlywheelControl(){
  int flywheelPct = 75;
  Brain.Screen.setPenColor(black);
  
  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(175, 100, 105, 80);
  Brain.Screen.setCursor(8, 20);
  Brain.Screen.print("Flywheel");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setCursor(2, 23);
  Brain.Screen.print(static_cast<int>(flywheelPct));

  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(200, 50, 50, 50);
  Brain.Screen.setCursor(4, 23);
  Brain.Screen.print("+");

  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(200, 175, 50, 50);
  Brain.Screen.setCursor(11, 23);
  Brain.Screen.print("-");

  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(20, 20, 105, 60);
  Brain.Screen.setCursor(3, 4);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print("Back");

  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(365, 20, 105, 80);
  Brain.Screen.setCursor(3, 38);
  Brain.Screen.print("SHOOT");
}

void drawVariableControl(){
  drawVariableMenu();
  Brain.Screen.setPenColor(white);

  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(5, 5, 80, 40);
  Brain.Screen.setCursor(2, 3);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print("Back");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setCursor(4, 4);
  Brain.Screen.print("kP");
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(20, 125, 50, 50);
  Brain.Screen.setCursor(8, 3);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print(static_cast<double>(kP));
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(25, 85, 40, 40);
  Brain.Screen.setCursor(6, 5);
  Brain.Screen.print("+");
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(25, 175, 40, 40);
  Brain.Screen.setCursor(10, 5);
  Brain.Screen.print("-");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setCursor(4, 12);
  Brain.Screen.print("kI");
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(90, 125, 50, 50);
  Brain.Screen.setCursor(8, 10);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print(static_cast<double>(kI));
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(95, 85, 40, 40);
  Brain.Screen.setCursor(6, 12);
  Brain.Screen.print("+");
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(95, 175, 40, 40);
  Brain.Screen.setCursor(10, 12);
  Brain.Screen.print("-");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setCursor(4, 18);
  Brain.Screen.print("kD");
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(160, 125, 50, 50);
  Brain.Screen.setCursor(8, 18);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print(static_cast<double>(kD));
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(165, 85, 40, 40);
  Brain.Screen.setCursor(6, 19);
  Brain.Screen.print("+");
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(165, 175, 40, 40);
  Brain.Screen.setCursor(10, 19);
  Brain.Screen.print("-");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setCursor(4, 23);
  Brain.Screen.print("turnKP");
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(225, 125, 50, 50);
  Brain.Screen.setCursor(8, 24);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print(static_cast<double>(turnKP));
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(230, 85, 40, 40);
  Brain.Screen.setCursor(6, 26);
  Brain.Screen.print("+");
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(230, 175, 40, 40);
  Brain.Screen.setCursor(10, 26);
  Brain.Screen.print("-");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setCursor(4, 30);
  Brain.Screen.print("turnKI");
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(290, 125, 50, 50);
  Brain.Screen.setCursor(8, 30);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print(static_cast<double>(turnKI));
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(295, 85, 40, 40);
  Brain.Screen.setCursor(6, 32);
  Brain.Screen.print("+");
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(295, 175, 40, 40);
  Brain.Screen.setCursor(10, 32);
  Brain.Screen.print("-");

  Brain.Screen.setPenColor(black);
  Brain.Screen.setCursor(4, 37);
  Brain.Screen.print("turnKD");
  Brain.Screen.setFillColor(orange);
  Brain.Screen.drawRectangle(360, 125, 50, 50);
  Brain.Screen.setCursor(8, 37);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print(static_cast<double>(turnKD));
  Brain.Screen.setPenColor(black);
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(365, 85, 40, 40);
  Brain.Screen.setCursor(6, 40);
  Brain.Screen.print("+");
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(365, 175, 40, 40);
  Brain.Screen.setCursor(10, 40);
  Brain.Screen.print("-");
}

void drawAutoSelect(){
  Brain.Screen.setPenColor(white);

  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(135, 20, 105, 80);
  Brain.Screen.setCursor(3, 16);
  Brain.Screen.print("AWP");
  
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(250, 20, 105, 80);
  Brain.Screen.setCursor(3, 28);
  Brain.Screen.print("Roller");

  Brain.Screen.setFillColor(yellow);
  Brain.Screen.drawRectangle(365, 20, 105, 80);
  Brain.Screen.setCursor(3, 38);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print("Tape");

  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(200, 115, 105, 60);
  Brain.Screen.setCursor(8, 24);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print("Back");

  }

void drawSkills(){
  Brain.Screen.setPenColor(white);
  
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(135, 20, 105, 80);
  Brain.Screen.setCursor(3, 16);
  Brain.Screen.print("Red Side");
  Brain.Screen.setCursor(4, 17);
  Brain.Screen.print("Start");
  
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(250, 20, 105, 80);
  Brain.Screen.setCursor(3, 27);
  Brain.Screen.print("Blue Side");
  Brain.Screen.setCursor(4, 27);
  Brain.Screen.print("Start");

  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(200, 115, 105, 60);
  Brain.Screen.setCursor(8, 24);
  Brain.Screen.setPenColor(black);
  Brain.Screen.print("Back");
}

double speed;

double x;
int t = 2;
double torque = 2.1;

double manVelocity = 1000;
bool pistonOutOn = false;

void RPM_Adjuster(){
  if(Distance.objectDistance(distanceUnits::in) < 12 || Distance.objectDistance(distanceUnits::in) > 6){
    Flywheel.setVelocity((2000.0/6), velocityUnits::rpm);
    speed = RightFlywheel.velocity(velocityUnits::rpm);
  }else if(Distance.objectDistance(distanceUnits::in) < 18 || Distance.objectDistance(distanceUnits::in) > 12){
    Flywheel.setVelocity((3000.0/7), velocityUnits::rpm);
    speed = RightFlywheel.velocity(velocityUnits::rpm);
  }
}

void velocityChange(){
  if(Distance.isObjectDetected() == 1){
    speed = Distance.objectDistance(distanceUnits::in)/2;
    Flywheel.setVelocity(speed, velocityUnits::rpm);
  }if(Distance.isObjectDetected() == 0){
    speed = Distance.objectDistance(distanceUnits::in)/5;
    Flywheel.setVelocity(speed, velocityUnits::rpm);
  }
}

