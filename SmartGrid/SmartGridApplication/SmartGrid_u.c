#include "SmartGrid_u.h"
#include <errno.h>

typedef struct ms_calculate_t {
	double ms_rate;
} ms_calculate_t;

typedef struct ms_sendBill_t {
	double ms_result;
	size_t ms_proof;
} ms_sendBill_t;

typedef struct ms_getUserData_t {
	double ms_retval;
} ms_getUserData_t;

static sgx_status_t SGX_CDECL SmartGrid_getUserData(void* pms)
{
	ms_getUserData_t* ms = SGX_CAST(ms_getUserData_t*, pms);
	ms->ms_retval = getUserData();

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * func_addr[1];
} ocall_table_SmartGrid = {
	1,
	{
		(void*)(uintptr_t)SmartGrid_getUserData,
	}
};

sgx_status_t calculate(sgx_enclave_id_t eid, double rate)
{
	sgx_status_t status;
	ms_calculate_t ms;
	ms.ms_rate = rate;
	status = sgx_ecall(eid, 0, &ocall_table_SmartGrid, &ms);
	return status;
}

sgx_status_t sendBill(sgx_enclave_id_t eid, double result, size_t proof)
{
	sgx_status_t status;
	ms_sendBill_t ms;
	ms.ms_result = result;
	ms.ms_proof = proof;
	status = sgx_ecall(eid, 1, &ocall_table_SmartGrid, &ms);
	return status;
}

