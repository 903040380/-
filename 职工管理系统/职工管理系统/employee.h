#pragma once
using namespace std;
#include "worker.h"

class employee:public worker{
public:
	employee(int id,string name,int deptId);

	virtual void showInfo();
	virtual string getDeptName();
};