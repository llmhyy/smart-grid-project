#pragma once
#include <string>

using namespace std;

class TRE
{
private:
	int smartMeterData;
	void loadCalculation();
	void sendData();
public:
	TRE();
	TRE(int data);
	void requestBill();
	string getResult();
};