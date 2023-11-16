/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10, D        
// ClawMotor            motor         3               
// ArmMotor             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include<bits/stdc++.h>
#include "vex.h"

using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

int clawMotorPosition = 65; // setting default position of claw motor
int clawDestination = 0; // destination of claw motor

void spinClawMotor(){
  if (clawMotorPosition == clawDestination) ClawMotor.spin(vex::forward, 0, voltageUnits::volt);;
  if (clawDestination > clawMotorPosition){
    ClawMotor.spin(vex::forward, 7, voltageUnits::volt);
    clawMotorPosition++;
  } else if (clawDestination < clawMotorPosition){
    ClawMotor.spin(vex::forward, -7, voltageUnits::volt);
    clawMotorPosition--;
  }
}


directionType findDirFromVolt(int volts){
  if (volts >= 0) return vex::forward;
  else return vex::reverse;
}

int valueNotZero(int a, int b){
  if (a != 0) return a;
  else return b;
}

int valueNotZero(double a, double b){
  if (a != 0.0) return a;
  else return b;
}

int signs(double a){
  if (a >= 0.0) return 1;
  else return -1;
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {


  RightMotor.spin(vex::forward, 5, voltageUnits::volt);
  LeftMotor.spin(vex::forward, 5, voltageUnits::volt);

  wait(1, seconds);

  RightMotor.spin(vex::forward, 0, voltageUnits::volt);
  LeftMotor.spin(vex::forward, 0, voltageUnits::volt);

  ClawMotor.spin(vex::forward, -7, voltageUnits::volt);

  wait(1.5, seconds);

  ClawMotor.spin(vex::forward, 0, voltageUnits::volt);

  ArmMotor.spin(vex::forward, 231987349, voltageUnits::volt);

  wait(2, seconds);

  ArmMotor.spin(vex::forward, 0, voltageUnits::volt);

  RightMotor.spin(vex::forward, 5, voltageUnits::volt);

  wait(1, seconds);

  RightMotor.spin(vex::forward, 5, voltageUnits::volt);
  LeftMotor.spin(vex::forward, 5, voltageUnits::volt);

  wait(1, seconds);

  RightMotor.spin(vex::forward, 0, voltageUnits::volt);
  LeftMotor.spin(vex::forward, 0, voltageUnits::volt);

  ArmMotor.spin(vex::reverse, 231987349, voltageUnits::volt);

  wait(2, seconds);

  ArmMotor.spin(vex::reverse, 0, voltageUnits::volt);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  while (1) {

    // wheel movement

    // joystick percentages range from -100 to 100 (left to right/down to up)
    // Axis 3-4 are left joystick, 3 is up and down while 4 is left to right
    // Axis 1-2 are right joystick, 2 is up and down while 1 is left to right

    double turnVolts = valueNotZero(Controller1.Axis1.position(percent) * 0.075 / 2, signs(Controller1.Axis4.position(percent)) * max(0, (int)(abs(Controller1.Axis4.position(percent)) - 75)) * 0.2);
    double forwardVolts = Controller1.Axis3.position(percent) * 0.075;

    int rightVolts = forwardVolts - turnVolts;
    int leftVolts = forwardVolts + turnVolts;

    RightMotor.spin(vex::forward, rightVolts, voltageUnits::volt);
    LeftMotor.spin(vex::forward, leftVolts, voltageUnits::volt);

    // claw and arm movement

    int r1 = -Controller1.ButtonR1.pressing();
    int l1 = Controller1.ButtonL1.pressing();

    int r2 = Controller1.ButtonR2.pressing();
    int l2 = -Controller1.ButtonL2.pressing();

    ArmMotor.spin(vex::forward, (r2+l2)*231987349, voltageUnits::volt);

    ClawMotor.spin(vex::forward, (r1+l1)*7, voltageUnits::volt);

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

  // Run the pre-autonomous function.
  pre_auton();

  // Run the autonomous function.
  autonomous();

  Competition.drivercontrol(usercontrol);

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
