#include "speechManager.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<ctime>
// ���캯��
SpeechManager::SpeechManager() {
	// ��ʼ����������
	this->initSpeech();

	// ����ѡ��
	this->createSpeaker();

	// ��ȡ�����¼
	this->loadRecord();
}

// ��ʼ������������
void SpeechManager::initSpeech() {
	// �������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();

	// ��ʼ�������ִ�
	this->m_Index = 1;
}

// ��ʾ�˵�
void SpeechManager::showMenu() {
	cout << "******************************************" << endl;
	cout << "************ ��ӭ�μ��ݽ����� ************" << endl;
	cout << "************  1.��ʼ�ݽ�����  ************" << endl;
	cout << "************  2.�鿴�����¼  ************" << endl;
	cout << "************  3.��ձ�����¼  ************" << endl;
	cout << "************  0.�˳���������  ************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}

// �˳�ϵͳ
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//����ѡ��
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}

		// ����ѡ�ֱ��
		this->v1.push_back(i + 10001);

		// ѡ�ֱ�Ŷ�Ӧѡ��
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}


void SpeechManager::startSpeech() {
	// ��һ�ֱ���

	// ��ǩ
	this->speechDraw();

	// ����
	this->speechContest();

	// ��ʾ�������
	this->showScore();

	// �ڶ��ֱ���
	this->m_Index++;
	// ��ǩ
	this->speechDraw();

	// ����
	this->speechContest();

	// ��ʾ���ս��
	this->showScore();
	// ���������ļ�
	this->saveRecord();

	// ���ñ���
	// ��ʼ����������
	this->initSpeech();

	// ����ѡ��
	this->createSpeaker();

	// ��ȡ�����¼
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

// ��ǩ
void  SpeechManager::speechDraw() {
	srand((unsigned int) time(NULL));
	cout << "�� " << this->m_Index << " �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1) {
		// ��һ��
		random_shuffle(v1.begin(), v1.end());
		for (auto it : v1) {
			cout << it << " ";
		}
		cout << endl;
	}
	else {
		// �ڶ���
		random_shuffle(v2.begin(), v2.end());
		for (auto it : v2) {
			cout << it << " ";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------------" << endl;
	system("pause");
	cout << endl;
	
}

// ����
void SpeechManager::speechContest() {
	srand((unsigned int)time(NULL));
	cout << "----------�� " << this->m_Index << " �ֱ���ѡ�����ڳ�ǩ----------" << endl;

	// ��ʱ�������С��ɼ�
	multimap<double, int, greater<double>> groupScore;

	int num = 0;// ��¼��Ա������6��һ��

	vector<int>v_Src; // ����ѡ������
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	// ��������ѡ�ֽ��б���
	for (auto it : v_Src) {

		num++;
		// ��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>()); // ��������
		d.pop_back(); // ȥ����ͷ�
		d.pop_front(); // ȥ����߷�

		double sum = accumulate(d.begin(), d.end(), 0.f);
		double avg = sum / (double)d.size(); // ��ƽ����

		// ��ӡƽ����
		// cout << "��ţ� " << it << "������" << this->m_Speaker[it].m_Name << "�÷֣�" << avg << endl;

		// ��ƽ���ַ���map������
		this->m_Speaker[it].m_Score[this->m_Index - 1] = avg;

		// ��������ݷ�����ʱС��������
		groupScore.insert(make_pair(avg, it));
		// ÿ6��ȡ��ǰ����
		if (num % 6 == 0) {
			cout << "�� " << num / 6 << " С��������Σ�" << endl;
			for (auto mt : groupScore) {
				cout << "��ţ� " << mt.second << "����: " << this->m_Speaker[mt.second].m_Name
					<< "�ɼ���" << this->m_Speaker[mt.second].m_Score[this->m_Index - 1] << endl;
			}
			
			// ȡ��ǰ����
			int count = 0;
			for (auto mt : groupScore) {
				if (count < 3) {
					if (this->m_Index == 1) {
						v2.push_back(mt.second);
					}
					else
						vVictory.push_back(mt.second);
					count += 1;
				}
				else
					break;
			}
			// С���������
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "----------�� " << this->m_Index << " �ֱ������----------" << endl;
	system("pause");
}

// ��ʾ�÷�
void SpeechManager::showScore() {
	cout << "----------�� " << this->m_Index << " �ֽ���ѡ����Ϣ����----------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
		v = v2;
	else
		v = vVictory;
	for (auto it : v) {
		cout << "ѡ�ֱ�ţ�" << it << "������" << this->m_Speaker[it].m_Name 
			<< "�÷֣�" << this->m_Speaker[it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	// if (this->m_Index == 1)
	this->showMenu();
}

// �ж��ļ��Ƿ�Ϊ��
bool SpeechManager::is_File() {
	// �ļ������ڻ��ļ�Ϊ��
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (ifs.is_open()) {
		char ch;
		ifs >> ch;
		if (!ifs.eof()) {
			ifs.close();
			return true; // �ļ�������
		}

	}
	ifs.close();
	return false; // ���ļ���û����
}

// �鿴���м�������
int SpeechManager::CountNum() {
	int num = 0;
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	string line;

	while (getline(ifs, line)) {
		num++;
	}
	num -= 1;

	
	return num/3;
}

// �������
void SpeechManager::saveRecord() {
	
	int num = 0;
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	if (!this->is_File()) {
		ofs << " " << "," << "ѡ�ֱ��" << "," << "ѡ������" << "," << "ѡ�ַ���" << endl;
	}
	else
		num = this->CountNum();
	ofs << "��" << num + 1 << "��";
	int cnt = 0;
	for (auto it : vVictory) {
		if (cnt == 0)
			ofs << "," << it << "," << this->m_Speaker[it].m_Name << "," << this->m_Speaker[it].m_Score[1] << endl;
		else
			ofs << " " << "," << it << "," << this->m_Speaker[it].m_Name << "," << this->m_Speaker[it].m_Score[1] << endl;
		cnt++;
	}
	ofs.close();
	cout << "��¼�ѱ���" << endl;
}

// ��ȡ��¼
void SpeechManager::loadRecord() {
	if (!this->is_File()) {
		// cout << "�ļ�Ϊ�ջ򲻴���" << endl;
		return;
	}
	vector<vector<string>>v; // ���3��ѡ������
	vector<string> v1; // ���ÿ��ѡ������
	ifstream ifs(FILENAME);
	string line;
	int index = 0;
	string Num;
	while (getline(ifs, line)) {

		istringstream sin(line);
		vector<string> fields;
		string field;
		if (index > 0) {
			while (getline(sin, field, ',')) {
				fields.push_back(field);
			}
			if ((index-1)%3 == 0)
				Num = Trim(fields[0]);
			
			string id = Trim(fields[1]);
			v1.push_back(id);
			string name = Trim(fields[2]);
			v1.push_back(name);
			string score = Trim(fields[3]);
			v1.push_back(score);
			v.push_back(v1);
			v1.clear();
			if (index % 3 == 0) {
				if (index != 0) {
					m_Record.insert(make_pair(Num, v));
					v.clear();
				}

			}
		}
		index++;
	}
	ifs.close();
}

// �鿴����
void SpeechManager::showRecord() {
	if (!this->is_File()) {
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (auto it : this->m_Record) {
		cout << "---------------" << it.first << "---------------" << endl;
		cout << "�ھ���ţ�" << it.second[0][0] << "������" << it.second[0][1] << "�÷֣�" << it.second[0][2] << endl;
		cout << "�Ǿ���ţ�" << it.second[1][0] << "������" << it.second[1][1] << "�÷֣�" << it.second[1][2] << endl;
		cout << "������ţ�" << it.second[2][0] << "������" << it.second[2][1] << "�÷֣�" << it.second[2][2] << endl;

	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadRecord();

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

// ��������
SpeechManager::~SpeechManager() {

}

// ��ȡcsv
string Trim(string& str)
{
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}