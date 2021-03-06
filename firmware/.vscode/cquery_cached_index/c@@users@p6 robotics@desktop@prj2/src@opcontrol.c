/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "shoulder.h"
#include "claw.h"
#include "elbow.h"
#include "wrist.h"


/*
 */
 void operatorControl() {

   Encoder encoder;

   int power;
   int turn;
   int shoulderPower;
   int pot = 0;

   bool is_reversed = false;
   encoder = encoderInit(QUAD_TOP_PORT, QUAD_BOTTOM_PORT, is_reversed);
   // ... Do work
   // Get encoder reading in degrees
   int counts = encoderGet(encoder);

   // ... Do other work
   encoderReset(encoder);

     while (1) {

         power = joystickGetAnalog(1, 1); // vertical axis on left joystick
         turn  = joystickGetAnalog(1, 2); // horizontal axis on right joystick
         motorSet(3, power + turn); // set left wheels
         motorSet(2, power - turn); // set right wheels


         if(joystickGetDigital(1, 8, JOY_UP) == 1) {
           clawSet(127); // pressing up, so lift should go up
         }
         else if(joystickGetDigital(1, 8, JOY_DOWN) == 1) {
           clawSet(-127); // pressing down, so lift should go down

         }
         else {
           clawSet(0);
         }

         // SHOULDER CONTROL

        if(joystickGetDigital(1, 7, JOY_UP) == 1) {
          shoulderSet(127); // pressing up, so lift should go up
        }
        else if(joystickGetDigital(1, 7, JOY_DOWN) == 1) {
          shoulderSet(-127); // pressing down, so lift should go down

        }
        else {
          shoulderSet(0);
        }


        // ELBOW CONTROL

        if(joystickGetDigital(1, 6, JOY_UP) == 1) {
          elbowSet(127); // pressing up, so lift should go up
        }
        else if(joystickGetDigital(1, 6, JOY_DOWN) == 1) {
          elbowSet(-127); // pressing down, so lift should go down

        }
        else {
          elbowSet(0);
        }

        // WRIST CONTROL

        if(joystickGetDigital(1, 5, JOY_UP) == 1) {
          wristSet(127); // pressing up, so lift should go up
        }
        else if(joystickGetDigital(1, 5, JOY_DOWN) == 1) {
          wristSet(-127); // pressing down, so lift should go down
        }
        else {
          wristSet(0);
        }

        delay(20);

        pot = analogRead(2);
        printf("the pot value %d \n", pot);

     }
}
