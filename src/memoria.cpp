/*
 * memoria.cpp
 *
 *  Created on: 14 de mai de 2017
 *      Author: drcfts
 */

#include "memoria.h"

void mem::interpreta_Noc(){
	uint32_t address, dado;
	int32_t dado_retorno, flag_salvou = 0;
	uint32_t cmd;
	int erro = 0;

	//Uma thread para tomar as decisoes da memoria
	//Recebe um vetor de payload da shell (comando,endereco)
	for( ; ;){
		cmd = memIn.read();
		switch(cmd){
		//Se for operacoes Load, recebe address (address + cte)
		case _LW:
			address = memIn.read();
			dado_retorno = lw(address, 0);
			break;
		case _LB:
			address = memIn.read();
			dado_retorno = lb(address, 0);
			break;
		case _LH:
			address = memIn.read();
			dado_retorno = lh(address, 0);
			break;
		case _LBU:
			address = memIn.read();
			dado_retorno = lbu(address, 0);
			break;
		case _LHU:
			address = memIn.read();
			dado_retorno = lhu(address, 0);
			break;
	    //Saves recebem, alem disso, os dados
		case _SW:
			address = memIn.read();
			dado = memIn.read();;
			sw(address, 0, dado);
			flag_salvou = 1;
			break;
		case _SB:
			address = memIn.read();
			dado = memIn.read();
			sb(address, 0,dado);
			flag_salvou = 1;
			break;
		case _SH:
			address = memIn.read();
			dado = memIn.read();
			sh(address, 0,dado);
			flag_salvou = 1;
			break;
		default:
			erro = 1;
			break;
		} //switch
		if(erro){
			//Vetor manda que houve erro apenas (para a Shell)
			memOut.write(0);
			erro = 0;
		}
		else{
			//Caso n haja erro
			memOut.write(1);
			//Se for load, deve mandar dado tambem
			if(!flag_salvou){
				memOut.write(dado_retorno);
				flag_salvou = 0;
			}
		}
	} //for

}
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

int32_t mem::lh(const unsigned address, int32_t constante){
	int32_t _t = address + constante;
	int16_t resto;
	int32_t MSB[2];
	int32_t MSB_anterior;

	if ((_t) > MAX_MEM ){
		cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
		sc_stop();
	}

	if (constante % 2 != 0 ){
		cout << "Offset nao eh multiplo de 2!" << endl;
		sc_stop();
	}

	resto = constante % 4;
	MSB[0] = mem_ptr[(_t)] & 0x0000f000;
	MSB[1] = mem_ptr[(_t)] & 0xf0000000;

	MSB_anterior = mem_ptr[(_t)-1] & 0xf0000000;

	if(!resto){
		//Se for negativo
		if(MSB[0]>= 0x00008000){
			return (mem_ptr[(_t)] | 0xffff0000);
		}
		//Se for positivo
		return (mem_ptr[(_t)] & 0x0000ffff);
	}


	if(resto == 2){
		//Se for negativo
		if(MSB[1]>= (int32_t)0x80000000){
			return ((mem_ptr[(_t)]>>16) | 0xffff0000);
		}
		//Se for positivo
		return (mem_ptr[(_t)] & 0xffff0000)>>16;
	}

	if(resto == -2){
		//Se for negativo
		if(MSB_anterior >= (int32_t)0x80000000){
			return ((mem_ptr[(_t)-1]>>16)| 0xffff0000);
		}
		//Se for positivo
		return (mem_ptr[(_t)-1] & 0xffff0000)>>16;
		}

}

int32_t mem::lb(const unsigned address, int32_t constante){
	int32_t _t = address + constante;
	int16_t resto;
	int32_t anterior;
	int32_t MSB[4];
	int32_t MSB_anterior[3];

	if ((_t) > MAX_MEM ){
			cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
			sc_stop();
		}

	resto = constante % 4;

	MSB[0] = mem_ptr[_t] & 0x000000f0;
	MSB[1] = mem_ptr[_t] & 0x0000f000;
	MSB[2] = mem_ptr[_t] & 0x00f00000;
	MSB[3] = mem_ptr[_t] & 0xf0000000;

	anterior = _t - 1;

	MSB_anterior[0] = mem_ptr[anterior] & 0xf0000000;
	MSB_anterior[1] = mem_ptr[anterior] & 0x00f00000;
	MSB_anterior[2] = mem_ptr[anterior] & 0x0000f000;

    if(resto == 0){
        /* Se o byte for negativo */
        if(MSB[0] >= 0x00000080){
            return (mem_ptr[_t] | 0xffffff00);
        }
        /* Se o byte for positivo */
        return (mem_ptr[_t] & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 1 */
    if(resto == 1){
        /* Se o byte for negativo */
        if(MSB[1] >= 0x00008000){
            return ((mem_ptr[_t] >> 8) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem_ptr[_t] >> 8) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -1 */
    if(resto == -1){
        /* Se o byte for negativo */
        if(MSB_anterior[0] >= (int32_t)0x80000000){
            return ((mem_ptr[anterior] >> 24) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem_ptr[anterior] >> 24) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 2 */
    if(resto == 2){
        /* Se o byte for negativo */
        if(MSB[2] >= 0x00800000){
            return ((mem_ptr[_t] >> 16) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem_ptr[_t] >> 16) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -2 */
    if(resto == -2){
        /* Se o byte for negativo */
        if(MSB_anterior[1] >= 0x00800000){
            return ((mem_ptr[anterior] >> 16) | 0xffffff00);
        }
        /* Se o byte for positivo */
        return ((mem_ptr[anterior] >> 16) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for 3 */
    if(resto == 3){
        /* Se o byte for negativo */
        if(MSB[3] >= (int32_t)0x80000000){
            return ((mem_ptr[_t] >> 24) | 0xffffff00);
        }
        return ((mem_ptr[_t] >> 24) & 0x000000ff);
    }

    /* Se o numero de bytes deslocados dentro do endereco for -3 */
    if(resto == -3){
        /* Se o byte for negativo */
        if(MSB_anterior[2] >= 0x00008000){
            return ((mem_ptr[anterior] >> 8) | 0xffffff00);
        }
        return ((mem_ptr[anterior] >> 8) & 0x000000ff);
}

}

int32_t mem::lhu(const unsigned address, int32_t constante){
	int32_t _t = address + constante;
	int16_t resto;

	if ((_t) > MAX_MEM ){
		cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
		sc_stop();
	}

	if (constante % 2 != 0 ){
		cout << "Offset nao eh multiplo de 2!" << endl;
		sc_stop();
	}

	resto = constante % 4;

	if(!resto){
		return (mem_ptr[(_t)] & 0x0000ffff);
	}


	if(resto == 2){
		return (mem_ptr[(_t)] & 0xffff0000)>>16;
	}

	if(resto == -2){
			return (mem_ptr[(_t)] & 0xffff0000)>>16;
		}

}

int32_t mem::lbu(const unsigned address, int32_t constante){
	int32_t _t = address + constante;
	int16_t resto;

	if ((_t) > MAX_MEM ){
			cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
			sc_stop();
		}

	resto = constante % 4;

	if(!resto){
		return (mem_ptr[(_t)] & 0x000000ff);
	}

	if(resto == 1){
		return (mem_ptr[(_t)] & 0x0000ff00)>>8;
	}

	if(resto == -1){
		return (mem_ptr[(_t)-1] & 0xff0000)>>24;
	}

	if(resto == 2){
		return (mem_ptr[(_t)] & 0x00ff0000)>>16;
	}

	if(resto == -2){
			return (mem_ptr[(_t)] & 0x00ff0000)>>16;
		}

	if(resto == 3){
		return (mem_ptr[(_t)] & 0xff000000)>>24;
	}

	if(resto == -3){
		return (mem_ptr[(_t)] & 0x0000ff00)>>8;
	}

}

void mem::sw(const unsigned address, int32_t constante, int32_t dado){
	int32_t _t = address + constante;

	if ((_t) > MAX_MEM ){
			cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
			sc_stop();
		}

	mem_ptr[(_t)] = dado;
}

void mem::sh(const unsigned address, int32_t constante, int32_t dado)
{
	int32_t _t = address + constante;
	int16_t resto;

	if ((_t) > MAX_MEM ){
		cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
		sc_stop();
	}

	if (constante % 2 != 0 ){
		cout << "Offset nao eh multiplo de 2!" << endl;
		sc_stop();
	}

	resto = constante % 4;

	if(!resto){
		mem_ptr[(_t)] = (dado & 0x0000ffff) | (mem_ptr[_t] & 0xffff0000);
	}


	if(resto == 2){
		mem_ptr[(_t)] = ((dado & 0x0000ffff) << 16) | (mem_ptr[(_t)] & 0x0000ffff);
	}

	if(resto == -2){
		mem_ptr[_t - 1] = ((dado & 0x0000ffff) << 16) | (mem_ptr[_t - 1] & 0x0000ffff);
	}

}

void mem::sb(const unsigned address, int32_t constante, int32_t dado){
	int32_t _t = address + constante;
	int16_t resto;

	if ((_t) > MAX_MEM ){
			cout << "Endereco fora do intervalo de tamanho da memoria!" << endl;
			sc_stop();
		}

	resto = constante % 4;

	if(!resto){
		mem_ptr[_t] = (dado & 0x000000ff) | (mem_ptr[_t] & 0xffffff00);
	}

	if(resto == 1){
		mem_ptr[_t] = ((dado & 0x000000ff) << 8) | (mem_ptr[_t] & 0xffff00ff);	}

	if(resto == -1){
		mem_ptr[_t - 1] = ((dado & 0x000000ff) << 24) | (mem_ptr[_t - 1] & 0x00ffffff);	}

	if(resto == 2){
		mem_ptr[_t] = ((dado & 0x000000ff) << 16) | (mem_ptr[_t] & 0xff00ffff);	}

	if(resto == -2){
		mem_ptr[_t-1] = ((dado & 0x000000ff) << 16) | (mem_ptr[_t - 1] & 0xff00ffff);		}

	if(resto == 3){
		mem_ptr[_t] = ((dado & 0x000000ff) << 24) | (mem_ptr[_t] & 0x00ffffff);	}

	if(resto == -3){
		mem_ptr[_t-1] = ((dado & 0x000000ff) << 8) | (mem_ptr[_t - 1] & 0xffff00ff);	}
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

