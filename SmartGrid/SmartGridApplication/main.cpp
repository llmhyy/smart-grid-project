#define ENCLAVE_FILE "SmartGrid.signed.dll"

#include "sgx_urts.h"
#include "SmartGrid_u.h"
#include "stdio.h"
#include "UtilityCompany.h"
#include "TRE.h"
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

	//Assume this main() is channel between Utility Company and TRE
	//The attacker is able to modify encrpyted_token, proof, bill.
	//These are values which are transfered through the channel
	//and the attacker is able to modify them.
	UtilityCompany uc = UtilityCompany(eid);
	TRE tre = TRE(eid);
	
	//Random token is generated from Utility Company's SGX
	int encrypted_token;
	encrypted_token = uc.generateToken();

	//Attacker can modify the token before it reaches to TRE
	//The modification can be done here.

	int proof[2];
	tre.calculateBill(encrypted_token, proof);

	//Attacker can modify proof or bill before it reaches to Utility Company
	//The modification can be done here.
	
	int result = uc.checkproof(proof);

	int decrypted_bill = *(proof+1) - 7;
	
	printf("Pre-define correct bill amount is: 500 * 1.34 = 670\n\n");
	if (result)
	{
		printf("CORRECT PROOF. Bill amount: %d\n", decrypted_bill);
	}
	else
	{
		printf("INCORRECT PROOF. Bill amount: %d\n", decrypted_bill);
	}

	clearSGXEnvironment();

	return 0;
}
