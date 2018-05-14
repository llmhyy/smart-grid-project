#include "UtilityCompany.h"
#include <stdio.h>


UtilityCompany::UtilityCompany(sgx_enclave_id_t eid)
{
	UtilityCompany::eid = eid;
}

int UtilityCompany::generateToken()
{
	int encrpted_random_token;
	
	uc_generateToken(eid, &encrpted_random_token);

	return encrpted_random_token;
}

int UtilityCompany::checkproof(int* proof)
{
	int result;
	uc_check_proof(eid, &result, proof);

	return result;
}
