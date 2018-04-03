#pragma once
#include "TRE.h"
#include <string>

using namespace std;

class UtilityCompany
{
private:
	TRE tre;
	bool checkBill();
public:
	UtilityCompany();
	void setTRE(TRE tre);
	void startBillRequest();
	string getResult();
};

