#pragma once
#include "identity.h"

class Teacher :public Identity {
public:
	// Ĭ�Ϲ���
	Teacher();

	// �вι���
	Teacher(int id, string name, string pwd);

	// �˵�ҳ��
	void openMenu();

	// �鿴����ԤԼ
	void showAllOrder();

	// ���ԤԼ
	void validOrder();

	int m_EmpId; // ��ʦ���
};