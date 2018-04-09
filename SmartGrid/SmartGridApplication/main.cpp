#define ENCLAVE_FILE "SmartGrid.signed.dll"

#include "sgx_urts.h"
#include "SmartGrid_u.h"
#include "stdio.h"
#include <string>

sgx_enclave_id_t eid;
sgx_status_t ret = SGX_SUCCESS;
sgx_launch_token_t token = { 0 };
int updated = 0;

void initSGXEnvironment()
{
	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
	if (ret != SGX_SUCCESS) {
		printf("SGX creation failed\n");
	}
}

void clearSGXEnvironment()
{
	if (sgx_destroy_enclave(eid) != SGX_SUCCESS) {
		printf("SGX destroy failed\n");
	}
}

int main()
{
	initSGXEnvironment();
	
	printf("Hello\n");


	clearSGXEnvironment();

	return 0;
}
