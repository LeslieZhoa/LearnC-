#pragma once
#include<iostream>
using namespace std;
#include "worker.h"

#include <fstream>
#define FILENAME "empFile.csv"
class WorkerManager {
public:
	WorkerManager();

	//չʾ�˵�
	void Show_Menu();

	// �˳�ϵͳ
	void ExitSystem();

	//��¼Ա������
	int m_EmpNum;


	//ְ������ָ��
	Worker ** m_EmpArray;

	//���ְ��
	void Add_Emp();

	// �����ļ�
	void save();

	// �ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	// ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	// ��ʾְ��
	void Show_Emp();

	// ɾ��Ա��
	void Del_Emp();
	
	// �ж�ְ���Ƿ����
	int IsExist(int id);

	// �޸�ְ��
	void Mod_Emp();

	//����Ա��
	void Find_Emp();

	// ����
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	~WorkerManager();
};

//��ȡcsv
string Trim(string& str);