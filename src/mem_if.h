/*
 * mem_if.h
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#ifndef MEM_IF_H_
#define MEM_IF_H_

#include "systemc.h"
#include <stdint.h>

struct mem_if : public sc_interface{

	virtual int16_t
	read(const unsigned short adress) = 0;

	virtual int16_t
	lw(const unsigned short address, int16_t constante) = 0;

	virtual void
	sw(const unsigned short address, int16_t constante, int16_t dado) = 0;

	virtual void
	write_mem(const unsigned short address, int16_t data) = 0;

	virtual void
	dump_mem(int inicio, int fim, char formato) = 0;

};



#endif /* MEM_IF_H_ */
