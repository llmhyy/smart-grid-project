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

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#pragma warning(disable: 4200)
#endif

static sgx_status_t SGX_CDECL sgx_uc_generateToken(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_uc_generateToken_t));
	ms_uc_generateToken_t* ms = SGX_CAST(ms_uc_generateToken_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	ms->ms_retval = uc_generateToken();


	return status;
}

static sgx_status_t SGX_CDECL sgx_uc_check_proof(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_uc_check_proof_t));
	ms_uc_check_proof_t* ms = SGX_CAST(ms_uc_check_proof_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_proof = ms->ms_proof;


	ms->ms_retval = uc_check_proof(_tmp_proof);


	return status;
}

static sgx_status_t SGX_CDECL sgx_tre_bill_calculation(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_tre_bill_calculation_t));
	ms_tre_bill_calculation_t* ms = SGX_CAST(ms_tre_bill_calculation_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_proof = ms->ms_proof;


	tre_bill_calculation(ms->ms_random_token, _tmp_proof);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* call_addr; uint8_t is_priv;} ecall_table[3];
} g_ecall_table = {
	3,
	{
		{(void*)(uintptr_t)sgx_uc_generateToken, 0},
		{(void*)(uintptr_t)sgx_uc_check_proof, 0},
		{(void*)(uintptr_t)sgx_tre_bill_calculation, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
} g_dyn_entry_table = {
	0,
};


#ifdef _MSC_VER
#pragma warning(pop)
#endif
