#ifndef _MAIN_H
#define _MAIN_H

#include "stdio.h"
#include "string.h"
#include "sched.h"
#include "pthread.h"
#include <limits.h>
#include <sys/mman.h>
#include "ecrt.h"

#include "ethercat_motor_node/config.h"

extern "C" {
#include "ethercat_motor_node/motor_control.h"
}


#define KP_MAX 500.0f
#define KP_MIN 0.0f
#define KD_MIN 0.0f
#define KD_MAX 50.0f
#define POS_MIN (-12.5f)
#define POS_MAX 12.5f
#define SPD_MIN (-18.0f)
#define SPD_MAX 18.0f
#define T_MIN (-30.0f)
#define T_MAX 30.0f
#define I_MIN (-30.0f)
#define I_MAX 30.0f
#define comm_ack 0x00

static ec_master_t* master = nullptr;
static ec_domain_t* domain = nullptr;
static ec_master_state_t master_state = {};
static ec_domain_state_t domain_state = {};
static uint8_t* domain_pd = nullptr;


typedef struct
{
    uint32_t ID;
    uint32_t RTR;
    uint32_t DLC;
    uint32_t DATA[8]; // DATA0~DATA7
} MotorDataOffset;

typedef struct
{
    uint32_t OUT_NOTOR_NUM;
    uint32_t OUT_CAN_IDE;
    MotorDataOffset OUT_MOTOR[6]; // OUT_MOTOR1 ~ OUT_MOTOR6
    MotorDataOffset IN_MOTOR[6]; // IN_MOTOR1 ~ IN_MOTOR6
    uint32_t IN_MOTOR_NUM;
    uint32_t IN_MOTOR_IDE;
} PDO_Struct;


struct period_info
{
    timespec next_period;
    long period_ns;
};

#endif
