/*
 * my_interrupt.h
 *
 *  Created on: 2025. 5. 5.
 *      Author: seungH
 */

#ifndef SRC_MY_INTERRUPT_H_
#define SRC_MY_INTERRUPT_H_

#define INTC_DEVICE_ID		XPAR_SCUGIC_0_DEVICE_ID
#define INTC_DEVICE_INT_ID	31

void interrupt_init(void);
int GicConfigure(u16 DeviceId);
void ServiceRoutine(void *CallbackRef);

#endif /* SRC_MY_INTERRUPT_H_ */
