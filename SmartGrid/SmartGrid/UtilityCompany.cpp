#include "stdafx.h"
#include "UtilityCompany.h"


bool UtilityCompany::checkBill()
{
	return false;
}

UtilityCompany::UtilityCompany()
{
}

void UtilityCompany::setTRE(TRE tre)
{
	UtilityCompany::tre = tre;
}

void UtilityCompany::startBillRequest()
{
	tre.requestBill();
}

string UtilityCompany::getResult()
{
	return tre.getResult();
}
