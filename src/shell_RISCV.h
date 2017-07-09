/*
 * shell_RISCV.h
 *
 *  Created on: 4 de jul de 2017
 *      Author: drcfts e litlle toin
 */

#ifndef SRC_SHELL_RISCV_H_
#define SRC_SHELL_RISCV_H_

#include <systemc.h>
#include "networkinterfacefrontendbase.h"
#include "shared.h"


class ShellRISCV : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(ShellRISCV);

    void _threadRun();

public:
    // IO
    sc_fifo_in< uint32_t >  shellIn;
    sc_fifo_out< uint32_t >  shellOut;

    ShellRISCV(sc_module_name name);
};


#endif /* SRC_SHELL_RISCV_H_ */
