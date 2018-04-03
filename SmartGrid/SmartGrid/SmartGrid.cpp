// SmartGrid.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "TRE.h"
#include "UtilityCompany.h"

using namespace std;

int main()
{
	TRE tre = TRE(100); // 100W
	UtilityCompany uc = UtilityCompany();

	uc.setTRE(tre);
	
	uc.startBillRequest();

	string result = uc.getResult();

	std::cout << result << std::endl;

    return 0;
}

