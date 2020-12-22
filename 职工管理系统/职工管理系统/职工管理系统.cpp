#include "workerManager.h"
#include <iostream>
using namespace std;

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"


int main(){


	//实例化管理对象
    workerManager wm;

	int choice = 0;
	
	while(true)
	{
	wm.showMenu();

	cout<<"请输入您的选择："<<endl;
	cin>>choice;

	switch (choice)
	{
	case 0:
		wm.exitSystem();
		break;
	case 1:
		wm.addEmp();
		break;
	case 2:
		wm.showEmp();
		break;
	case 3:
		wm.delEmp();
		break;
	case 4:
		wm.modEmp();
		break;
	case 5:
		wm.findEmp();
		break;
	case 6:
		wm.sortEmp();
		break;
	case 7:
		wm.clFile();
		break;
	default:
		system("cls");
		break;
	}
}
	
	system("pause");

};