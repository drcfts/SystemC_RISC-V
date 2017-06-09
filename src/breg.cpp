/*
 * breg.cpp
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#include "breg.h"

int16_t breg::read(const unsigned short address){
	if ((address) > 15 ){
		cout << "Endereco fora do intervalo de tamanho do Banco de Registradores!" << endl;
		exit(0);
	}
	return breg_ptr[address];
}

void breg::write(const unsigned short address, int16_t dado){
	if ((address) > 15 ){
			cout << "Endereco fora do intervalo de tamanho do Banco de Registradores!" << endl;
			exit(0);
		}

	breg_ptr[address] = dado;
}

void breg::dump_breg() {
		for (int i=0; i<16; i++) {
      		printf("BREG[%2d] = \t%4d \t\t\t%4x\n", i, breg_ptr[i], breg_ptr[i]);
	}
}

