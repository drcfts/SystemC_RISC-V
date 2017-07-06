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
    int send;
    char rec;
    for (;;) {
        // Writing
        NoCDebug::printDebug("ShellRISC <- Master", NoCDebug::NI);
        shellIn.read(send);
        std::vector<uint32_t> payload;
        payload.push_back(send);
        // DESTINO -> MEMÓRIA, qual o valor ?????????//////
        int payloadDst = 1;
        NoCDebug::printDebug("ShellRISC -> Channel", NoCDebug::NI);
        sendPayload(payload, payloadDst);
        payload.clear();

        // Reading
        int payloadSrc;
        NoCDebug::printDebug("ShellRISC <- Channel", NoCDebug::NI);
        receivePayload(payload, &payloadSrc);
        rec = payload.at(0);
        NoCDebug::printDebug("ShellRISC -> Master", NoCDebug::NI);
        shellOut.write(rec);

        // Só lê do Master
//        int readVal;
//        shellIn.read(readVal);
//        std::cout << readVal << std::endl;
//        char writeVal = 'v';
//        shellOut.write(writeVal);
    }
}


