/*
 * memoria.cpp
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#include "memoria.h"

int32_t mem::read(const unsigned address){
	if ((address) > MAX_MEM ){
		cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
		sc_stop();
	}
	return mem_ptr[address];
}

int32_t mem::lw(const unsigned address, int32_t constante){
	int32_t _t = address + constante;

	if ((_t) > MAX_MEM ){
			cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
			sc_stop();
		}

	return mem_ptr[(_t)];
}

void mem::sw(const unsigned address, int32_t constante, int32_t dado){
	int32_t _t = address + constante;

	if ((_t) > MAX_MEM ){
			cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
			sc_stop();
		}

	mem_ptr[(_t)] = dado;
}

void mem::write_mem(const unsigned address, int32_t data){
	mem_ptr[address] = data;
}

void mem::dump_mem(int inicio, int fim, char formato){
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

