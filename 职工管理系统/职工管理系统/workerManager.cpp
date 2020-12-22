#include "workerManager.h"
#include <iostream>
using namespace std;

workerManager::workerManager(){
	//文件不存在

	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	
	if(!ifs.is_open()){
	//cout<<"文件不存在"<<endl;
		this->m_empNum = 0;
		this->m_empArray = NULL;
		this->m_fileIsEmpty = true;

		ifs.close();
		return;
	}

	//文件存在 数据为空

	char ch;
	ifs >> ch;
	if(ifs.eof()){
	//cout<<"文件存在 数据为空"<<endl;
		this->m_empNum = 0;
		this->m_empArray = NULL;
		this->m_fileIsEmpty = true;

		ifs.close();
		return;
	}

	//文件存在 数据存在

	int num = this->getEmpNum();
	//cout<<"职工人数："<<num<<endl;
	this->m_empNum = num;
	this->m_fileIsEmpty = false;

	this->m_empArray = new worker*[this->m_empNum];
	this->initEmp();

	/*for(int i=0;i<this->m_empNum;i++){
		cout<<"编号"<<this->m_empArray[i]->m_id
			<<"姓名"<<m_empArray[i]->m_name
			<<"部门"<<m_empArray[i]->m_deptId<<endl;
	}*/

}

void workerManager::showMenu(){
	cout<<"**********************************"<<endl;
	cout<<"**********0.退出管理程序**********"<<endl;
	cout<<"**********1.增加职工信息**********"<<endl;
	cout<<"**********2.显示职工信息**********"<<endl;
	cout<<"**********3.删除职工信息**********"<<endl;
	cout<<"**********4.修改职工信息**********"<<endl;
	cout<<"**********5.查找职工信息**********"<<endl;
	cout<<"**********6.按照编号排序**********"<<endl;
	cout<<"**********7.清空所有文档**********"<<endl;
	cout<<"**********************************"<<endl;
}

void workerManager::exitSystem(){
	cout<<"欢迎下次使用"<<endl;
	system("pause");
	exit(0);
}

void workerManager::addEmp(){
	cout<<"请输入添加职工数量："<<endl;
	
	int addNum = 0;
	cin>>addNum;


	if(addNum>0){
//计算添加入数组的新空间大小 新空间人数=已记录人数+新增人数
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
			cout<<"请输入第"<<i+1<<"个新职工编号"<<endl;
			cin>>id;
			int ret=this->isExist(id);
			if(ret == -1){

				cout<<"请输入第"<<i+1<<"个新职工姓名"<<endl;
			    cin>>name;
			    cout<<"请选择该职工岗位"<<endl;
			    cout<<"1.员工"<<endl;
			    cout<<"2.经理"<<endl;
			    cout<<"3.老板"<<endl;
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
				//将创建的职工信息保存到数组中
			    newSpace[this->m_empNum+i] = wk;
				//释放已记录空间
		        delete[] this->m_empArray;
		        //已记录空间指向新空间
		        this->m_empArray=newSpace;
		        //更新个数
		        this->m_empNum=newSize;
		        //更新职工不为空
		        this->m_fileIsEmpty = false;
		
		        cout<<"成功添加"<<addNum<<"名新职工!"<<endl;

		        this->save();
		    }
			else{
				cout<<"职工编号重复！"<<endl;
			}
			
		}

		
	}
	else{
		cout<<"输入有误，请重新输入"<<endl;
	}

	//清屏
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
		cout<<"文件不存在或者记录为空!"<<endl;
	}
	else{
		for(int i = 0;i<m_empNum;i++){
			this->m_empArray[i]->showInfo();
		}
	}

	//清屏
	system("pause");
	system("cls");
}

void workerManager::delEmp(){
	if(this->m_fileIsEmpty){
		cout<<"文件不存在或记录为空！"<<endl;
	}
	else{
		cout<<"请输入想要删除的职工编号："<<endl;
		int id=0;
		cin>>id;

		int index = this->isExist(id);

		if(index!=-1){
			for(int i=index;i<this->m_empNum-1;i++){
				this->m_empArray[i]=this->m_empArray[i+1];
			}
			this->m_empNum--;
			this->save();

			cout<<"删除成功！"<<endl;
		}
		else{
			cout<<"查无此人！"<<endl;
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
		cout<<"文件不存在或记录为空！"<<endl;
	}
	else{
		cout<<"请输入想要修改的职工编号："<<endl;
		int id;
		cin>>id;

		int ret = this->isExist(id);

		if(ret != -1){
			delete this->m_empArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout<<"查到"<<id<<"号职工，请输入新职工编号："<<endl;
			cin>>newId;
			cout<<"请输入新职工姓名"<<endl;
			cin>>newName;
			cout<<"请选择新职工岗位"<<endl;
			cout<<"1.员工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;
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

			//更新数据到数组中
			this->m_empArray[ret] = wk;
			cout<<"修改成功！"<<endl;

			this->save();
		}
		else{
			cout<<"查无此人！"<<endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::findEmp(){
	if(this->m_fileIsEmpty){
		cout<<"文件不存在或记录为空！"<<endl;
	}
	else{
		cout<<"请选择查找的方式："<<endl;
		cout<<"1.按职工编号查找"<<endl;
		cout<<"2.按职工姓名查找"<<endl;

		int select = 0;
		cin>>select;

		if(select == 1){
			int id;
			cout<<"请输入该职工编号："<<endl;
			cin>>id;

			int ret = this->isExist(id);

			if(ret != -1){
				cout<<"查找成功！该职工信息如下："<<endl;
				this->m_empArray[ret]->showInfo();
			}
			else{
				cout<<"查无此人！"<<endl;
			}
		}
		else if(select == 2){
			string name;
			cout<<"请输入该职工姓名："<<endl;
			cin>>name;

			//加入判断是否查到的标志
			bool flag = false;

			for(int i=0;i<this->m_empNum;i++){
				if(this->m_empArray[i]->m_name == name){
					cout<<"查找成功！该职工编号为："
						<<this->m_empArray[i]->m_id
						<<"号信息如下"<<endl;
                    this->m_empArray[i]->showInfo();
					
					flag=true;
				    
				}
			}
			if(flag == false){
				cout<<"查无此人！"<<endl;
			}
		}
		else{
			cout<<"输入有误！"<<endl;
		}

	}

	system("pause");
	system("cls");

}

void workerManager::sortEmp(){
	if(this->m_fileIsEmpty){
		cout<<"文件不存在或记录为空！"<<endl;
		system("pause");
	    system("cls");
	}
	else{
		cout<<"请选择排序的方式："<<endl;
		cout<<"1.按职工编号升序"<<endl;
		cout<<"2.按职工姓名降序"<<endl;
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

		//判断一开始认定的最小值或者最大值是不是计算的，如果不是则交换数据
		if(i!=minOrMax){
			worker * temp = this->m_empArray[i];
			this->m_empArray[i]=this->m_empArray[minOrMax];
		    this->m_empArray[minOrMax] = temp ;
		}
	}

	cout<<"排序成功！排序后结果为："<<endl;
	this->save();
	this->showEmp();
}

void workerManager::clFile(){
	cout<<"确定清空？"<<endl;
	cout<<"1.确定"<<endl;
	cout<<"2.返回"<<endl;

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

		cout<<"清空成功！"<<endl;
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