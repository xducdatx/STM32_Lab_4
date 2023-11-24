/*
 * cooperative_scheduler.h
 *
 *  Created on: Nov 24, 2023
 *      Author: datph
 */

#ifndef INC_COOPERATIVE_SCHEDULER_H_
#define INC_COOPERATIVE_SCHEDULER_H_

#include "main.h"

#define SCH_MAX_TASKS	40
#define	NO_TASK_ID 		0

void SCH_Init(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t taskID);
#endif /* INC_COOPERATIVE_SCHEDULER_H_ */
