#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct User {
	char Account[19];
	string Name;
	string ID;
	int Password;
	//金额，限制均可自由修改
	long long Money = 10000;
	long long daylimit = 100000;
	long long limit = 1000;
} users[10000000];
//用户个数
int num = 0;
//提前声明功能大厅
void functionhall();
//提前声明主菜单
void mainmenu();
//提前声明获取函数
void getuser();

//储存用户信息
void Userinf() {
	FILE *user;
	user = fopen("userlist.txt", "rw+");
	if (user == NULL) {
		cout << "用户信息储存失败！";
	} else {
		for (int i = 1; i <= num; i++) {
			fwrite(&users[i], sizeof(struct User), 1, user);
		}
	}
	fclose(user);
}

//创建用户（实际上为记录用户信息）
void create_user() {
	getuser();
	printf("================创建新用户================\n") ;
	int id = num + 1;
	num = id;
	printf("=======输入新账号（默认19位仅数字）=======\n") ;
	while (1) {
		char h[19];//临时记录账号
		while (1) {
			cin >> h;
			if (strlen(h) != 19) {
				printf("======账号需为19位纯数字！请重新输入======\n") ;
			} else {
				break;
			}
		}
		int count = 0;
		for (int i = 1; i <= num; i++) {
			count = 0;
			for (int j = 0; j < 19; j++) {
				if (users[i].Account[j] == h[j]) {
					count++;
				}
			}
			if (count == 19) {
				printf("=======该账号已经存在，请重新输入！=======\n");
				break;
			}
		}
		if (count != 19) {
			for (int t = 0; t < 19; t++) {
				users[id].Account[t] = h[t];
			}
			break;
		}
	}
	printf("===============输入您的姓名===============\n") ;
	cin >> users[id].Name;
	printf("=============输入您的身份证号=============\n") ;
	cin >> users[id].ID;
	while (1) {
		printf("======输入您的密码（默认为6位仅数字）=====\n") ;
		int l;
		cin >> l;
		if (l > 999999 || l < 100000) {
			printf("======密码格式错误（默认为6位仅数字）=====\n") ;
		} else {
			users[id].Password = l;
			break;
		}
	}
	printf("============请再次输入您的密码============\n") ;
	while (1) {
		int password01;
		cin >> password01;
		if (password01 == users[id].Password) {
			getchar();
			printf("=========创建账户成功感谢您的使用=========\n");
			printf("===========输入0进入主菜单登录!===========\n");
			Sleep(390);
			break;
		} else {
			printf("===========密码不一致请重新输入===========\n");
		}
	}
	Userinf();//储存用户信息
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		mainmenu();
	}
}

//获取账户
void getuser() {
	num = 0;
	FILE *user;
	user = fopen("userlist.txt", "r");
	if (user == NULL) {
		cout << "用户信息获取失败！";
	} else {
		while (!feof(user)) {
			fread(&users[++num], sizeof(struct User), 1, user);
		}
	}
	fclose(user);
	num--;
}
int user_num = 0; //查询，转账，取款，修改密码记录客户编号

//主菜单
void mainmenu() {
	getuser();
	printf("=欢迎使用中国农业银行重庆大学虎溪校区分行=\n");
	printf("=============选择服务前请插卡=============\n");
	Sleep(390);
	printf("=================正在读卡=================\n");
	Sleep(390);
	printf("===========读卡成功！请输入账号===========\n");
	int psw;
	char n[19];
	while (1) {
		int m = 0;
		cin >> n;
		for (int i = 1; i <= num; i++) {
			m = 0;
			for (int j = 0; j < 19; j++) {
				if (users[i].Account[j] == n[j]) {
					m++;
				}
			}
			if (m == 19) {
				psw = users[i].Password;
				user_num = i; //标注出操作用户，方便后续更改密码转账查询直接访问
				break;
			}
		}
		if (m != 19) {
			printf("======未查询到账号，请检查后重新输入！=====\n");
		} else {
			printf("==============账号验证成功！==============\n");
			break;
		}
	}
	system("cls");
	printf("======请输入密码（您有三次输入机会）======\n");
	for (int i = 1; i <= 3; i++) {
		int a;
		cin >> a;
		if (a == psw) {
			printf("===验证密码成功！正在跳转功能界面。。。===\n");
			Sleep(390);
			system("cls");
			functionhall();
			break;
		} else if (i <= 2) {
			printf("=========验证密码错误！请再次输入=========\n");
		} else if (i == 3) {
			printf("=验证密码错误！请于次日带身份证于本行解锁=\n");
			printf("============正在退出系统。。。============\n");
			break;
		}
	}
}

//余额查询
void view() {
	getuser();
	printf("==============正在查询。。。==============\n");
	Sleep(390);
	cout << "您的账户余额为：" << users[user_num].Money << "元。" << endl;
	printf("============输入0返回功能大厅=============\n");
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		functionhall();
	}
}

//取款功能
void getmoney() {
	getuser();
	printf("=================正在准备=================\n");
	Sleep(390);
	printf("==请输入取款金额（金额需为100的整数倍）:==\n");
	while (1) {
		long long n;
		cin >> n;
		if (n > users[user_num].Money) {
			printf("======账户余额不足，请重新输入金额：======\n");
		} else if (n % 100 != 0) {
			printf("==请重新输入取款金额，金额应为100整数倍:==\n");
		} else if (n > users[user_num].limit) {
			printf("===您今日取款已超出单笔上限，请次日申请===\n");
		} else if (n > users[user_num].daylimit) {
			printf("=====您今日取款已超出上限，请次日取款=====\n");
		} else if (n <= users[user_num].limit && n % 100 == 0 && n <= users[user_num].Money && n <= users[user_num].daylimit) {
			users[user_num].Money = users[user_num].Money - n;
			users[user_num].daylimit = users[user_num].daylimit - n;
			printf("==========正在取款，请稍后。。。==========\n");
			Sleep(390);
			printf("================取款成功！================\n");
			break;
		}
	}
	Userinf();
	printf("============输入0返回功能大厅=============\n");
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		functionhall();
	}
}
int y;//标记转账账户编号

//转账功能()
void transmoney() {
	getuser();
	printf("===============准备中。。。===============\n");
	Sleep(390);
	printf("============请输入转账用户账号============\n");
	char s[19];
	//string s;
	while (1) {
		char e[19];
		//string e;
		cin >> e;
		int flag0 = 0;
		for (int i = 1; i <= num; i++) {
			flag0 = 0;
			for (int j = 0; j < 19; j++) {
				if (users[i].Account[j] == e[j]) {
					flag0++;
				}
			}
			if (flag0 == 19) {
				for (int o = 0; o < 19; o++) {
					s[o] = e[o];
				}
				//s = e;
				y = i;
				break;
			}
		}
		if (flag0 != 19) {
			printf("======该账号不存在，请检查后重新输入======\n");
		} else {
			break;
		}
	}
	printf("===========请再次输入账号并确认===========\n");
	while (1) {
		char E[19];
		cin >> E;
		int count2 = 0;
		for (int j = 0; j < 19; j++) {
			if (E[j] == s[j]) {
				count2++;
			}
		}
		if (count2 != 19) {
			printf("=====两次账号不一致，请检查后重新输入=====\n");
		} else {
			printf("===请输入转账金额:（金额需为100整数倍）===\n");
			break;
		}
	}
	while (1) {
		long long g;
		cin >> g;
		if (g > users[user_num].Money) {
			printf("======账户余额不足，请重新输入金额：======\n");
		} else if (g % 100 != 0) {
			printf("==请重新输入转账金额，金额应为100整数倍:==\n");
		} else if (g > users[user_num].limit) {
			printf("===您今日转账已超出单笔上限，请次日申请===\n");
		} else if (g > users[user_num].daylimit) {
			printf("===您今日消费总额已超出上限，请次日转账===\n");
		} else if (g <= users[user_num].limit && g % 100 == 0 && g <= users[user_num].Money && g <= users[user_num].daylimit) {
			users[user_num].Money = users[user_num].Money - g;
			users[user_num].daylimit = users[user_num].daylimit - g;
			users[y].Money = users[y].Money + g;
			printf("==========正在转账，请稍后。。。==========\n");
			Sleep(390);
			printf("================转账成功！================\n");
			break;
		}
	}
	Userinf();
	printf("============输入0返回功能大厅=============\n");
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		functionhall();
	}
}

//修改密码
void changepsw() {
	getuser();
	printf("=================正在准备=================\n");
	printf("===============请输入原密码===============\n");
	while (1) {
		int b;
		cin >> b;
		if (b != users[user_num].Password) {
			printf("========密码输入错误！请输入原密码========\n");
		} else {
			printf("===============请输入新密码===============\n");
			break;
		}
	}
	int B;
	cin >> B;
	printf("==============请再次输入密码==============\n");
	while (1) {
		int C;
		cin >> C;
		if (C != B) {
			printf("=======密码输入错误！请再次输入密码=======\n");
		} else {
			printf("==============密码修改成功！==============\n");
			break;
		}
	}
	users[user_num].Password = B;
	Userinf();
	printf("============输入0返回功能大厅=============\n");
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		functionhall();
	}
}

//功能界面
void functionhall() {
	getuser();
	printf("=欢迎来到功能大厅！请选择服务选项前数字：=\n");
	printf("================[1]余额查询===============\n");
	printf("================[2]取款功能===============\n");
	printf("================[3]转账功能===============\n");
	printf("================[4]修改密码===============\n");
	printf("================[5]创建账户===============\n");
	printf("================[6]退出大厅===============\n");
	printf("================[7]重新登录===============\n");
	int n;
	cin >> n;
	switch (n) {
		case 1:
			printf("===========正在跳转请稍后。。。===========\n");
			Sleep(390);
			system("cls");
			view();
			break;
		case 2:
			printf("===========正在跳转请稍后。。。===========\n");
			Sleep(390);
			system("cls");
			getmoney();
			break;
		case 3:
			printf("===========正在跳转请稍后。。。===========\n");
			Sleep(390);
			system("cls");
			transmoney();
			break;
		case 4:
			printf("===========正在跳转请稍后。。。===========\n");
			Sleep(390);
			system("cls");
			changepsw();
			break;
		case 5:
			printf("===========正在跳转请稍后。。。===========\n");
			Sleep(390);
			system("cls");
			create_user();
			break;
		case 6:
			printf("===========正在退卡请稍后。。。===========\n");
			Sleep(390);
			system("cls");
			printf("=====感谢您的使用！期待下次您的光临！=====\n");
			break;
		case 7:
			printf("===========正在跳转请稍后。。。===========\n");
			Sleep(390);
			system("cls");
			mainmenu();
			break;
	}
}

int main() {
	Userinf();
	FILE *fp;
	fp = fopen("userlist.txt", "r");
	getuser();
	printf("+=========================================+\n");
	printf("|=      中国农业银行重庆大学虎溪分行     =|\n");
	printf("|=                                       =|\n");
	printf("|=                                       =|\n");
	printf("|=           =欢迎使用ATM柜台机=         =|\n");
	printf("|=           =输入1注册新用户!=          =|\n");
	printf("|=              =输入2登录=              =|\n");
	printf("|=                                       =|\n");
	printf("|=                                       =|\n");
	printf("+=========================================+\n");
	int j;
	cin >> j;
	system("cls");
	//登录界面
	if (j == 1) {
		create_user();
	} else if (j == 2) {
		mainmenu();
	}
	Userinf();
	return 0;
}