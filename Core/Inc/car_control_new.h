//
// Created by 24319 on 2025/3/25.
//


#ifndef PID_CAR_CAR_CONTROL_NEW_H
#define PID_CAR_CAR_CONTROL_NEW_H
void set_right_speed(float Speed);
void set_left_speed(float Speed);
//----------------------------------------------------------------
void self_set_speed(float right,float left);
void Go_Motor(void);
void Stop_Motor(void);
void Backward_Motor(void);
void Turn_Left_Slower(void);
void Turn_Right_Slower(void);
void Turn_Left_Motor(void);
void Turn_Right_Motor(void);
void Turn_Around_Left_Motor(void);
void Turn_Around_Right_Motor(void);
//——————————————————————————————————————————————————————————————---
void Start_PWM(void);
void Stop_PWM(void);
//---------------------------------------------------------------

#endif //PID_CAR_CAR_CONTROL_NEW_H
