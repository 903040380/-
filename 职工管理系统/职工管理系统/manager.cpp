#include "manager.h"
#include <iostream>

manager::manager(int id,string name,int deptId){
	this->m_id=id;
	this->m_name=name;
	this->m_deptId=deptId;
}

 void manager::showInfo(){
	 cout<<"ְ����ţ�"<<this->m_id
	 <<"\tְ��������"<<this->m_name
	 <<"\tְ����λ��"<<this->getDeptName()
	 <<"\t��λְ�𣺹���Ա��"<<endl;
 }

string manager::getDeptName(){
	return string("����");
}