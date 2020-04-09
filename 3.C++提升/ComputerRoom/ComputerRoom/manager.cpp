#include "manager.h"

// Ĭ�Ϲ���
Manager::Manager() {

}

// �вι���
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->initVector();

	// ��ȡ������Ϣ
	ifstream ifs(COMPUTER_FILE);
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
		vCom.push_back(c);
	// cout << "��ǰ����������" << vCom.size() << endl;
	ifs.close();
}

// ѡ��˵�
void Manager::openMenu() {
	cout << "��ӭ����Ա��" << this->m_Name << "��½��" << endl;
	cout << "\t\t  ------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         1.����˺�            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         2.�鿴�˺�            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         3.�鿴����            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         4.���ԤԼ            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|         0.ע����½            |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t  ------------------------------\n";
	cout << "���������Ĳ�����" << endl;

}

// ����˺�
void Manager::addPerson() {
	cout << "����������˺�����" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.�����ʦ" << endl;
	string fileName;
	string tip;
	ofstream ofs;

	int select = 0;
	cin >> select;
	bool ret;
	string errorTip; // �ظ���ʾ
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errorTip = "ѧ���ظ�������������";
	}
	else {
		fileName = TEACHER_FILE;
		tip = "������ְ����ţ�";
		errorTip = "ְ�����ظ�������������";
	}
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (1) {
		cin >> id;
		if (select == 1)
			ret = this->checkRepeat(id, 1);
		else
			 ret = this->checkRepeat(id, 2);
		if (ret) {
			cout << errorTip << endl;
		}
		else {
			break;
		}
	}
	
	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
}


// ��ʼ������
void Manager::initVector() {
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	vStu.clear();
	vTea.clear();

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();

	// ��ȡ��ʦ��Ϣ
	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
	ifs.close();

}

// ����Ƿ����ظ�
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		for (auto it : vStu) {
			if (id == it.m_Id)
				return true;
		}
	}
	else {
		for (auto it : vTea) {
			if (id == it.m_EmpId)
				return true;
		}
	}
	return false;
}

// �鿴�˺�
void Manager::showPerson() {
	cout << "��ѡ��鿴����" << endl;
	cout << "1.�鿴����ѧ��" << endl;
	cout << "2.�鿴������ʦ" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else {
		cout << "������ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

// �鿴������Ϣ
void Manager::showComputer() {
	cout << "������Ϣ���£�" << endl;
	for (auto it : vCom) {
		cout << "������ţ�" << it.m_ComId << " �������������" << it.m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

// ���ԤԼ
void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ�" << endl;
	system("pause");
	system("cls");
}

void printStudent(Student & s) {
	cout << "ѧ��: " << s.m_Id << "������" << s.m_Name << "���룺" << s.m_Pwd << endl;
}
void printTeacher(Teacher & t) {
	cout << "ְ����: " << t.m_EmpId << "������" << t.m_Name << "���룺" << t.m_Pwd << endl;
}