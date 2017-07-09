
/*
 * shell_RISCV.cpp
 *
 *  Created on: 4 de jul de 2007
 *      Author: drcfts e litlle toin
 */

#include "shell_RISCV.h"
#include "nocdebug.h"

ShellRISCV::ShellRISCV(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void ShellRISCV::_threadRun()
{
	int flag_save = 0;
	uint32_t   send, rec;
    uint32_t overhead;
    for (;;) {
    	//Zera flag a cada iteracao
    	flag_save = 0;
        // Writing
        NoCDebug::printDebug("ShellRISC <- Master", NoCDebug::NI);
        send = shellIn.read();
        std::vector<uint32_t> payload;
        //comando,endereco
        //Payload eh um vetor
        //Se for save, tem-se endereco e dado
        if(send == _SB || send == _SW || send == _SH){
        	flag_save = 1;
        	//Coloca cmd
        	payload.push_back(send);
            send = shellIn.read();
            //Coloca endereco
        	payload.push_back(send);
            send = shellIn.read();
            //Coloca dado
        	payload.push_back(send);
        }
        //Se for load
        else{
        	//Coloca cmd
        	payload.push_back(send);
        	send = shellIn.read();
        	//Coloca endereco
        	payload.push_back(send);
        }
        // DESTINO -> MEMÓRIA, qual o valor ?????????//////
        int payloadDst = 1;
        NoCDebug::printDebug("ShellRISC -> Channel", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();

        // Reading
        int payloadSrc = 0;
        NoCDebug::printDebug("ShellRISC <- Channel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        overhead = payload.at(0);
        shellOut.write(overhead);
        //Se deu certo
        if(overhead){
        	//Se for load, le ainda o dado
        	if(!flag_save){
        		NoCDebug::printDebug("ShellRISC -> Master", NoCDebug::NI);
        		rec = payload.at(1);
        		shellOut.write(rec);
        	}
        }
        //Apos fim das operacoes, limpa payload
        payload.clear();

        //Se n deu certo, n escreve de volta para a Cache

        // Só lê do Master
//        int readVal;
//        shellIn.read(readVal);
//        std::cout << readVal << std::endl;
//        char writeVal = 'v';
//        shellOut.write(writeVal);
    }
}


