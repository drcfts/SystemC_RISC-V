/*
 * memoria_instrucoes.cpp
 *
 *  Created on: 8 de jul de 2017
 *      Author: drcfts
 */

#include "memoria_instrucoes.h"

int32_t mem_inst::read(const uint32_t address){
	if ((address) > MAX_MEM ){
		cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
		sc_stop();
	}
	return mem_ptr[address];
}

int32_t mem_inst::lw(const unsigned address, int32_t constante){
	return 0;
}

int32_t mem_inst::lh(const unsigned address, int32_t constante){
	return 0;
}

int32_t mem_inst::lb(const unsigned address, int32_t constante){
	return 0;
}

int32_t mem_inst::lhu(const unsigned address, int32_t constante){
	return 0;
}

int32_t mem_inst::lbu(const unsigned address, int32_t constante){
	return 0;
}

void mem_inst::sw(const unsigned address, int32_t constante, int32_t dado){
}

void mem_inst::sh(const unsigned address, int32_t constante, int32_t dado)
{

}

void mem_inst::sb(const unsigned address, int32_t constante, int32_t dado){

}

void mem_inst::write_mem(const unsigned address, uint32_t data){
	mem_ptr[address] = data;

}

void mem_inst::dump_mem(int inicio, int fim, char formato){
	switch (formato) {
		case 'h':
		case 'H':
			for (int32_t i = inicio; i <= fim; i+=4)
				printf("%d\t%8x\n", i, lw(i, 0));
			break;
		case 'd':
		case 'D':
			for (int32_t i = inicio; i <= fim; i+=4)
				printf("%d\t%8d\n", i, lw(i, 0));
			break;
		default:
			break;
	}
}




