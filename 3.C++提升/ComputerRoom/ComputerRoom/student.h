#pragma once
#include "identity.h"

// ѧ����
class Student :public Identity {
public:
	// Ĭ�Ϲ���
	Student();

	// �вι���
	Student(int id, string name, string pwd);

	// �˵�ҳ��
	void openMenu();

	// ����ԤԼ
	void applyOrder();

	// �鿴�ҵ�ԤԼ
	void showMyOrder();

	// �鿴����ԤԼ
	void showAllOrder();

	// ȡ��ԤԼ
	void cancelOrder();

	// ѧ��ѧ��
	int m_Id;

	// ��������
	vector<ComputerRoom> vCom;

};