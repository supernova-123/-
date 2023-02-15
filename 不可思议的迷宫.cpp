#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
//����˼����Թ� Beta ver2.03
//���ߣ�ף���� 1229704185@qq.com
using namespace std;
int sx, sy;//ȫ�ֱ���sx,sy������������
int difficulty;
int x[4] = { 1,0,-1,0 };//��ʾx������ƶ�
int y[4] = { 0,-1,0,1 };//��ʾy������ƶ�
//�����Թ��ĺ���ԭ��
char** mazeGenerator(int, int);
//����Թ���Ϣ�ĺ���ԭ��
void showMaze(char **, int, int);
//���Թ��ĺ���ԭ��
void mazeTraverse(char**, int, int, int, int, int);
//չʾ��Ϸ����ĺ���ԭ��
void Help();

int main()
{
	int m, n;
	int choose = 0;
Menu://Menu������Ϸ�˵��ڳ����е�����
	//setw(2)Ϊ���ý��������
	cout << setw(2) << "����ӭ����zjh�Ĳ���˼���Թ�^_^��\n\n";
	cout << setw(2) << "###################" << endl;
	cout << setw(2) << "###����1������Ϸ###" << endl;
	cout << setw(2) << "###����2�鿴����###" << endl;
	cout << setw(2) << "###����0�˳���Ϸ###" << endl;
	cout << setw(2) << "#���Enter�������#" << endl;
	cout << setw(2) << "###################" << endl;
Choose://Choose������Ϸ�����ڳ����е�����
	cin >> choose;
	switch (choose)
	{
	case 1:
		cout << setw(2) << "###################" << endl;
		cout << setw(2) << "###��ѡ����Ϸ�Ѷ�##" << endl;
		cout << setw(2) << "###����1ѡ���###" << endl;
		cout << setw(2) << "###����2ѡ������###" << endl;
		cout << setw(2) << "#���Enter�������#" << endl;
		cout << setw(2) << "###################" << endl;
	DifficultyChoose://DifficlutyChoose�����Ѷ�ѡ���ڳ����е�����
		cin >> difficulty;
		switch (difficulty)
		{
		case 1:
			cout << setw(2) << "#######��  ��#######" << endl;
			break;
		case 2:
			cout << setw(2) << "#######��  ��#######" << endl;
			break;
		default:
			cout << "û�и�ѡ����������룺\n";
			goto DifficultyChoose;//�ص��Ѷ�ѡ��
		}
		break;//ֱ�ӽ�����Ϸ
	case 2:
		Help(); goto Menu;//������Ϸ�˵�
	case 0:
		cout << "��ӭ�´����棡\n\n";
		return 0;
	default:
		cout << "û�и�ѡ����������룺\n";
		goto Choose;//������Ϸѡ��
	}

	cout << setw(2) << "�������Թ��ĳ��Ϳ�(���Ϳ����3)\n";
	LengthNWidth://ѡ�񳤺Ϳ�
	while (cin >> n >> m)//��ʽ��ʼѭ��
	{
		if (n <= 3 || m <= 3)
		{
			cout << "���������3�ĳ��Ϳ�\n";
			goto LengthNWidth;
		}
		char** zjh = mazeGenerator(m, n);//zjh[][]��ʾ�Թ��Ķ�ά����
		showMaze(zjh, m, n);//��չʾ���������ɵ��Թ�
		cout << "�����㱾�ֵ��Թ�\n";
		cin.get();//��ȡ�������ַ�
		int face = 0;//�泯�����ʼ��Ϊ��
		mazeTraverse(zjh, m, n, sx + 1, sy, face);//��ʼ������
		cout << "�Ƿ�����һ�֣�������1��ʾ�ǣ�0��ʾ�񣬲��ص��˵���\n";

	AnotherChoose://�ٴ�ѡ��
		cin >> choose;
		switch (choose)
		{
		case 1:
			cout << setw(2) << "###################" << endl;
			cout << setw(2) << "###��ѡ����Ϸ�Ѷ�##" << endl;
			cout << setw(2) << "###����1ѡ���###" << endl;
			cout << setw(2) << "###����2ѡ������###" << endl;
			cout << setw(2) << "#���Enter�������#" << endl;
			cout << setw(2) << "###################" << endl;

		AnotherDifficultyChoose:
			cin >> difficulty;
			switch (difficulty)
			{
			case 1:
				cout << setw(2) << "#######��  ��#######" << endl;
				break;
			case 2:
				cout << setw(2) << "#######��  ��#######" << endl;
				break;
			default:
				cout << "û�и�ѡ����������룺\n";
				goto AnotherDifficultyChoose;//�ص��Ѷ�ѡ��
			}

			cout << setw(2) << "�������Թ��ĳ��Ϳ�\n"; break;
		case 0:
			system("cls"); goto Menu;//�������ص��˵�
		default:
			cout << "û�и�ѡ����������룺\n";
			goto AnotherChoose;
			break;
		}
	}
}
char** mazeGenerator(int m, int n)
{
	//���������
	srand(int(time(0)));
	//���ٶ�ά��̬���� ��m*n���Թ�
	//��Ϊ�˷�����������Թ��ڸ���������(1~m,1~n)��
	//���Թ���Χ��һȦΪ'#'�����ʱ������ʾ
	char** maze = new char*[m + 1];
	for (int i = 0; i <= m + 1; ++i)
	{
		maze[i] = new char[n + 1];
	}
	if (difficulty == 1)
	{
		for (int i = 1; i <= m; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				//���Ѷ��£������2/3�Ŀո���Ϊͨ· ʣ��Ĭ�ϲ�ͨ
				if (rand() % 3 == 0) maze[i][j] = '#';
				else maze[i][j] = '.';
			}
		}
	}
	else if (difficulty == 2)
	{
		for (int i = 1; i <= m; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				//�����Ѷ��£������1/2�Ŀո���Ϊͨ· ʣ��Ĭ�ϲ�ͨ
				if (rand() % 2 == 0) maze[i][j] = '.';
				else maze[i][j] = '#';
			}
		}
	}
	//�Ӵ��Ѷȣ�������ںͳ��ڵ����������ｫ�����ϲ����
	for (int i = 0; i <= m + 1; ++i)
	{
		maze[i][0] = '#';
		maze[i][1] = '#';
	}
	for (int j = 0; j <= n + 1; ++j)
	{
		maze[0][j] = '#';
		maze[1][j] = '#';
	}
	//��ǿ����ԣ�ѡ��һ�����Ϸ��ĵ���Ϊ��ڣ��������Ӧ
	bool x = false;//x==0����ûѡ���� x==1����ѡ������
FLAG:
	for (int i = 2; i <= m / 2; ++i)
	{
		for (int j = 1; j <= n / 2; ++j)
		{
			//(m/2-1)*(n/2)���㣬ÿ�ֵ�һ������1/(m*n)�ĸ���ѡ��
			if (rand() % (m*n) == 0)
			{
				maze[i][j] = 'X';
				x = true;//ѡ������
				sx = j; sy = i;//�������
				//Ϊ����Ϸ���У�����Ҫ�ڳ�ʼʱ��һ��ͨ·��һ��ǽ��
				maze[i][j + 1] = maze[i][j + 2] = '.';
				maze[i + 1][j] = maze[i - 1][j] = maze[i][j - 1] = '#';
				return maze;
			}
		}
	}
	if (!x) goto FLAG;//ûѡ�����ͻص�FLAG����ֱ��ѡ����
}
void showMaze(char **a, int m, int n)
{
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			cout << setw(2) << a[i][j];
		}
		cout << '\n';
	}
}

void mazeTraverse(char**a, int m, int n, int nx, int ny, int f)
{
	/*nx,ny�������ڵ�����;f������,f%4=0ʱ����,=1ʱ����,=2ʱ����,=3ʱ����*/
	//��ǰ�����յ㣬��ɹ�
	if ((nx == n || ny == m) && a[ny][nx] == '.')
	{
		cout << endl << "���س��������ƶ�......";
		cin.get();
		a[ny][nx] = 'X';
		showMaze(a, m, n);
		cout << "�ɹ��߳��Թ�\n";
		return;
	}
	else if (nx == sx && ny == sy)//�ص�����ˣ�ʧ��
	{
		cout << endl << "���س��������ƶ�......";
		cin.get();
		showMaze(a, m, n);
		cout << "���˵����\n";
		return;
	}
	//�����յ�ʱ
	cout << endl;
	cout << "���س��������ƶ�......";
	a[ny][nx] = 'O';//O��ʾ��ǰ���ڵĵ�
	cin.get();
	cout << endl;
	showMaze(a, m, n);
	a[ny][nx] = 'X';//���Ϊ�߹�
	int nowx = nx, nowy = ny;
	//����·����ʱ���ء����ַ��򡱣���������ת�����ǰ�����ٴ���ת������ͷ
	if (a[nowy + y[(f + 3) % 4]][nowx + x[(f + 3) % 4]] != '#')//���ֱ���·
	{
		f = (f + 3) % 4;//����ת��
		return mazeTraverse(a, m, n, nx + x[f], ny + y[f], f);//��ת
	}
	//��߲����Ǻ�(����)��ֻ��û·��ʱ��ź���
	else if (a[nowy + y[f]][nowx + x[f]] != '#')//ǰ����·
	{
		return mazeTraverse(a, m, n, nx + x[f], ny + y[f], f);//���ֲ��䣬����ǰ��
	}
	else if (a[nowy + y[(f + 1) % 4]][nowx + x[(f + 1) % 4]] != '#')//�����·
	{
		f = (f + 1) % 4;
		return mazeTraverse(a, m, n, nx + x[f], ny + y[f], f);//��ת
	}
	//������˺�(�߹���)��û������·�ˣ��͵�ͷ
	else
	{
		f = (f + 2) % 4;
		return mazeTraverse(a, m, n, nx + x[f], ny + y[f], f);
	}
}

void Help()
{
	cout << "\n��Ϸ����\n" << endl;
	cout << "����һ���Զ����Թ��ĳ���\n" << "���趨�ѶȽ�����Ϸ��" << "����������Թ��ĳ��Ϳ������Թ������е���\n";
	cout << "����ϵͳ��������һ�������Թ����� # ����ʾǽ�ڣ�����Խ������ . ����ʾͨ·������ͨ������ X ����ʾ���߹���·��\n";
	cout << "Ȼ��ϵͳ����չʾ����㿪ʼ�Զ�Ѱ���Թ����ڵ�·��\n";
	cout << "�������˳���(���Թ���Ե�ġ� . ��)����ɹ�����û������ڣ����ջ᷵����㣬Ȼ�����\n";
	cout << "���⣬Ϊ�˱��ڲ鿴�������á� O ����ʾ��ǰ���ڵ�λ��\n";
	cout << "�������������������صĳ���ɣ�\n";
	system("pause");
	system("cls");
}
