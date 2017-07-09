/*
 *  shell_mips_if.h
 *  MIPS_sc_v1
 *
 *  Created by Ricardo Jacobi on 20/5/16.
 *  Copyright 2016 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef SHELL_MEM_RISC_IF_H
#define SHELL_MEM_RISC_IF_H

#include <stdint.h>
#include "systemc.h"

struct shell_mem_risc_if : public sc_interface {


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




};

#endif
