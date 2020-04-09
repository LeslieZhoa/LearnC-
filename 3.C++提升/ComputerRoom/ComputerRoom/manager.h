#pragma once
#include "identity.h"
#include "student.h"
#include "teacher.h"


class Manager :public Identity {
public:
	// Ĭ�Ϲ���
	Manager();

	// �вι���
	Manager(string name, string pwd);

	// ѡ��˵�
	void openMenu();

	// ����˺�
	void addPerson();

	// �鿴�˺�
	void showPerson();

	// �鿴������Ϣ
	void showComputer();

	// ���ԤԼ
	void cleanFile();

	// ��ʼ������
	void initVector();

	// ����Ƿ����ظ�
	bool checkRepeat(int id, int type);

	// ѧ������
	vector<Student> vStu;

	// ��ʦ����
	vector<Teacher> vTea;

	// ��������
	vector<ComputerRoom> vCom;

};

void printStudent(Student & s);
void printTeacher(Teacher & t);