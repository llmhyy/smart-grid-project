#ifndef SMARTGRID_U_H__
#define SMARTGRID_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


sgx_status_t uc_generateToken(sgx_enclave_id_t eid, int* retval);
sgx_status_t uc_check_proof(sgx_enclave_id_t eid, int* retval, int* proof);
sgx_status_t tre_bill_calculation(sgx_enclave_id_t eid, int random_token, int* proof);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
