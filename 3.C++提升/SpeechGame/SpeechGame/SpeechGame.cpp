# include<iostream>
# include"speechManager.h"
using namespace std;
# include <string>

int main() {
	// ����������
	SpeechManager sm;

	int choice = 0;
	while (1) {
		
		sm.showMenu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //��ʼ����
			sm.startSpeech();
			break;
		case 2: //�鿴�����¼
			sm.showRecord();
			break;
		case 3: // ��ռ�¼
			sm.clearRecord();
			break;
		case 0: // �˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}