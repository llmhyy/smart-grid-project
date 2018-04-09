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

double SGX_UBRIDGE(SGX_NOCONVENTION, getUserData, ());

sgx_status_t calculate(sgx_enclave_id_t eid, double rate);
sgx_status_t sendBill(sgx_enclave_id_t eid, double result, size_t proof);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
