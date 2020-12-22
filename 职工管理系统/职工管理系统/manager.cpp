#include "manager.h"
#include <iostream>

manager::manager(int id,string name,int deptId){
	this->m_id=id;
	this->m_name=name;
	this->m_deptId=deptId;
}

 void manager::showInfo(){
	 cout<<"职工编号："<<this->m_id
	 <<"\t职工姓名："<<this->m_name
	 <<"\t职工岗位："<<this->getDeptName()
	 <<"\t岗位职责：管理员工"<<endl;
 }

string manager::getDeptName(){
	return string("经理");
}