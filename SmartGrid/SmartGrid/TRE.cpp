#include "stdafx.h"
#include "TRE.h"


void TRE::loadCalculation()
{
	// Send calculation program to SGX
}

void TRE::sendData()
{
	// Send data to SGX
}

TRE::TRE()
{
}

TRE::TRE(int data)
{
	smartMeterData = data;
}

void TRE::requestBill()
{
	//Create SGX environment
	loadCalculation();
	sendData();
}

string TRE::getResult()
{
	return string();
}
