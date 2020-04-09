#include<iostream>
using namespace std;
#include<fstream>
#include "student.h"
#include "teacher.h"
#include "manager.h"

// ��������Ա�˵�
void managerMenu(Identity * &manager) {
	while (1) {
		// ����˵�
		manager->openMenu();

		Manager * man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1) // ����˺�
		{
			cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2) // �鿴�˺�
		{
			cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if (select == 3) // �鿴����
		{
			cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if (select == 4) // ���ԤԼ
		{
			cout << "���ԤԼ" << endl;
			man->cleanFile();
		}
		else {
			delete manager;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

// ����ѧ���˵�
void studentMenu(Identity * &student) {
	while (1) {
		// ����˵�
		student->openMenu();

		Student * stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) // ����ԤԼ
		{
			cout << "����ԤԼ" << endl;
			stu->applyOrder();
		}
		else if (select == 2) // �鿴����ԤԼ
		{
			cout << "�鿴����ԤԼ" << endl;
			stu->showMyOrder();
		}
		else if (select == 3) // �鿴����ԤԼ
		{
			cout << "�鿴����ԤԼ" << endl;
			stu->showAllOrder();
		}
		else if (select == 4) // ȡ��ԤԼ
		{
			cout << "ȡ��ԤԼ" << endl;
			stu->cancelOrder();
		}
		else {
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

// ������ʦ�˵�
void TeacherMenu(Identity * &teacher) {
	while (1) {
		// ����˵�
		teacher->openMenu();

		Teacher * tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1) // �鿴����ԤԼ
		{
			cout << "�鿴����ԤԼ" << endl;
			tea->showAllOrder();
		}
		else if (select == 2) // ���ԤԼ
		{
			cout << "���ԤԼ" << endl;
			tea->validOrder();
		}
		
		else {
			delete teacher;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

// ��½����
void LoginIn(string fileName, int type) {
	Identity * person = NULL;

	// ���ļ�
	ifstream ifs(fileName);
	// �ж��ļ��Ƿ����
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	// ׼���û�������Ϣ
	int id = 0;
	string name;
	string pwd;

	// �ж����
	if (type == 1) {
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "���������ְ���ţ�" << endl;
		cin >> id;
	}
	cout << "�������û�����" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	if (type == 1) {
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			// ���û�������Ϣ�Ա�
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "ѧ����֤��½�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				// ����ѧ������Ӳ˵�
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			// ���û�������Ϣ�Ա�
			if (fId == id && fName == name && fPwd == pwd) {
				cout << "��ʦ��֤��½�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				// �����ʦ����Ӳ˵�
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3) {
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			// ���û�������Ϣ�Ա�
			if (fName == name && fPwd == pwd) {
				cout << "����Ա��֤��½�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				// �������Ա����Ӳ˵�
				managerMenu(person);
				return;
			}
		}

	}
	cout << "��֤��½ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
	return;
}



int main() {

	int select;
	while (1) {
		cout << "===================== ��ӭ��������ԤԼϵͳ =====================" << endl;
		cout << endl << "������������" << endl;
		cout << "\t\t  ------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|         1.ѧ������            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|         2.��    ʦ            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|         3.�� �� Ա            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|         0.��    ��            |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t  ------------------------------\n";
		cout << "����������ѡ��" << endl;
		cin >> select;
		switch (select)
		{
		case 1: // ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2: // ��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3: // ����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: // �˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "�������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	
	system("pause");
	return 0;
}