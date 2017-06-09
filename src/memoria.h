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
//com os modulos do RISC16
struct mem : public sc_module, public mem_if {

	int16_t read(const unsigned short adress);

	int16_t lw(const unsigned short address, int16_t constante);

	void sw(const unsigned short address, int16_t constante, int16_t dado);

	void write_mem(const unsigned short address, int16_t data);

	void dump_mem(int inicio, int fim, char formato);


	SC_CTOR(mem){
		mem_ptr = new int16_t[MAX_MEM];
	}

private:
		int16_t *mem_ptr;
};




#endif /* MEMORIA_H_ */
