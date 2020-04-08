#include "workerManager.h"
using namespace std;
#include"worker.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include <sstream>
#include <string>
#include<vector>


WorkerManager::WorkerManager() {

	// �ļ������ڻ��ļ�Ϊ��
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	this->m_FileIsEmpty = true;
	if (ifs.is_open()) {
		char ch;
		ifs >> ch;
		if (!ifs.eof()) {
			this->m_FileIsEmpty = false;
			ifs.close();
		}
	}
	if (this->m_FileIsEmpty){
		if (!ifs.is_open())
			cout << "�ļ�������" << endl;
		else
			cout << "�ļ�Ϊ��" << endl;
	
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	else {
		int num = this->get_EmpNum();
		cout << "ְ������Ϊ�� " << num << endl;
		this->m_EmpNum = num;

		// ���ٿռ��������
		this->m_EmpArray = new Worker*[this->m_EmpNum];
		this->init_Emp();
	}
	
}

// ��ʾ�˵�
void WorkerManager::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ��  *********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְ��Ϣ  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

// ���ְ��
void WorkerManager::Add_Emp() {
	cout << "���������ְ������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->m_EmpNum + addNum;
		
		//�����¿ռ�
		Worker ** newSpace = new Worker*[newSize];

		// ��ԭ�����ݿ������¿ռ�
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		// ���������
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			cout << "������� " << i + 1 << " ����ְ����ţ� " << endl;
			while (1) {
				cin >> id;
				if (this->IsExist(id) == -1)
					break;
				else
					cout << "id�ظ�������������" << endl;
			}
			cout << "������� " << i + 1 << " ����ְ�������� " << endl;
			cin >> name;

			cout << "������� " << i + 1 << " ����ְ����λ�� " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			while (1) {
				cin >> dSelect;
				if (dSelect == 1 || dSelect == 2 || dSelect == 3)
					break;
				else
					cout << "��������û�и�ְλ������������" << endl;
			}
			

			Worker * worker = NULL;
			
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				cout << "��������û�и�ְλ������������" << endl;
				break;
			}
			// ������ְ�����浽����
			newSpace[this->m_EmpNum + i] = worker;
			
		}
		// �ͷ�ԭ�пռ�
		
		delete[] this->m_EmpArray;
		
		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;
		//��������
		this->m_EmpNum = newSize;
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��!" << endl;
		

		// ��������
		this->save();
		this->m_FileIsEmpty = false;
		
	}
	else
		cout << "��������" << endl;
	system("pause");
	system("cls");
}

void WorkerManager::save() {
	
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//д��
	
	ofs << "ְ�����" << "," << "ְ������" << "," << "ְ��ְλ" << endl;
	
	for (int i = 0 ; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << ","
			<< this->m_EmpArray[i]->m_Name << ","
			<< this->m_EmpArray[i]->getDeptName() << endl;
	}
	ofs.close();
}

int WorkerManager::get_EmpNum()  {
	int num = 0;
	if (!this->m_FileIsEmpty) {
		ifstream ifs;
		ifs.open(FILENAME, ios::in);
		string line;
		
		while (getline(ifs, line)) {
			num++;
		}
		num -= 1;

	}
	return num;
}

 //��ʼ��Ա��
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string line;
	int index = 0;
	while (getline(ifs, line)) {

		istringstream sin(line);
		vector<string> fields;
		string field;
		if (index > 0) {
			while (getline(sin, field, ',')) {
				fields.push_back(field);
			}
			int id = std::stoi(Trim(fields[0]));
			string name = Trim(fields[1]);
			string dId = Trim(fields[2]);
			Worker * worker = NULL;

			if (dId == "Ա��") {
				worker = new Employee(id, name, 1);
			}
			else if (dId == "����") {
				worker = new Manager(id, name, 2);
			}
			else if (dId == "�ܲ�") {
				worker = new Boss(id, name, 3);
			}
			this->m_EmpArray[index - 1] = worker;
		}
		index++;
	}
	ifs.close();
}

void WorkerManager::Show_Emp() {
	//�ж��ļ��Ƿ�������
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

// ɾ��Ա��
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;

	}
	else {
		// ��idɾ��
		cout << "����Ҫɾ��id" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		
		if (index != -1) {
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			// ͬ�����ļ���
			this->save();
		}
		else
			cout << "δ�ҵ������ݣ�ɾ��ʧ��" << endl;
	}
	system("pause");
	system("cls");
}

// �ж�ְ���Ƿ����
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}


// �޸�ְ��
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		cout << "�������޸��û���ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			//���ұ��Ա��
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "�鵽�� " << id << "��ְ��,��������ְ���ţ�" << endl;
			cin >> newId;
			cout << "�������µ�����: " << endl;
			cin >> newName;
			cout << "�������µĸ�λ: " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			while (1) {
				cin >> dSelect;
				if (dSelect == 1 || dSelect == 2 || dSelect == 3)
					break;
				else
					cout << "��������û�и�ְλ������������" << endl;
			}

			Worker * worker = NULL;

			switch (dSelect) {
			case 1:
				worker = new Employee(newId, newName, 1);

				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				cout << "��������û�и�ְλ������������" << endl;
				break;
			}
			// ���µ�������
			this->m_EmpArray[ret] = worker;
			cout << "�޸ĳɹ�" << endl;

			// ����
			this->save();
			
		}
		else {
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����Ա��
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;

	}
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1.����ְ����Ų���" << endl;
		cout << "2.����ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			// ����Ų�
			int id;
			cout << "�������û����ұ�� " << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1) {
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
				cout << "���޴���" << endl;
		}
		else if (select == 2) {
			// �����ֲ�
			string name;
			cout << "�������û��������� " << endl;
			cin >> name;

			bool flag = false; // �Ƿ��и�Ա��0
			for (int i = 0; i < m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
					
				}
				
			}
			if (flag == false)
				cout << "����ʧ�ܣ����޴���" << endl;
		}
		else {
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");

}

void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
		system("pause");
		system("cls");

	}
	else
	{
		cout << "����������ʽ" << endl;
		cout << "1.����ְ�������������" << endl;
		cout << "2.����ְ����Ž�������" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum-1; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < m_EmpNum; j++) {
				if (select == 1) {
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
					
				}
				else {
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) {
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax) {
				Worker * temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "����ɹ����������Ϊ��" << endl;
		this->save();
		this->Show_Emp();
	}

}

void WorkerManager::Clean_File() {
	cout << "ȷ�����?" << endl;
	cout << "1.ȷ��!" << endl;
	cout << "2.����!" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�!!!" << endl;
	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			delete this->m_EmpArray[i];
			this->m_EmpArray[i] = NULL;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}


// ��ȡcsv
string Trim(string& str)
{
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}
