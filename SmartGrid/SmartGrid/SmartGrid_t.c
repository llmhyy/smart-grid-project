#include "SmartGrid_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <errno.h>
#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_calculate(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_calculate_t));
	ms_calculate_t* ms = SGX_CAST(ms_calculate_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	calculate(ms->ms_rate);


	return status;
}

static sgx_status_t SGX_CDECL sgx_sendBill(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_sendBill_t));
	ms_sendBill_t* ms = SGX_CAST(ms_sendBill_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	sendBill(ms->ms_result, ms->ms_proof);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[2];
} g_ecall_table = {
	2,
	{
		{(void*)(uintptr_t)sgx_calculate, 0},
		{(void*)(uintptr_t)sgx_sendBill, 1},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[1][2];
} g_dyn_entry_table = {
	1,
	{
		{0, 0, },
	}
};


sgx_status_t SGX_CDECL getUserData(double* retval)
{
	sgx_status_t status = SGX_SUCCESS;

	ms_getUserData_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_getUserData_t);
	void *__tmp = NULL;


	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_getUserData_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_getUserData_t));

	status = sgx_ocall(0, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
