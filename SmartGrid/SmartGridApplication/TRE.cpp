#include "TRE.h"

void requestBill(int token, int& proof, double& result)
{
	proof = (token >> 5) + 7;

	result = 100000;
}
