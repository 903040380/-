#include "boss.h"
#include <iostream>

boss::boss(int id,string name,int deptId){
	this->m_id=id;
	this->m_name=name;
	this->m_deptId=deptId;
}

 void boss::showInfo(){
	 cout<<"ְ����ţ�"<<this->m_id
	 <<"\tְ��������"<<this->m_name
	 <<"\tְ����λ��"<<this->getDeptName()
	 <<"\t��λְ�𣺹�����"<<endl;
 }

string boss::getDeptName(){
	return string("�ϰ�");
}