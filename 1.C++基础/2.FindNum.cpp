# include <iostream>
# include <string>
using namespace std;


int main()
{
	// ������������´�С

	// ���������
	int num = rand() % 100;
	int val = 0;
	cin >> val;
	while (val != num)
	{
		if (val > num)
		{
			cout << "�´���" << endl;
		}
		else
		{
			cout << "��С��" << endl;
		}
		cin >> val;
	}
	cout << "�¶���Ӵ" << endl;

	

	system("pause");
	return 0;

}