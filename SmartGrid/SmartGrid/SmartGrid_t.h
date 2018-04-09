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


void calculate(double rate);
void sendBill(double result, size_t proof);

sgx_status_t SGX_CDECL getUserData(double* retval);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
