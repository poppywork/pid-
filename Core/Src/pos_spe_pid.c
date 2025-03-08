//
// Created by 24319 on 2025/3/9.
//

#include <stdint-gcc.h>
#include <stdlib.h>
#include <stdio.h>
#include "pos_spe_pid.h"
#include "AI.h"
#include "car_control.h"
#include "OLED.h"
//待改参数
#define TARGET_DISTANCE 10  //目标距离 单位米


#define POSITION_KP 0.6
#define POSITION_KI 0.1
#define POSITION_KD 0.01
#define SPEED_KP 1.2
#define SPEED_KI 0.07
#define SPEED_KD 0.01
#define ERROR_CAR_ANGLE 5//用于小车两边车轮速度不同，通过MPU6050给一个偏角
extern float yaw;
extern uint8_t display_buf[20];
PIDController position_pid_1, speed_pid_1;
PIDController position_pid_2, speed_pid_2;
int32_t previous_position_1 = 0, previous_position_2 = 0;
void pos_spe_pid(void)
{
    //初始化目标值和pid
    PID_Init(&position_pid_1, POSITION_KP, POSITION_KI, POSITION_KD, (TARGET_DISTANCE*3750+100)/100.0);//一米对应3750脉冲
    PID_Init(&speed_pid_1, SPEED_KP, SPEED_KI, SPEED_KD, 0);
    PID_Init(&position_pid_2, POSITION_KP, POSITION_KI, POSITION_KD, (TARGET_DISTANCE*3750+100)/100.0);///100防止溢出
    PID_Init(&speed_pid_2, SPEED_KP, SPEED_KI, SPEED_KD, 0);


    int32_t current_position_1 = Read_Speed(&htim2)+100;//+10防止开始时为65355,导致疯转
    int32_t current_position_2 = Read_Speed(&htim3)+100;
    sprintf((char *)display_buf,"%d   ",current_position_1);
    OLED_ShowString(1,3,display_buf);
    sprintf((char *)display_buf,"%d   ",current_position_2);
    OLED_ShowString(2,3,display_buf);

    int32_t current_speed_1 = current_position_1 - previous_position_1;
    int32_t current_speed_2 = current_position_2 - previous_position_2;
    previous_position_1 = current_position_1;
    previous_position_2 = current_position_2;

    float position_output_1 = pid_calculate(&position_pid_1, current_position_1/100.0);///100防止溢出
    float position_output_2 = pid_calculate(&position_pid_2, current_position_2/100.0);

    speed_pid_1.Target = position_output_1;
    speed_pid_2.Target = position_output_2;

    float speed_output_1 = pid_calculate(&speed_pid_1, current_speed_1);
    float speed_output_2 = pid_calculate(&speed_pid_2, current_speed_2);
//    float speed_difference = current_position_1 - current_position_2;
    float correction_factor = 6.5;  // 修正系数，可根据实际调整
//
//    // 如果速度差值过大，调整速度使小车走直线
//    if (speed_difference > 2) {
//        speed_output_1 -= correction_factor * speed_difference;
//        speed_output_2 += correction_factor * speed_difference;
//    }
//    if (speed_difference < -2) {
//        speed_output_1 += correction_factor * speed_difference;
//        speed_output_2 -= correction_factor * speed_difference;
//    }
    float angle_error = yaw;
    if (angle_error >= -ERROR_CAR_ANGLE) {
        speed_output_1 -= correction_factor * (angle_error+ERROR_CAR_ANGLE);
        speed_output_2 += correction_factor * (angle_error+4);
    }
    if (angle_error < -ERROR_CAR_ANGLE) {
        speed_output_1 += correction_factor * (angle_error+ERROR_CAR_ANGLE);
        speed_output_2 -= correction_factor * (angle_error+ERROR_CAR_ANGLE);
    }

//    sprintf((char *)display_buf,"%d  ",current_speed_1);
//    OLED_ShowString(3,2,display_buf);
//    sprintf((char *)display_buf,"%d  ",current_speed_2);
//    OLED_ShowString(4,2,display_buf);
    self_set_speed(speed_output_1,speed_output_2);
    if (abs(TARGET_DISTANCE*3750 - current_position_1) < 50 || abs(TARGET_DISTANCE*3600 - current_position_2) < 50) {
        Stop_PWM();
        speed_output_1=0;
        speed_output_2=0;
    }
    MPU6050();
}