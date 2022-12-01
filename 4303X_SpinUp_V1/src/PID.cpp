#include "vex.h"
#include "vex_imu.h"
#include "vex_units.h"
using namespace vex;
#include "PID.h"

double kP = 1.4;
double kI = 0.007;
double kD = 5.5;
double turnKP = 0.98;
double turnKI = 0.001;
double turnKD = 5.5;

void drivePID(double target, double angle, bool turnWhileDrive){
  if(turnWhileDrive == false){    
    double threshold;
    if(target <- 0.0){
      threshold = 1.5;
    }else{
      threshold = 0.7;
    }
    double averagePosition = (LeftDriveMotorA.position(rotationUnits::rev) + LeftDriveMotorB.position(rotationUnits::rev) + RightDriveMotorA.position(rotationUnits::rev) + RightDriveMotorB.position(rotationUnits::rev))/4;
    double error = target - averagePosition;
    double integral;
    double derivative;
    double prevError;
    double kP = 1.4;
    double kI = 0.007;
    double kD = 5.5;

    while(fabs(error) > threshold){
      error = target - averagePosition;
      integral = integral + error;
      if(error == 0 || fabs(error) >= target){
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double p = error * kP;
      double i = integral * kI;
      double d = derivative * kD;

      double vel = p + i + d;
    
      LeftDriveMotorA.spin(directionType::fwd, vel, voltageUnits::volt);
      RightDriveMotorA.spin(directionType::fwd, vel, voltageUnits::volt);
      LeftDriveMotorB.spin(directionType::fwd, vel, voltageUnits::volt);
      RightDriveMotorB.spin(directionType::fwd, vel, voltageUnits::volt);
    }

    wait(250, timeUnits::msec);

    double turnThreshold;
    if(angle <- 0.0){
      turnThreshold = 1.5;
    }else{
      turnThreshold = 0.7;
    }
    double turnError = angle - Inertial.rotation(rotationUnits::deg);
    double turnIntegral;
    double turnDerivative;
    double turnPrevError;
    double turnKP = 0.98;
    double turnKI = 0.001;
    double turnKD = 5.5;

    while(fabs(turnError) > turnThreshold){
      turnError = angle - Inertial.rotation(rotationUnits::deg);
      turnIntegral = turnIntegral + turnError;
      if(turnError == 0 || fabs(turnError) >= angle){
        integral = 0;
      }
      turnDerivative = turnError - turnPrevError;
      turnPrevError = turnError;
      double turnP = turnError * turnKP;
      double turnI = turnIntegral * turnKI;
      double turnD = turnDerivative * turnKD;

      double turnVel = turnP + turnI + turnD;

      LeftDriveMotorA.spin(directionType::fwd, turnVel, voltageUnits::volt);
      RightDriveMotorA.spin(directionType::rev, turnVel, voltageUnits::volt);
      LeftDriveMotorB.spin(directionType::fwd, turnVel, voltageUnits::volt);
      RightDriveMotorB.spin(directionType::rev, turnVel, voltageUnits::volt);
    }
  }if(turnWhileDrive == true){
    double averagePosition = (LeftDriveMotorA.position(rotationUnits::rev) + LeftDriveMotorB.position(rotationUnits::rev) + RightDriveMotorA.position(rotationUnits::rev) + RightDriveMotorB.position(rotationUnits::rev))/4;
    double error = target - averagePosition;
    double integral;
    double derivative;
    double prevError;
    double kP = 1.4;
    double kI = 0.007;
    double kD = 5.5;

    double turnThreshold;
    double threshold;
    if(angle <- 0.0 && target <- 0.0){
      turnThreshold = 1.5;
      threshold = 1.5;
    }else{
      turnThreshold = 0.7;
      threshold = 0.7;
    }
    double turnError = angle - Inertial.rotation(rotationUnits::deg);
    double turnIntegral;
    double turnDerivative;
    double turnPrevError;
    double turnKP = 0.98;
    double turnKI = 0.001;
    double turnKD = 5.5;

    while(fabs(turnError) > turnThreshold && fabs(error) > threshold){
      turnError = angle - Inertial.rotation(rotationUnits::deg);
      turnIntegral = turnIntegral + turnError;
      error = target - averagePosition;
      integral = integral + error;
      if((turnError == 0 || fabs(turnError) >= angle) && (error == 0 || fabs(error) >= target)){
        integral = 0;
        turnIntegral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      double p = error * kP;
      double i = integral * kI;
      double d = derivative * kD;

      turnDerivative = turnError - turnPrevError;
      turnPrevError = turnError;
      double turnP = turnError * turnKP;
      double turnI = turnIntegral * turnKI;
      double turnD = turnDerivative * turnKD;

      double vel = p + i + d;
      double turnVel = turnP + turnI + turnD;

      LeftDriveMotorA.spin(directionType::fwd, vel + turnVel, voltageUnits::volt);
      RightDriveMotorA.spin(directionType::fwd, vel - turnVel, voltageUnits::volt);
      LeftDriveMotorB.spin(directionType::fwd, vel + turnVel, voltageUnits::volt);
      RightDriveMotorB.spin(directionType::fwd, vel - turnVel, voltageUnits::volt);
    }
  }
}

void gyroPID(double angle){
  double threshold;
  if(angle <- 0.0){
    threshold = 1.5;
  }
  else{
    threshold = 0.7;
  }

  double error = angle - Inertial.rotation(rotationUnits::deg);
  double integral;
  double derivative;
  double prevError;
  double turnKP = 0.98;
  double turnKI = 0.001;
  double turnKD = 5.5;

  while(fabs(error) > threshold){
    error = angle - Inertial.rotation(rotationUnits::deg);
    integral = integral + error;
    if(error == 0 || fabs(error) >= angle){
      integral = 0;
    }
    derivative = error - prevError;
    prevError = error;
    double p = error * turnKP;
    double i = integral * turnKI;
    double d = derivative * turnKD;

    double vel = p + i + d;

    LeftDriveMotorA.spin(directionType::fwd, vel, voltageUnits::volt);
    RightDriveMotorA.spin(directionType::rev, vel, voltageUnits::volt);
    LeftDriveMotorB.spin(directionType::fwd, vel, voltageUnits::volt);
    RightDriveMotorB.spin(directionType::rev, vel, voltageUnits::volt);
  }
}