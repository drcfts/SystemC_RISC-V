/*
 * shell_RISCV.cpp
 *
 *  Created on: 4 de jul de 2007
 *      Author: drcfts
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
    uint32_t* send;
    uint32_t overhead;
    uint32_t* rec, *aux;
    for (;;) {
        // Writing
        NoCDebug::printDebug("ShellRISC <- Master", NoCDebug::NI);
        shellIn.read(send);
        std::vector<uint32_t> payload;
        while(send!=NULL){
        	payload.push_back(*send);
        	send++;
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

        shellOut.write(&overhead);
        //Se deu certo
        if(overhead){

        	NoCDebug::printDebug("ShellRISC -> Master", NoCDebug::NI);
        	aux = rec;
        	for(int x=1;x <= 16;x++)
        	{
        		*aux = payload.at(x);
        		aux++;

        	}
        	shellOut.write(rec);
        }
        //Se n deu certo, n escreve de volta para a Cache

        // Só lê do Master
//        int readVal;
//        shellIn.read(readVal);
//        std::cout << readVal << std::endl;
//        char writeVal = 'v';
//        shellOut.write(writeVal);
    }
}


