//
// Created by 24319 on 2025/3/25.
//

#include "car_control_new.h"
//
// Created by 24319 on 2025/3/8.
//

#include "car_control_new.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#define MIDDLE_SPEED 400
#define HIGH_SPEED 700
#define LOW_SPEED 300


//——————————————————————————————————————————————————————————————————————————————
int wadawdawd;
void set_right_speed(float Speed)//设置方向
{
    if (Speed >= 0) {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Speed);
    } else{
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,-Speed);
    }
}
void set_left_speed(float Speed)//设置方向
{
    if (Speed >= 0) {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,Speed);
    } else{
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,-Speed);
    }
}
//——————————————————————————————————————————————————————————————————————————————————————
void self_set_speed(float right,float left)
{
    set_right_speed(right);
    set_left_speed(left);
}
void Go_Motor(void)
{
    set_right_speed(200);
    set_left_speed(200);
}
void Stop_Motor(void)
{
    set_right_speed(0);
    set_left_speed(0);
}
void Backward_Motor(void)
{
    set_right_speed(-MIDDLE_SPEED);
    set_left_speed(-MIDDLE_SPEED);
}
void Turn_Left_Slower(void)
{
    set_right_speed(MIDDLE_SPEED);
    set_left_speed(LOW_SPEED);
}
void Turn_Right_Slower(void)
{
    set_right_speed(LOW_SPEED);
    set_left_speed(MIDDLE_SPEED);
}
void Turn_Left_Motor(void)
{
    set_right_speed(200);
    set_left_speed(100);
}
void Turn_Right_Motor(void)
{
    set_right_speed(0);
    set_left_speed(MIDDLE_SPEED);
}
void Turn_Around_Left_Motor(void)
{
    set_right_speed(MIDDLE_SPEED);
    set_left_speed(-MIDDLE_SPEED);
}
void Turn_Around_Right_Motor(void)
{
    set_right_speed(-MIDDLE_SPEED);
    set_left_speed(MIDDLE_SPEED);
}
//————————————————————————————————————————————————————————————————————————————————————-
void Start_PWM(void)
{
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
}
void Stop_PWM(void)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
}
