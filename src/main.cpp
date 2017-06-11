/*
 * main.cpp
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "stdarg.h"
#include "breg.h"
#include "memoria.h"

short gerainst(int n, ...);

int sc_main(int argc, char* argv[]){
	fetch Fetch("Fetch");
	decode Decode("Decode");
	execute Execute("Execute");

	mem Memoria("Memoria");
	breg Breg("Breg");

	sc_fifo < contexto* > e_f( 1);
	sc_fifo < contexto* > f_d( 1);
	sc_fifo < contexto* > d_e( 1);


	Fetch.p_mem(Memoria);
	Fetch.p_breg(Breg);
	Fetch.execute_fetch(e_f);
	Fetch.fetch_decode(f_d);

	Execute.p_breg(Breg);
	Execute.p_mem(Memoria);
	Execute.decode_execute(d_e);
	Execute.execute_fetch(e_f);

	Decode.p_breg(Breg);
	Decode.decode_execute(d_e);
	Decode.fetch_decode(f_d);

	contexto *dado_entrada = new contexto();
	//Inicializacao
	//Zera PC
	Breg.write(31, 0);
	e_f.write(dado_entrada);

//		/* addi $1, 0 */
//		Memoria.write_mem(0, gerainst(TIPO_J, i_ADDi, 1, 0 ));
//		/* addi $1, 8 */
//		Memoria.write_mem(1, gerainst(TIPO_J, i_ADDi, 1, 8 ));
//		/* addi $2, -12 */
//		Memoria.write_mem(2, gerainst(TIPO_J, i_ADDi, 2, -12 ));
//		/* add $3, $2, $1 */
//		Memoria.write_mem(3, gerainst(TIPO_R, i_ADD, 1, 2, 3 ));
//		/* sub $4, $2, $1 */
//		Memoria.write_mem(4, gerainst(TIPO_R, i_SUB, 2, 1, 4 ));
//		/* add $5, $0, $1 */
//		Memoria.write_mem(5, gerainst(TIPO_R, i_ADD, 1, 0, 5 ));
//		/* shift $5, 2*/
//		Memoria.write_mem(6, gerainst(TIPO_J, i_SHIFT, 5, 2));
//		/* add $6, $0, $1*/
//		Memoria.write_mem(7, gerainst(TIPO_R, i_ADD, 1, 0, 6 ));
//		 /*shift $6, -4*/
//		Memoria.write_mem(8, gerainst(TIPO_J, i_SHIFT, 6, -4));
//		 /*lui $7, FF*/
//		Memoria.write_mem(9, gerainst(TIPO_J, i_LUI, 7, 0xFF));
//		/* and $8, $7, $4*/
//		Memoria.write_mem(10, gerainst(TIPO_R, i_AND, 4, 7, 8));
//		 /*add $9, $0, $8*/
//		Memoria.write_mem(11, gerainst(TIPO_R, i_ADD, 8, 0, 9 ));
//		 /*not $9*/
//		Memoria.write_mem(12, gerainst(TIPO_R, i_NOT, 9, 0, 0 ));
//		 /*xor $10, $4, $7*/
//		Memoria.write_mem(13, gerainst(TIPO_R, i_XOR, 4, 7, 10 ));
//		 /*slt $11, $5, $1*/
//		Memoria.write_mem(14, gerainst(TIPO_R, i_SLT, 5, 1, 11 ));
//		 /*sw $5, $0, $6*/
//		Memoria.write_mem(15, gerainst(TIPO_R, i_SW, 6, 0, 5 ));
//		 /*lw $12, $0, $0*/
//		Memoria.write_mem(16, gerainst(TIPO_R, i_LW, 6, 0, 12 ));
//		 /*jal 20*/
//		Memoria.write_mem(17, gerainst(TIPO_J, i_JAL, 0, 20 ));
//		/* beq $0, $1 -> 5*/
//		Memoria.write_mem(18, gerainst(TIPO_R, i_BEQ, 0, 1, 5 ));
//		 /*bne $0, $1 -> 7*/
//		Memoria.write_mem(19, gerainst(TIPO_R, i_BNE, 0, 1, 7 ));
//		 /*jr 15*/
//		Memoria.write_mem(20, gerainst(TIPO_J, i_J, 15, 0 ));
//
	cout << "Iniciando simulacao..." << endl;

	sc_start();

	Memoria.dump_mem(0, 50, 'h');

	Breg.dump_breg();

	return 0;
}

short gerainst(int n, ...){
	short inst = 0;

	va_list ap;

	va_start(ap, n);

	switch (n) {
//		case TIPO_R:
//			inst |= (va_arg(ap, int ) & 0xF) << 12;
//			inst |= (va_arg(ap, int ) & 0xF) << 8;
//			inst |= (va_arg(ap, int ) & 0xF) << 4;
//			inst |= (va_arg(ap, int ) & 0xF);
//			break;
//		case TIPO_J:
//			inst |= (va_arg(ap, int ) & 0xF) << 12;
//			inst |= (va_arg(ap, int ) & 0xF) << 8;
//			inst |= (va_arg(ap, int ) & 0xFF);
			break;
		default:
			break;
	}
	return inst;
}
