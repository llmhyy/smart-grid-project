#define ENCLAVE_FILE "SmartGrid.signed.dll"

#include "sgx_urts.h"
#include "SmartGrid_u.h"
#include "stdio.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include "TRE.h"

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
	
	srand((unsigned)time(0));
	int randomToken = rand();
	int proof;
	double result;

	requestBill(randomToken, proof, result);

	printf("My randomToken is %d\n", randomToken);
	printf("My proof calculation is %d\n", (randomToken >> 5) + 7);
	printf("My proof from tre is %d\n", proof);

	clearSGXEnvironment();

	return 0;
}
