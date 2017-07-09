#ifndef SHELL_MEM_RISC_H
#define SHELL_MEM_RISC_H

#include "systemc.h"
#include "SHELL_MEM_RISC_if.h"

struct shell_mem_risc : public sc_module,public shell_mem_risc_if {

    sc_fifo_in< std::vector<uint32_t> > shellMEM_RISC_In;
    sc_fifo_out< std::vector<uint32_t> > shellMEM_RISC_Out;


	int32_t lw(const unsigned address, int32_t constante);

	int32_t lh(const unsigned address, int32_t constante);

	int32_t lhu(const unsigned address, int32_t constante);

	int32_t lb(const unsigned address, int32_t constante);

	int32_t lbu(const unsigned address, int32_t constante);

	void sw(const unsigned address, int32_t constante, int32_t dado);

	void sh(const unsigned address, int32_t constante, int32_t dado);

	void sb(const unsigned address, int32_t constante, int32_t dado);



    SC_HAS_PROCESS( shell_mem_risc );
    shell_mem_risc (
        sc_module_name _name,
        unsigned int identify
                          ):
    sc_module(_name), identify(identify)
    {

    }
  private:
    unsigned int identify;


};

#endif
