#include "systemc.h"
#include "cache_pr.h"

void cache::address_handler(){

	int align;
	int _address;
	
	_address = address.read();
	align = (_address & 0x00000003);
	if(align != 0){
		std::cout << "Endereco desalinhado. Vai dar ruim." << std::endl;
	}
	else{
		address_offset = ((_address >> 2) & 0x0000000F);
		address_index = ((_address >> 6) & 0x000000FF);
		address_tag = ((_address >> 14) & 0x0003FFFF);
	}
}

void cache::get_data(){

	address_handler();

	if(address_offset < 0 || address_offset > 15 || address_tag < 0 || address_tag > 262143 || address_index < 0 || address_index > 255 ){
		std::cout << "Endereco fora dos limites da memoria" << std::endl;
	}
	else{
		if(address_tag == cached_tag[index]){
			data.write(cached_data[index][offset]);
			hit.write(true);
		}
		else{
			data.write(0x0);
			hit.write(false);
			
			//call_mem(address);
			//cash_writer(address, data);
		}
	}
}
