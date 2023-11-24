/*
 * cooperative_scheduler.c
 *
 *  Created on: Nov 24, 2023
 *      Author: datph
 */

#ifndef SRC_COOPERATIVE_SCHEDULER_C_
#define SRC_COOPERATIVE_SCHEDULER_C_
#include "cooperative_scheduler.h"



typedef struct
{
	void ( *pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

sTask SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init()
{
	unsigned char i;
	for (i = 0; i < SCH_MAX_TASKS; i++)
	{
		SCH_Delete_Task(i);
	}
}

void SCH_Update(void)
{
	unsigned char Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++)
	{
		if (SCH_tasks_G[Index].pTask)
		{
			if (SCH_tasks_G[Index].Delay == 0)
			{
				SCH_tasks_G[Index].RunMe += 1;
				if (SCH_tasks_G[Index].Period)
				{
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			}
			else
			{
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}

uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
	unsigned char Index = 0;
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
	{
		Index++;
	}
	 SCH_tasks_G[Index].pTask = pFunction;
	 SCH_tasks_G[Index].Delay = DELAY;
	 SCH_tasks_G[Index].Period = PERIOD;
	 SCH_tasks_G[Index].RunMe = 0;
	 return Index;
}

void SCH_Dispatch_Tasks(void)
{
	unsigned char Index;
	for (Index = 0; Index < SCH_MAX_TASKS; Index++)
	{
		if (SCH_tasks_G[Index].RunMe > 0)
		{
			(*SCH_tasks_G[Index].pTask)();
			SCH_tasks_G[Index].RunMe -= 1;
			if (SCH_tasks_G[Index].Period == 0)
			{
				SCH_Delete_Task(Index);
			}
		}
	}
}

uint8_t SCH_Delete_Task(uint32_t taskID)
{
	uint8_t Return_code;
	if (SCH_tasks_G[taskID].pTask == 0)
	{
		Return_code = 1;
	}
	else
	{
		Return_code = 0;
	}
	SCH_tasks_G[taskID].pTask = 0;
	SCH_tasks_G[taskID].Delay = 0;
	SCH_tasks_G[taskID].Period = 0;
	SCH_tasks_G[taskID].RunMe = 0;
	return Return_code;
}
#endif /* SRC_COOPERATIVE_SCHEDULER_C_ */
