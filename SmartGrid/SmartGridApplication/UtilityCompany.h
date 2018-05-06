#pragma once
#include "SmartGrid_u.h"

class UtilityCompany
{
private:
	sgx_enclave_id_t eid;
public:
	UtilityCompany(sgx_enclave_id_t eid);
	int generateToken();
	int checkproof(int* proof);
};

