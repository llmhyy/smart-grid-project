#ifndef SMARTGRID_T_H__
#define SMARTGRID_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


int uc_generateToken();
int uc_check_proof(int* proof);
void tre_bill_calculation(int random_token, int* proof);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
