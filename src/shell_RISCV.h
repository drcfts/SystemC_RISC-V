/*
 * shell_RISCV.h
 *
 *  Created on: 4 de jul de 2017
 *      Author: drcfts
 */

#ifndef SRC_SHELL_RISCV_H_
#define SRC_SHELL_RISCV_H_

#include <systemc.h>
#include "networkinterfacefrontendbase.h"

class ShellRISCV : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ShellRISCV);

    void _threadRun();
   	std::vector<uint32_t> monta_send(uint32_t adress,uint32_t commando);

public:
    // IO
    sc_fifo_in< std::vector<uint32_t> >  shellIn;
    sc_fifo_out< std::vector<uint32_t> >  shellOut;

    ShellRISCV(sc_module_name name);
};


#endif /* SRC_SHELL_RISCV_H_ */
