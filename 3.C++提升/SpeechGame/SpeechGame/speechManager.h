#pragma once
# include<iostream>
# include<string>
using namespace std;
# include<vector>
# include<map>
# include"speaker.h"
#include <sstream>
# include<fstream>

#define FILENAME "speech.csv"

class SpeechManager {
public:
	//����
	SpeechManager();

	// ��ʼ������������
	void initSpeech();

	// ��ʾ�˵�
	void showMenu();

	// �˳�ϵͳ
	void exitSystem();

	//����ѡ��
	void createSpeaker();

	// �������̿���
	void startSpeech();

	// ��ǩ
	void speechDraw();

	// ����
	void speechContest();

	// ��ʾ�÷�
	void showScore();

	// �������
	void saveRecord();

	// �ж��ļ��Ƿ�Ϊ��
	bool is_File();

	// �鿴���м�������
	int CountNum();

	// ��ȡ��¼
	void loadRecord();

	// �鿴����
	void showRecord();

	// ��ռ�¼
	void clearRecord();

	// ��������¼����
	map<string, vector<vector<string>>>m_Record;

	// ��Ա����
	// �����һ��ѡ�ֱ�š�
	vector<int> v1;

	// ��һ��ѡ�ֽ������
	vector<int> v2;

	// ʤ��ǰ�������
	vector<int>vVictory;

	// ��ű���Լ���Ӧѡ��
	map<int, Speaker> m_Speaker;

	// ��ű����ִ�
	int m_Index;

	//����
	~SpeechManager();
};

//��ȡcsv
string Trim(string& str);