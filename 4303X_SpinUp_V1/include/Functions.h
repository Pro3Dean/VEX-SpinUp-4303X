#include "vex.h"
using namespace vex;

extern int autonSelect;
extern int pageSelect;
extern double manVelocity;
extern bool pistonOutOn;
extern int flywheelPct;
extern double speed;
extern double screenKP;
extern double screenKI;
extern double screenKD;
extern double screenTurnKP;
extern double screenTurnKI;
extern double screenTurnKD;

void drawMenuScreen();
void drawVariableMenu();
void drawVariableTest();
void drawAutoSelect();
void drawFlywheelControl();
void drawVariableControl();
void drawSkills();
void RPM_Adjuster();
void velocityChange();
