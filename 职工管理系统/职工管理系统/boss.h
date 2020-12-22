#pragma once
using namespace std;
#include "worker.h"

class boss:public worker{
public:
	boss(int id,string name,int deptId);

	virtual void showInfo();
	virtual string getDeptName();
};