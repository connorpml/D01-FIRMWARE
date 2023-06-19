/*
 * tick.h
 *
 * Created: 8/22/2016 2:03:33 PM
 *  Author: Connor
 */ 


#ifndef SYSTICK_H_
#define SYSTICK_H_


void tick_init(void (*callback)(void));


#endif /* SYSTICK_H_ */