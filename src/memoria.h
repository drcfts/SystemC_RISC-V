/*
 * memoria.h
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <systemc.h>
#include "mem_if.h"
#include "shared.h"

using namespace std;

//Implementacao da interface de memoria, para se conectar
//com os modulos do RISC-V
struct mem : public sc_module, public mem_if {

	int32_t read(const unsigned adress);

	int32_t lw(const unsigned address, int32_t constante);

	int32_t lh(const unsigned address, int32_t constante);

	int32_t lhu(const unsigned address, int32_t constante);

	int32_t lb(const unsigned address, int32_t constante);

	int32_t lbu(const unsigned address, int32_t constante);

	void sw(const unsigned address, int32_t constante, int32_t dado);

	void sh(const unsigned address, int32_t constante, int32_t dado);

	void sb(const unsigned address, int32_t constante, int32_t dado);

	void write_mem(const unsigned address, int32_t data);

	void dump_mem(int inicio, int fim, char formato);


	SC_CTOR(mem){
		mem_ptr = new int32_t[MAX_MEM];
	}

private:
	int32_t *mem_ptr;
};




#endif /* MEMORIA_H_ */
