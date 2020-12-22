#pragma once         //��ֹͷ�ļ��ظ�����
#include <iostream>  //���������ͷ�ļ� cout cin
using namespace std; //��׼�����ռ�
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

	//�ж��ļ��Ƿ�Ϊ��
	bool m_fileIsEmpty;

	//ͳ���ļ���ְ������
	int getEmpNum();

	//��ʼ��Ա��   
	void initEmp();

	//��¼ְ������
	int m_empNum;

	//��ʾְ��
	void showEmp();

	//ɾ��ְ��
	void delEmp();

	//�ж�ְ������
	int isExist(int id);

	//�޸�ְ��
	void modEmp();

	//����ְ��
	void findEmp();

	//����ְ��
	void sortEmp();

	//����ļ�
	void clFile();


	//ְ������ָ��
	worker ** m_empArray;

	~workerManager();
};
