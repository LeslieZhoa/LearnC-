#pragma once
#include<iostream>
#include<fstream>
#include "globalFile.h"
#include<string>
#include<vector>
#include<algorithm>
#include "computerRoom.h"
#include "orderFile.h"
using namespace std;

// ��������
class Identity {
public:
	// �����˵�
	virtual void openMenu() = 0;

	string m_Name; // �û���
	string m_Pwd; //�û�����
};