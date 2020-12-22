#pragma once
using namespace std;
#include "worker.h"

class manager:public worker{
public:
	manager(int id,string name,int deptId);

	virtual void showInfo();
	virtual string getDeptName();
};