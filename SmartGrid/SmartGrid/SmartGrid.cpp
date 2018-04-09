#include "SmartGrid_t.h"

#include "sgx_trts.h"
#include "stdlib.h"
#include <functional>

//SGX functions
//SmartGrid bill calculation within SGX
void calculate(double rate)
{
	double userdata;
	getUserData(&userdata);
	double result = userdata * rate;
	

	size_t proof = std::hash<double>{}(rate);
	sendBill(result, proof);
}

//SmartGrid send bill to utility company
void sendBill(double result, size_t proof)
{

}
