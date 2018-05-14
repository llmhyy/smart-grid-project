#include "SmartGrid_t.h"

#include "sgx_trts.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int uc_random_token;

int uc_generateToken()
{	
	unsigned char * rand;
	sgx_read_rand(rand, 4);
	uc_random_token = *rand;

	//Encryption
	int encrypted = uc_random_token + 7;

	return encrypted;
}

int uc_check_proof(int* proof)
{
	//Decryption
	int decrypted = *proof - 7;

	int uc_proof = (uc_random_token >> 5) + 7;

	return uc_proof == decrypted;
}

void tre_bill_calculation(int random_token, int* proof)
{
	//Decryption
	int decrypted = random_token - 7;

	//Creating proof
	*proof = ((decrypted >> 5) + 7);
	//Encryption
	*proof = *proof + 7;

	//Pre-defined bill calculation
	int user_data = 500;
	*(proof + 1) = (user_data * 1.34) + 7;
}