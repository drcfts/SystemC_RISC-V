/*
 * memoria_instrucoes.cpp
 *
 *  Created on: 8 de jul de 2017
 *      Author: drcfts
 */

#include "memoria_instrucoes.h"

int32_t mem_inst::read(const unsigned address){
	if ((address) > MAX_MEM ){
		cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
		sc_stop();
	}
	return mem_ptr[address];
}


void mem_inst::write_mem(const unsigned address, int32_t data){
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


