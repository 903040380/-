#pragma once         //防止头文件重复包含
#include <iostream>  //输入输出流头文件 cout cin
using namespace std; //标准命名空间
#include <string>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

class workerManager{
public:
	workerManager();

	void showMenu();

	void exitSystem();

	void addEmp();

	void save();

	//判断文件是否为空
	bool m_fileIsEmpty;

	//统计文件内职工人数
	int getEmpNum();

	//初始化员工   
	void initEmp();

	//记录职工人数
	int m_empNum;

	//显示职工
	void showEmp();

	//删除职工
	void delEmp();

	//判断职工存在
	int isExist(int id);

	//修改职工
	void modEmp();

	//查找职工
	void findEmp();

	//排序职工
	void sortEmp();

	//清空文件
	void clFile();


	//职工数组指针
	worker ** m_empArray;

	~workerManager();
};
