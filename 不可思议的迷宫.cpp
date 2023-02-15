#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
//不可思议的迷宫 Beta ver2.03
//作者：祝锦红 1229704185@qq.com
using namespace std;
int sx, sy;//全局变量sx,sy代表起点的坐标
int difficulty;
int x[4] = { 1,0,-1,0 };//表示x坐标的移动
int y[4] = { 0,-1,0,1 };//表示y坐标的移动
//生成迷宫的函数原型
char** mazeGenerator(int, int);
//输出迷宫信息的函数原型
void showMaze(char **, int, int);
//走迷宫的函数原型
void mazeTraverse(char**, int, int, int, int, int);
//展示游戏规则的函数原型
void Help();

int main()
{
	int m, n;
	int choose = 0;
Menu://Menu代表游戏菜单在程序中的坐标
	//setw(2)为了让界面更美观
	cout << setw(2) << "※欢迎来到zjh的不可思议迷宫^_^※\n\n";
	cout << setw(2) << "###################" << endl;
	cout << setw(2) << "###按下1进入游戏###" << endl;
	cout << setw(2) << "###按下2查看规则###" << endl;
	cout << setw(2) << "###按下0退出游戏###" << endl;
	cout << setw(2) << "#点击Enter完成输入#" << endl;
	cout << setw(2) << "###################" << endl;
Choose://Choose代表游戏主体在程序中的坐标
	cin >> choose;
	switch (choose)
	{
	case 1:
		cout << setw(2) << "###################" << endl;
		cout << setw(2) << "###请选择游戏难度##" << endl;
		cout << setw(2) << "###按下1选择简单###" << endl;
		cout << setw(2) << "###按下2选择困难###" << endl;
		cout << setw(2) << "#点击Enter完成输入#" << endl;
		cout << setw(2) << "###################" << endl;
	DifficultyChoose://DifficlutyChoose代表难度选择在程序中的坐标
		cin >> difficulty;
		switch (difficulty)
		{
		case 1:
			cout << setw(2) << "#######简  单#######" << endl;
			break;
		case 2:
			cout << setw(2) << "#######困  难#######" << endl;
			break;
		default:
			cout << "没有该选项，请重新输入：\n";
			goto DifficultyChoose;//回到难度选择
		}
		break;//直接进入游戏
	case 2:
		Help(); goto Menu;//返回游戏菜单
	case 0:
		cout << "欢迎下次游玩！\n\n";
		return 0;
	default:
		cout << "没有该选项，请重新输入：\n";
		goto Choose;//返回游戏选择
	}

	cout << setw(2) << "请输入迷宫的长和宽：(长和宽大于3)\n";
	LengthNWidth://选择长和宽
	while (cin >> n >> m)//正式开始循环
	{
		if (n <= 3 || m <= 3)
		{
			cout << "请输入大于3的长和宽：\n";
			goto LengthNWidth;
		}
		char** zjh = mazeGenerator(m, n);//zjh[][]表示迷宫的二维数组
		showMaze(zjh, m, n);//先展示这次随机生成的迷宫
		cout << "这是你本轮的迷宫\n";
		cin.get();//读取缓冲区字符
		int face = 0;//面朝方向初始化为右
		mazeTraverse(zjh, m, n, sx + 1, sy, face);//初始化坐标
		cout << "是否再来一局？（输入1表示是，0表示否，并回到菜单）\n";

	AnotherChoose://再次选择
		cin >> choose;
		switch (choose)
		{
		case 1:
			cout << setw(2) << "###################" << endl;
			cout << setw(2) << "###请选择游戏难度##" << endl;
			cout << setw(2) << "###按下1选择简单###" << endl;
			cout << setw(2) << "###按下2选择困难###" << endl;
			cout << setw(2) << "#点击Enter完成输入#" << endl;
			cout << setw(2) << "###################" << endl;

		AnotherDifficultyChoose:
			cin >> difficulty;
			switch (difficulty)
			{
			case 1:
				cout << setw(2) << "#######简  单#######" << endl;
				break;
			case 2:
				cout << setw(2) << "#######困  难#######" << endl;
				break;
			default:
				cout << "没有该选项，请重新输入：\n";
				goto AnotherDifficultyChoose;//回到难度选择
			}

			cout << setw(2) << "请输入迷宫的长和宽：\n"; break;
		case 0:
			system("cls"); goto Menu;//清屏并回到菜单
		default:
			cout << "没有该选项，请重新输入：\n";
			goto AnotherChoose;
			break;
		}
	}
}
char** mazeGenerator(int m, int n)
{
	//生成随机数
	srand(int(time(0)));
	//开辟二维动态数组 即m*n的迷宫
	//※为了方便后续处理，迷宫内各点坐标在(1~m,1~n)中
	//令迷宫外围的一圈为'#'，输出时不予显示
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
				//简单难度下，大概有2/3的空格填为通路 剩下默认不通
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
				//困难难度下，大概有1/2的空格填为通路 剩下默认不通
				if (rand() % 2 == 0) maze[i][j] = '.';
				else maze[i][j] = '#';
			}
		}
	}
	//加大难度，控制入口和出口的数量，这里将左侧和上侧封死
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
	//增强随机性，选择一个左上方的点作为入口，与上面对应
	bool x = false;//x==0代表还没选出来 x==1代表选出来了
FLAG:
	for (int i = 2; i <= m / 2; ++i)
	{
		for (int j = 1; j <= n / 2; ++j)
		{
			//(m/2-1)*(n/2)个点，每轮第一个点有1/(m*n)的概率选到
			if (rand() % (m*n) == 0)
			{
				maze[i][j] = 'X';
				x = true;//选出来了
				sx = j; sy = i;//起点坐标
				//为了游戏可行，我们要在初始时有一段通路和一段墙壁
				maze[i][j + 1] = maze[i][j + 2] = '.';
				maze[i + 1][j] = maze[i - 1][j] = maze[i][j - 1] = '#';
				return maze;
			}
		}
	}
	if (!x) goto FLAG;//没选出来就回到FLAG处，直到选出来
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
	/*nx,ny代表所在点坐标;f代表方向,f%4=0时向右,=1时向下,=2时向左,=3时向上*/
	//当前就在终点，则成功
	if ((nx == n || ny == m) && a[ny][nx] == '.')
	{
		cout << endl << "按回车键进行移动......";
		cin.get();
		a[ny][nx] = 'X';
		showMaze(a, m, n);
		cout << "成功走出迷宫\n";
		return;
	}
	else if (nx == sx && ny == sy)//回到起点了，失败
	{
		cout << endl << "按回车键进行移动......";
		cin.get();
		showMaze(a, m, n);
		cout << "回退到入口\n";
		return;
	}
	//不在终点时
	cout << endl;
	cout << "按回车键进行移动......";
	a[ny][nx] = 'O';//O表示当前所在的点
	cin.get();
	cout << endl;
	showMaze(a, m, n);
	a[ny][nx] = 'X';//标记为走过
	int nowx = nx, nowy = ny;
	//还有路，此时遵守“右手法则”，优先向右转，其次前进、再次左转、最后调头
	if (a[nowy + y[(f + 3) % 4]][nowx + x[(f + 3) % 4]] != '#')//右手边有路
	{
		f = (f + 3) % 4;//方向转换
		return mazeTraverse(a, m, n, nx + x[f], ny + y[f], f);//右转
	}
	//这边不考虑后方(倒退)，只有没路的时候才后退
	else if (a[nowy + y[f]][nowx + x[f]] != '#')//前面有路
	{
		return mazeTraverse(a, m, n, nx + x[f], ny + y[f], f);//保持不变，继续前进
	}
	else if (a[nowy + y[(f + 1) % 4]][nowx + x[(f + 1) % 4]] != '#')//左边有路
	{
		f = (f + 1) % 4;
		return mazeTraverse(a, m, n, nx + x[f], ny + y[f], f);//左转
	}
	//如果除了后方(走过的)，没有其他路了，就调头
	else
	{
		f = (f + 2) % 4;
		return mazeTraverse(a, m, n, nx + x[f], ny + y[f], f);
	}
}

void Help()
{
	cout << "\n游戏规则\n" << endl;
	cout << "这是一个自动走迷宫的程序\n" << "在设定难度进入游戏后，" << "你可以输入迷宫的长和宽来对迷宫规格进行调整\n";
	cout << "接着系统将会生成一个矩形迷宫，“ # ”表示墙壁，不可越过，“ . ”表示通路，可以通过，“ X ”表示已走过的路径\n";
	cout << "然后系统将会展示从起点开始自动寻找迷宫出口的路径\n";
	cout << "若到达了出口(即迷宫边缘的“ . ”)，则成功；若没到达出口，最终会返回起点，然后结束\n";
	cout << "另外，为了便于查看，我们用“ O ”表示当前所在的位置\n";
	cout << "最后，请愉快地享受这个朴素的程序吧！\n";
	system("pause");
	system("cls");
}
