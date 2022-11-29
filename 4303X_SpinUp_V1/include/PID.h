#include "vex.h"
using namespace vex;

extern double averagePosition;
extern double error;
extern double integral;
extern double derivative;
extern double prevError;
extern double kP;
extern double kI;
extern double kD;
extern double turnError;
extern double turnIntegral;
extern double turnDerivative;
extern double turnPrevError;
extern double turnKP;
extern double turnKI;
extern double turnKD;
extern double threshold;
extern double turnThreshold;

extern bool turnWhileDrive;

void drivePID(double target, double angle, bool turnWhileDrive=false);
void gyroPID(double angle);