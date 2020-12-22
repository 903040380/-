#include "workerManager.h"
#include <iostream>
using namespace std;

workerManager::workerManager(){
	//�ļ�������

	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	
	if(!ifs.is_open()){
	//cout<<"�ļ�������"<<endl;
		this->m_empNum = 0;
		this->m_empArray = NULL;
		this->m_fileIsEmpty = true;

		ifs.close();
		return;
	}

	//�ļ����� ����Ϊ��

	char ch;
	ifs >> ch;
	if(ifs.eof()){
	//cout<<"�ļ����� ����Ϊ��"<<endl;
		this->m_empNum = 0;
		this->m_empArray = NULL;
		this->m_fileIsEmpty = true;

		ifs.close();
		return;
	}

	//�ļ����� ���ݴ���

	int num = this->getEmpNum();
	//cout<<"ְ��������"<<num<<endl;
	this->m_empNum = num;
	this->m_fileIsEmpty = false;

	this->m_empArray = new worker*[this->m_empNum];
	this->initEmp();

	/*for(int i=0;i<this->m_empNum;i++){
		cout<<"���"<<this->m_empArray[i]->m_id
			<<"����"<<m_empArray[i]->m_name
			<<"����"<<m_empArray[i]->m_deptId<<endl;
	}*/

}

void workerManager::showMenu(){
	cout<<"**********************************"<<endl;
	cout<<"**********0.�˳��������**********"<<endl;
	cout<<"**********1.����ְ����Ϣ**********"<<endl;
	cout<<"**********2.��ʾְ����Ϣ**********"<<endl;
	cout<<"**********3.ɾ��ְ����Ϣ**********"<<endl;
	cout<<"**********4.�޸�ְ����Ϣ**********"<<endl;
	cout<<"**********5.����ְ����Ϣ**********"<<endl;
	cout<<"**********6.���ձ������**********"<<endl;
	cout<<"**********7.��������ĵ�**********"<<endl;
	cout<<"**********************************"<<endl;
}

void workerManager::exitSystem(){
	cout<<"��ӭ�´�ʹ��"<<endl;
	system("pause");
	exit(0);
}

void workerManager::addEmp(){
	cout<<"���������ְ��������"<<endl;
	
	int addNum = 0;
	cin>>addNum;


	if(addNum>0){
//���������������¿ռ��С �¿ռ�����=�Ѽ�¼����+��������
		int newSize = this->m_empNum+addNum;

		worker ** newSpace = new worker*[newSize];

		if(this->m_empArray != NULL){
			for(int i=0;i<this->m_empNum;i++)
			{
				newSpace[i]=this->m_empArray[i];
			}
		}
		
		for(int i=0;i<addNum;i++){
			int id;
			string name;
			int dSelect;
			cout<<"�������"<<i+1<<"����ְ�����"<<endl;
			cin>>id;
			int ret=this->isExist(id);
			if(ret == -1){

				cout<<"�������"<<i+1<<"����ְ������"<<endl;
			    cin>>name;
			    cout<<"��ѡ���ְ����λ"<<endl;
			    cout<<"1.Ա��"<<endl;
			    cout<<"2.����"<<endl;
			    cout<<"3.�ϰ�"<<endl;
		    	cin>>dSelect;

		    	worker * wk = NULL;
		    	switch (dSelect)
			    {
			    case 1:
				    wk=new employee(id,name,dSelect);
				    break;
			    case 2:
				    wk=new manager(id,name,dSelect);
		 		    break;
		    	case 3:
				    wk=new boss(id,name,dSelect);
	    			break;
		    	default:
			    	break;
               }
				//��������ְ����Ϣ���浽������
			    newSpace[this->m_empNum+i] = wk;
				//�ͷ��Ѽ�¼�ռ�
		        delete[] this->m_empArray;
		        //�Ѽ�¼�ռ�ָ���¿ռ�
		        this->m_empArray=newSpace;
		        //���¸���
		        this->m_empNum=newSize;
		        //����ְ����Ϊ��
		        this->m_fileIsEmpty = false;
		
		        cout<<"�ɹ����"<<addNum<<"����ְ��!"<<endl;

		        this->save();
		    }
			else{
				cout<<"ְ������ظ���"<<endl;
			}
			
		}

		
	}
	else{
		cout<<"������������������"<<endl;
	}

	//����
	system("pause");
	system("cls");
}


void workerManager::save(){
	ofstream ofs;
	ofs.open(FILENAME,ios::out);

	for(int i=0;i<this->m_empNum;i++)
	{
		ofs<<this->m_empArray[i]->m_id<<" "
           <<this->m_empArray[i]->m_name<<" "
           <<this->m_empArray[i]->m_deptId<<endl;
	}

	ofs.close();
}

int workerManager::getEmpNum(){
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int deptId;

	int num = 0;

	while(ifs >> id && ifs >> name && ifs >> deptId){
		num++;
	}

	ifs.close();
	return num;
}

void workerManager::initEmp(){
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int deptId;
	
	int index = 0;

	while(ifs>>id && ifs>>name && ifs>>deptId){

		worker * wk = NULL;

		if(deptId==1){
			wk = new employee(id,name,deptId);
		}
		else if(deptId==2){
			wk = new manager(id,name,deptId);
		}
		else if(deptId==3){
			wk = new boss(id,name,deptId);
		}

		this->m_empArray[index]=wk;
		index++;
	}
	ifs.close();
}

void workerManager::showEmp(){

	if(this->m_fileIsEmpty){
		cout<<"�ļ������ڻ��߼�¼Ϊ��!"<<endl;
	}
	else{
		for(int i = 0;i<m_empNum;i++){
			this->m_empArray[i]->showInfo();
		}
	}

	//����
	system("pause");
	system("cls");
}

void workerManager::delEmp(){
	if(this->m_fileIsEmpty){
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
	}
	else{
		cout<<"��������Ҫɾ����ְ����ţ�"<<endl;
		int id=0;
		cin>>id;

		int index = this->isExist(id);

		if(index!=-1){
			for(int i=index;i<this->m_empNum-1;i++){
				this->m_empArray[i]=this->m_empArray[i+1];
			}
			this->m_empNum--;
			this->save();

			cout<<"ɾ���ɹ���"<<endl;
		}
		else{
			cout<<"���޴��ˣ�"<<endl;
		}
	}
	system("pause");
	system("cls");

}


int workerManager::isExist(int id){
	int index = -1;
	for(int i=0 ;i<this->m_empNum ;i++){
		if(this->m_empArray[i]->m_id == id){
		index = i;
		break;
		}
	}
	return index;
}

void workerManager::modEmp(){
	if(this->m_fileIsEmpty){
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
	}
	else{
		cout<<"��������Ҫ�޸ĵ�ְ����ţ�"<<endl;
		int id;
		cin>>id;

		int ret = this->isExist(id);

		if(ret != -1){
			delete this->m_empArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout<<"�鵽"<<id<<"��ְ������������ְ����ţ�"<<endl;
			cin>>newId;
			cout<<"��������ְ������"<<endl;
			cin>>newName;
			cout<<"��ѡ����ְ����λ"<<endl;
			cout<<"1.Ա��"<<endl;
			cout<<"2.����"<<endl;
			cout<<"3.�ϰ�"<<endl;
			cin>>dSelect;

			worker * wk = NULL;
			switch (dSelect)
			{
			case 1:
				wk=new employee( newId,newName,dSelect);
				break;
			case 2:
				wk=new manager( newId,newName,dSelect);
				break;
			case 3:
				wk=new boss( newId,newName,dSelect);
				break;
			default:
				break;
			}

			//�������ݵ�������
			this->m_empArray[ret] = wk;
			cout<<"�޸ĳɹ���"<<endl;

			this->save();
		}
		else{
			cout<<"���޴��ˣ�"<<endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::findEmp(){
	if(this->m_fileIsEmpty){
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
	}
	else{
		cout<<"��ѡ����ҵķ�ʽ��"<<endl;
		cout<<"1.��ְ����Ų���"<<endl;
		cout<<"2.��ְ����������"<<endl;

		int select = 0;
		cin>>select;

		if(select == 1){
			int id;
			cout<<"�������ְ����ţ�"<<endl;
			cin>>id;

			int ret = this->isExist(id);

			if(ret != -1){
				cout<<"���ҳɹ�����ְ����Ϣ���£�"<<endl;
				this->m_empArray[ret]->showInfo();
			}
			else{
				cout<<"���޴��ˣ�"<<endl;
			}
		}
		else if(select == 2){
			string name;
			cout<<"�������ְ��������"<<endl;
			cin>>name;

			//�����ж��Ƿ�鵽�ı�־
			bool flag = false;

			for(int i=0;i<this->m_empNum;i++){
				if(this->m_empArray[i]->m_name == name){
					cout<<"���ҳɹ�����ְ�����Ϊ��"
						<<this->m_empArray[i]->m_id
						<<"����Ϣ����"<<endl;
                    this->m_empArray[i]->showInfo();
					
					flag=true;
				    
				}
			}
			if(flag == false){
				cout<<"���޴��ˣ�"<<endl;
			}
		}
		else{
			cout<<"��������"<<endl;
		}

	}

	system("pause");
	system("cls");

}

void workerManager::sortEmp(){
	if(this->m_fileIsEmpty){
		cout<<"�ļ������ڻ��¼Ϊ�գ�"<<endl;
		system("pause");
	    system("cls");
	}
	else{
		cout<<"��ѡ������ķ�ʽ��"<<endl;
		cout<<"1.��ְ���������"<<endl;
		cout<<"2.��ְ����������"<<endl;
	}
	int select = 0;
	cin >>select;
	
	for(int i=0;i<this->m_empNum;i++){
		int minOrMax = i;
		for(int j = i+1;j<this->m_empNum;j++){

		    if(select == 1){
				if(this->m_empArray[minOrMax]->m_id > this->m_empArray[j]->m_id){
					minOrMax = j;
				}
		    }
			else{
				if(this->m_empArray[minOrMax]->m_id < this->m_empArray[j]->m_id){
					minOrMax = j;
				}
			}
		}

		//�ж�һ��ʼ�϶�����Сֵ�������ֵ�ǲ��Ǽ���ģ���������򽻻�����
		if(i!=minOrMax){
			worker * temp = this->m_empArray[i];
			this->m_empArray[i]=this->m_empArray[minOrMax];
		    this->m_empArray[minOrMax] = temp ;
		}
	}

	cout<<"����ɹ����������Ϊ��"<<endl;
	this->save();
	this->showEmp();
}

void workerManager::clFile(){
	cout<<"ȷ����գ�"<<endl;
	cout<<"1.ȷ��"<<endl;
	cout<<"2.����"<<endl;

	int select =0;
	cin>>select;

	if(select == 1){
		ofstream ofs(FILENAME,ios::trunc);
		ofs.close();

		if(this->m_empArray !=NULL)
		{
			for(int i=0;i<this->m_empNum;i++){
				delete this->m_empArray[i];
				this->m_empArray[i] = NULL;
			}
			delete[] this->m_empArray;
		    this->m_empArray=NULL;
			this->m_empNum;
			this->m_fileIsEmpty = true;
		}

		cout<<"��ճɹ���"<<endl;
	}
	system("pause");
	system("cls");
}

workerManager::~workerManager(){

	if(this->m_empArray != NULL){

		for(int i=0;i<this->m_empNum;i++){

			if(this->m_empArray[i] !=NULL){
				delete this->m_empArray[i];
			}
		}

		delete[] this->m_empArray;
		this->m_empArray=NULL;
	}
}