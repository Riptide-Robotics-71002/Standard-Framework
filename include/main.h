/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
    #define _PROS_MAIN_H_

    /**
     * If defined, C++ literals will be available for use. All literals are in the
     * pros::literals namespace.
     *
     * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
     */
    #define PROS_USE_LITERALS

    #include "api.h"

    /**
     * You should add more #includes here
     */
    //#include "okapi/api.hpp"
    //#include "pros/api_legacy.h"

    /**
     * Prototypes for the competition control tasks are redefined here to ensure
     * that they can be called from user code (i.e. calling autonomous from a
     * button press in opcontrol() for testing purposes).
     */
    #ifdef __cplusplus
        extern "C" {
    #endif 
        void autonomous(void);
        void initialize(void);
        void disabled(void);
        void competition_initialize(void);
        void opcontrol(void);
    #ifdef __cplusplus
        }
    #endif

    #ifdef __cplusplus
        /**
         * You can add C++-only headers here
         */
        //#include <iostream>
        #include <cmath>
    #endif

#endif  // _PROS_MAIN_H_

// Constructors for the motor objects
pros::Motor wheel_right_back (
    10, // Port number
    pros::E_MOTOR_GEARSET_18, // Gearset type
    true, // Reverse direction
    pros::E_MOTOR_ENCODER_DEGREES // Rotation measurement units
);
pros::Motor wheel_right_front (
    8, // Port number
    pros::E_MOTOR_GEARSET_18, // Gearset type
    true, // Reverse direction
    pros::E_MOTOR_ENCODER_DEGREES // Rotation measurement units
);
pros::Motor wheel_left_back (
    9, // Port number
    pros::E_MOTOR_GEARSET_18, // Gearset type
    false, // Reverse direction
    pros::E_MOTOR_ENCODER_DEGREES // Rotation measurement units
);
pros::Motor wheel_left_front (
    7, // Port number
    pros::E_MOTOR_GEARSET_18, // Gearset type
    false, // Reverse direction
    pros::E_MOTOR_ENCODER_DEGREES // Rotation measurement units
);
pros::Motor wheel_middle (
    6, // Port number
    pros::E_MOTOR_GEARSET_18, // Gearset type
    false, // Reverse direction
    pros::E_MOTOR_ENCODER_DEGREES // Rotation measurement units
);
// Constructors for the motor group objects
pros::Motor_Group wheels_right ({
    wheel_right_back, 
    wheel_right_front
});
pros::Motor_Group wheels_left ({
    wheel_left_back,
    wheel_left_front
});
pros::Motor_Group wheels ({
    wheel_right_back, 
    wheel_right_front,
    wheel_left_back,
    wheel_left_front,
    wheel_middle
});
// Constructors for controller objects
pros::Controller controller_master (pros::E_CONTROLLER_MASTER);
pros::Controller controller_partner (pros::E_CONTROLLER_PARTNER);

int max_velocity = 200;

void drive() {
    int left_sum = 
        controller_master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)
        +
        controller_master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)
    ;
    int right_sum = 
        controller_master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)
        -
        controller_master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)
    ;
    int left;
    int right;
    if (left_sum>max_velocity) {
        left = max_velocity;
        right = (left/left_sum)*right_sum;
    } else if (right_sum>max_velocity) {
        left = (right/left_sum)*right_sum;
        right = max_velocity;
    } else {
        left = left_sum;
        right = right_sum;
    }
    wheels_left.move_velocity(left);
    wheels_right.move_velocity(right);
    printf("Left: %i, Right: %i\n", left, right);

};