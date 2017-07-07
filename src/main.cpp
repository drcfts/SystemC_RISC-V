
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#include "stdarg.h"
#include "breg.h"
#include "memoria.h"

std::string hex_para_decimal(uint32_t hex12);
uint32_t gerainst(int n, ...);


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

	// zera pc;
	Breg.write(31, 0);
	e_f.write(dado_entrada);

	sc_start();

	return 0;
}

// 					ORDEM
// AUIPC => IMEDIATO, depois rd (registrador destino)
// LUI => IMEDIATO, depois rd (registrador destino)
// TIPO R => FUNCT7,rs2,rs1,FUNCT3,rd.
// TIPO I => imm, rs1, funct3, rd
// TIPO S => imm(11-5), rs2, rs1, funct3, imm(4-0)
//TIPO JALR => imm, rs1,func3,rd
// TIPO I SHAMT => FUNCT7,shamt,rs1,FUNCT3,rd.
// JAL => imm(20), imm(10-1), imm(11), imm(19-12), rd
// Tipo B => imediato, rs2,rs1,funct3
uint32_t gerainst(int n, ...){
	uint32_t inst = 0;
	int imediato_JAL, imediato_S, imediato_B;
	va_list ap;

	va_start(ap, n);

	switch (n) {
	case TIPO_LUI :
		inst = (va_arg(ap, int) & 0xFFFFF) << 5;
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 6;
		inst = inst | n;
		std::cout <<std::dec<< "inst ->" << inst <<std::endl;
		std::cout <<std::hex<< "n ->" << n <<std::endl;
		break;
	case TIPO_AUIPC :
		inst = (va_arg(ap, int) & 0xFFFFF) << 5;
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 6;
		inst = inst | n;
		std::cout <<std::hex<< "inst ->" << inst <<std::endl;
		std::cout <<std::hex<< "n ->" << n <<std::endl;
		break;
		//Tipo I possui a mesma decodificacao
	case TIPO_I_REST0   :
		// desce pra jalr que é o mesmo
	case TIPO_JALR:
		inst = ((va_arg(ap, int) & 0xFFF) ) << 5;
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 3;
		inst = ((va_arg(ap, int) & 0x7) | inst) << 5;
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 7;
		inst |= n;

		std::cout <<std::dec<< "inst ->" << inst <<std::endl;
		std::cout <<std::hex<< "n ->" << n <<std::endl;
		break;
	case TIPO_I2_SHAMT :
		// colocando f7
		inst = (va_arg(ap, int) & 0x7F) << 5;
		// colocando SHAMT
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 5;
		// colocando rs1
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 3;
		// colocando funct3
		inst = ((va_arg(ap, int) & 0x7) | inst) << 5;
		// colocando rd
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 7;
		// por fim opcode
		inst = inst | n;


		std::cout <<std::dec<< "inst ->" << inst <<std::endl;
		std::cout <<std::hex<< "n ->" << n <<std::endl;
		break;
		// TIPO S => imm(11-5), rs2, rs1, funct3, imm(4-0)
	case TIPO_S :
		imediato_S = (va_arg(ap, int) );
		inst = ((imediato_S & 0xFE0) ) << 5;
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 5;
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 3;
		inst = ((va_arg(ap, int) & 0x07) | inst) << 5;
		inst = ((imediato_S & 0x1F) | inst) << 7;
		inst |= n;
		std::cout <<std::dec<< "inst ->" << inst <<std::endl;
		std::cout <<std::hex<< "n ->" << n <<std::endl;
		break;
	case TIPO_B :
		imediato_B = (va_arg(ap, int));
		// primeiro bit
		inst = (((imediato_B >> 11) & 0x1) ) << 6;
		// mais um pedaco imm[10:5]
		inst = (((imediato_B & 0x3F0) )) << 5;
		//rs2
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 5;
		//rs1
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 3;
		//funct3
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 4;
		//// mais um pedaco imm[4:1]
		inst = ((imediato_B & 0x01E )) << 1;
		// mais um bit
		inst = (((imediato_B >> 10) & 0x1) ) << 7;
		inst |= n;


		break;
    // JAL => imm(20), imm(10-1), imm(11), imm(19-12), rd
	case TIPO_JAL :
		imediato_JAL = (va_arg(ap, int) );
		inst = ((imediato_JAL & 0x100000) ) << 10;
		inst = (((imediato_JAL>>1)& 0x3FF) | inst) << 1;
		inst = ((imediato_JAL & 0x800) | inst) << 8;
		inst = ((imediato_JAL & 0xFF000) | inst) << 5;
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 7;
		inst |= n;

		std::cout <<std::dec<< "inst ->" << inst <<std::endl;
		std::cout <<std::hex<< "n ->" << n <<std::endl;
	break;
	case TIPO_R:
		// MODIFICA O F3 e F7
		// colocando f7
		inst = (va_arg(ap, int) & 0x7F) << 5;
		std::cout << "inst"<< hex_para_decimal(inst) <<std::endl;
		std::cout << std::hex << "Inst ->"<< inst <<std::endl;
		// colocando rs2
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 5;

		// colocando rs1
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 3;
		// colocando funct3
		inst = ((va_arg(ap, int) & 0x7) | inst) << 5;
		// colocando rd
		inst = ((va_arg(ap, int) & 0x1F) | inst) << 7;
		// por fim opcode
		inst = inst | n;
		std::cout << "inst"<< hex_para_decimal(inst) <<std::endl;
		std::cout << std::hex << "Inst ->"<< inst <<std::endl;
		break;
	default:
		break;
	}
	return inst;
}


std::string hex_para_decimal(uint32_t hex12){
	std::string sRet="";
	std::string x;
	std::stringstream ss;
	ss <<std::hex<<hex12;
	x= ss.str();


	for(int i=0;i<x.length();++i){
		switch(x[i]){
		case '0':sRet.append("0000");break;
		case '1':sRet.append("0001");break;
		case '2':sRet.append("0010");break;
		case '3':sRet.append("0011");break;
		case '4':sRet.append("0100");break;
		case '5':sRet.append("0101");break;
		case '6':sRet.append("0110");break;
		case '7':sRet.append("0111");break;
		case '8':sRet.append("1000");break;
		case '9':sRet.append("1001");break;
		case 'A':sRet.append("1010");break;
		case 'a':sRet.append("1010");break;
		case 'B':sRet.append("1011");break;
		case 'b':sRet.append("1011");break;
		case 'C':sRet.append("1100");break;
		case 'c':sRet.append("1100");break;
		case 'D':sRet.append("1101");break;
		case 'd':sRet.append("1101");break;
		case 'E':sRet.append("1110");break;
		case 'e':sRet.append("1110");break;
		case 'F':sRet.append("1111");break;
		case 'f':sRet.append("1111");break;

		}

	}
	return sRet;
}

