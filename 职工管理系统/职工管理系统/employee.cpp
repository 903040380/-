#include "employee.h"
#include <iostream>

employee::employee(int id,string name,int deptId){
	this->m_id=id;
	this->m_name=name;
	this->m_deptId=deptId;
}

 void employee::showInfo(){
	 cout<<"职工编号："<<this->m_id
	 <<"\t职工姓名："<<this->m_name
	 <<"\t职工岗位："<<this->getDeptName()
	 <<"\t岗位职责：工作"<<endl;
 }

string employee::getDeptName(){
	return string("员工");
}