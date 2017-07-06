/*
 * breg.cpp
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#include "breg.h"

int32_t breg::read(const unsigned address){
	if ((address) > 31 ){
		cout << "Endereco fora do intervalo de tamanho do Banco de Registradores!" << endl;
		exit(0);
	}
	if (breg_ptr[0] != 0 ){
		breg_ptr[0] = 0;
	}

	return breg_ptr[address];
}

void breg::write(const unsigned address, int32_t dado){

	if ((address) == 0 ){
			cout << "Impossivel escrever no registrador Zero - Valor sempre será Zero!" << endl;
			exit(0);
		}

	if ((address) > 31 ){
			cout << "Endereco fora do intervalo de tamanho do Banco de Registradores!" << endl;
			exit(0);
		}

	breg_ptr[address] = dado;
}

void breg::dump_breg() {
		for (int i=0; i<32; i++) {
      		printf("BREG[%2d] = \t%4d \t\t\t%8x\n", i, breg_ptr[i], breg_ptr[i]);
	}
}

