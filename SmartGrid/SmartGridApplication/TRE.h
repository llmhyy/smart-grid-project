#pragma once
#include "SmartGrid_u.h"

class TRE
{
private:
	sgx_enclave_id_t eid;
public:
	TRE(sgx_enclave_id_t eid);
	void calculateBill(int random_token, int* proof);
};

