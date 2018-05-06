#include "TRE.h"



TRE::TRE(sgx_enclave_id_t eid)
{
	TRE::eid = eid;
}

void TRE::calculateBill(int random_token, int * proof)
{
	tre_bill_calculation(eid, random_token, proof);
}
