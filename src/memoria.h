/*
 * memoria.h
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#ifndef MEMORIA_H_
#define MEMORIA_H_

#include <systemc.h>
#include "shared.h"

using namespace std;

//Memoria que se conectar a NoC
struct mem : public sc_module{

	// Conexao com a NoC
	sc_fifo_out< uint32_t > memOut;
	sc_fifo_in< uint32_t > memIn;

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

	void interpreta_Noc();

	SC_CTOR(mem){
		mem_ptr = new int32_t[MAX_MEM];
		SC_THREAD(interpreta_Noc);

	}

private:
	int32_t *mem_ptr;
};

/****************************
 * ENDEREÇO VAI TER 32 BITS *
 ****************************
 * 	32 bits -------------------
 *	2 bits-- de dados(coluna) -
 *  20 bits-- tag		      -
 *  10 bits indica a linha    -
 *  ---------------------------
 *  O TAMANHO DA CACHE VAI SER 1024 = 2¹⁰
 * -------------------------
 * Matriz da memória de cache
 * bit de validade - 0 ou 1  -> indicando se foi preenchida ou nao
 * Tag -> uma parte do endereço para verificar se é aquele endereço mesmo
 * Dados -> é onde vai conter os dados como a memória é de 4K, vai ter um vetor
 * 4dados
 * **************************************************************
 *
 * typedef struct{
	bool validade;
	uint32_t tag_cache;
	int dados[4];
	uint32_t palavra_coluna;
	uint32_t linha_endereco_cache;

	}mem_cache;
*
*
*decode_mem(endereco){
 	 palavra_coluna = (endereco) & 0x3;
	 tag_cache = (endereco >> 12) & 0xFFFFF;
	 linha_endereco_cache = (endereco >> 2) & 0x3FF;
 }
*/



#endif /* MEMORIA_H_ */
