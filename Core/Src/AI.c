//
// Created by 24319 on 2025/3/8.
//

#include <stdio.h>
#include "AI.h"
#include "tim.h"
#include "OLED.h"
#include"car_control_new.h"
#include"mpu6050.h"
#include "inv_mpu.h"
#define ki_max_output 300
#define output_max 1000
float roll,pitch,yaw;
float output,Ki_accumulate,last_error;
float error;
float kp,ki,kd;
float pid_calculate(PIDController *pid,float Real_num)//计算pid的值
{
    kp=pid->kp;ki=pid->ki;kd=pid->kd;
    last_error=error;
    error=pid->Target-Real_num;
    Ki_accumulate+=error;
    if(Ki_accumulate>=ki_max_output)
    {
        Ki_accumulate=ki_max_output;
    }
    if(Ki_accumulate<=-ki_max_output)
    {
        Ki_accumulate=-ki_max_output;
    }
    output=kp*error+ki*Ki_accumulate+kd*(error-last_error);
    if(output>=output_max)output=output_max;
    if(output<=-output_max)output=-output_max;
    return output;//-1000-1000
}



void PID_Init(PIDController *pid, float kp, float ki, float kd, float Target) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->Target = Target;
    pid->ki_output = 0;
    pid->last_error = 0;
}
int32_t Read_Speed(TIM_HandleTypeDef *htim)
{
    int temp;
    temp=__HAL_TIM_GetCounter(htim);
   // __HAL_TIM_SetCounter(htim,0);
    return temp;
}
uint32_t sys_tick;
int Encoder_Left,Encoder_Right;
uint8_t display_buf[20];
void read(void)
{
    if(uwTick-sys_tick<10)
        return;
    sys_tick=uwTick;
    Encoder_Left=Read_Speed(&htim2);
    Encoder_Right=-Read_Speed(&htim3);
    sprintf((char *)display_buf,"%d   ",Encoder_Left);
    OLED_ShowString(2,2,display_buf);
    sprintf((char *)display_buf,"%d   ",Encoder_Right);
    OLED_ShowString(4,2,display_buf);
    if(Encoder_Left>=60000)Stop_Motor();
}
void MPU6050(void)
{
    mpu_dmp_get_data(&pitch,&roll,&yaw);
   sprintf((char *)display_buf,"yaw:%.2f  ",yaw);
    OLED_ShowString(3,2,display_buf);

}
