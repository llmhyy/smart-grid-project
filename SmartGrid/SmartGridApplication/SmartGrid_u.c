#include "SmartGrid_u.h"
#include <errno.h>

typedef struct ms_uc_generateToken_t {
	int ms_retval;
} ms_uc_generateToken_t;

typedef struct ms_uc_check_proof_t {
	int ms_retval;
	int* ms_proof;
} ms_uc_check_proof_t;

typedef struct ms_tre_bill_calculation_t {
	int ms_random_token;
	int* ms_proof;
} ms_tre_bill_calculation_t;

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_SmartGrid = {
	0,
	{ NULL },
};

sgx_status_t uc_generateToken(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_uc_generateToken_t ms;
	status = sgx_ecall(eid, 0, &ocall_table_SmartGrid, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t uc_check_proof(sgx_enclave_id_t eid, int* retval, int* proof)
{
	sgx_status_t status;
	ms_uc_check_proof_t ms;
	ms.ms_proof = proof;
	status = sgx_ecall(eid, 1, &ocall_table_SmartGrid, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t tre_bill_calculation(sgx_enclave_id_t eid, int random_token, int* proof)
{
	sgx_status_t status;
	ms_tre_bill_calculation_t ms;
	ms.ms_random_token = random_token;
	ms.ms_proof = proof;
	status = sgx_ecall(eid, 2, &ocall_table_SmartGrid, &ms);
	return status;
}

