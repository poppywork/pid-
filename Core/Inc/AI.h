//
// Created by 24319 on 2025/3/8.
//

#ifndef PID_CAR_AI_H
#define PID_CAR_AI_H

#include "tim.h"

typedef struct {
    float kp;
    float ki;
    float kd;
    float Target;
    float ki_output;
    float last_error;
} PIDController;

float pid_calculate(PIDController *pid,float Real_num);//计算pid的值
void PID_Init(PIDController *pid, float kp, float ki, float kd, float Target);
int32_t Read_Speed(TIM_HandleTypeDef *htim);
void read(void);
void MPU6050(void);
#endif //PID_CAR_AI_H
