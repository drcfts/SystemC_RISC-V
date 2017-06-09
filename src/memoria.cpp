/*
 * memoria.cpp
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#include "memoria.h"

int16_t mem::read(const unsigned short address){
	if ((address) > MAX_MEM ){
		cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
		sc_stop();
	}
	return mem_ptr[address];
}

int16_t mem::lw(const unsigned short address, int16_t constante){
	int16_t _t = address + constante;

	if ((_t) > MAX_MEM ){
			cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
			sc_stop();
		}

	return mem_ptr[(_t)];
}

void mem::sw(const unsigned short address, int16_t constante, int16_t dado){
	int16_t _t = address + constante;

	if ((_t) > MAX_MEM ){
			cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
			sc_stop();
		}

	mem_ptr[(_t)] = dado;
}

void mem::write_mem(const unsigned short address, int16_t data){
	mem_ptr[address] = data;
}

void mem::dump_mem(int inicio, int fim, char formato){
	switch (formato) {
		case 'h':
		case 'H':
			for (int16_t i = inicio; i <= fim; i+=2)
				printf("%d\t%4x\n", i, lw(i, 0));
			break;
		case 'd':
		case 'D':
			for (int16_t i = inicio; i <= fim; i+=2)
				printf("%d\t%4d\n", i, lw(i, 0));
			break;
		default:
			break;
	}
}

