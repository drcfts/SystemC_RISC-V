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

	virtual int32_t
	read(const uint32_t  adress) = 0;

	virtual int32_t
	lw(const unsigned  address, int32_t constante) = 0;

	virtual int32_t
	lh(const unsigned  address, int32_t constante) = 0;

	virtual int32_t
	lbu(const unsigned  address, int32_t constante) = 0;

	virtual int32_t
	lhu(const unsigned  address, int32_t constante) = 0;

	virtual int32_t
	lb(const unsigned  address, int32_t constante) = 0;

	virtual void
	sw(const unsigned  address, int32_t constante, int32_t dado) = 0;

	virtual void
	sh(const unsigned  address, int32_t constante, int32_t dado) = 0;

	virtual void
	sb(const unsigned  address, int32_t constante, int32_t dado) = 0;

	virtual void
	write_mem(const unsigned address, uint32_t data) = 0;

	virtual void
	dump_mem(int inicio, int fim, char formato) = 0;

};



#endif /* MEM_IF_H_ */
