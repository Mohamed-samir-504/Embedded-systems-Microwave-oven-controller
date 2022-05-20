#include "FSMmanager.h"
#include "Idle.h"
#include "Popcorn.h"
#include "BeefChicken.h"
#include "FreeTimer.h"
#include <stdlib.h>
#define NOfStates 7

f_pointer_void_void* loop;

States myStates;

void FSM_int()
{
    loop = (f_pointer_void_void*)calloc(NOfStates, sizeof(f_pointer_void_void));
    Idle_Init();
    Popcorn_Init();
    BeefChicken_Init();
    FreeTimer_Init();
    Pause_Init();
		Timer_Init();
    Locked_Init();
};

StatesEnum CurrentState;
