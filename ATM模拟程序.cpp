#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct User {
	char Account[19];
	string Name;
	string ID;
	int Password;
	//�����ƾ��������޸�
	long long Money = 10000;
	long long daylimit = 100000;
	long long limit = 1000;
} users[10000000];
//�û�����
int num = 0;
//��ǰ�������ܴ���
void functionhall();
//��ǰ�������˵�
void mainmenu();
//��ǰ������ȡ����
void getuser();

//�����û���Ϣ
void Userinf() {
	FILE *user;
	user = fopen("userlist.txt", "rw+");
	if (user == NULL) {
		cout << "�û���Ϣ����ʧ�ܣ�";
	} else {
		for (int i = 1; i <= num; i++) {
			fwrite(&users[i], sizeof(struct User), 1, user);
		}
	}
	fclose(user);
}

//�����û���ʵ����Ϊ��¼�û���Ϣ��
void create_user() {
	getuser();
	printf("================�������û�================\n") ;
	int id = num + 1;
	num = id;
	printf("=======�������˺ţ�Ĭ��19λ�����֣�=======\n") ;
	while (1) {
		char h[19];//��ʱ��¼�˺�
		while (1) {
			cin >> h;
			if (strlen(h) != 19) {
				printf("======�˺���Ϊ19λ�����֣�����������======\n") ;
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
				printf("=======���˺��Ѿ����ڣ����������룡=======\n");
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
	printf("===============������������===============\n") ;
	cin >> users[id].Name;
	printf("=============�����������֤��=============\n") ;
	cin >> users[id].ID;
	while (1) {
		printf("======�����������루Ĭ��Ϊ6λ�����֣�=====\n") ;
		int l;
		cin >> l;
		if (l > 999999 || l < 100000) {
			printf("======�����ʽ����Ĭ��Ϊ6λ�����֣�=====\n") ;
		} else {
			users[id].Password = l;
			break;
		}
	}
	printf("============���ٴ�������������============\n") ;
	while (1) {
		int password01;
		cin >> password01;
		if (password01 == users[id].Password) {
			getchar();
			printf("=========�����˻��ɹ���л����ʹ��=========\n");
			printf("===========����0�������˵���¼!===========\n");
			Sleep(390);
			break;
		} else {
			printf("===========���벻һ������������===========\n");
		}
	}
	Userinf();//�����û���Ϣ
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		mainmenu();
	}
}

//��ȡ�˻�
void getuser() {
	num = 0;
	FILE *user;
	user = fopen("userlist.txt", "r");
	if (user == NULL) {
		cout << "�û���Ϣ��ȡʧ�ܣ�";
	} else {
		while (!feof(user)) {
			fread(&users[++num], sizeof(struct User), 1, user);
		}
	}
	fclose(user);
	num--;
}
int user_num = 0; //��ѯ��ת�ˣ�ȡ��޸������¼�ͻ����

//���˵�
void mainmenu() {
	getuser();
	printf("=��ӭʹ���й�ũҵ���������ѧ��ϪУ������=\n");
	printf("=============ѡ�����ǰ��忨=============\n");
	Sleep(390);
	printf("=================���ڶ���=================\n");
	Sleep(390);
	printf("===========�����ɹ����������˺�===========\n");
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
				user_num = i; //��ע�������û������������������ת�˲�ѯֱ�ӷ���
				break;
			}
		}
		if (m != 19) {
			printf("======δ��ѯ���˺ţ�������������룡=====\n");
		} else {
			printf("==============�˺���֤�ɹ���==============\n");
			break;
		}
	}
	system("cls");
	printf("======���������루��������������ᣩ======\n");
	for (int i = 1; i <= 3; i++) {
		int a;
		cin >> a;
		if (a == psw) {
			printf("===��֤����ɹ���������ת���ܽ��档����===\n");
			Sleep(390);
			system("cls");
			functionhall();
			break;
		} else if (i <= 2) {
			printf("=========��֤����������ٴ�����=========\n");
		} else if (i == 3) {
			printf("=��֤����������ڴ��մ����֤�ڱ��н���=\n");
			printf("============�����˳�ϵͳ������============\n");
			break;
		}
	}
}

//����ѯ
void view() {
	getuser();
	printf("==============���ڲ�ѯ������==============\n");
	Sleep(390);
	cout << "�����˻����Ϊ��" << users[user_num].Money << "Ԫ��" << endl;
	printf("============����0���ع��ܴ���=============\n");
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		functionhall();
	}
}

//ȡ���
void getmoney() {
	getuser();
	printf("=================����׼��=================\n");
	Sleep(390);
	printf("==������ȡ��������Ϊ100����������:==\n");
	while (1) {
		long long n;
		cin >> n;
		if (n > users[user_num].Money) {
			printf("======�˻����㣬�����������======\n");
		} else if (n % 100 != 0) {
			printf("==����������ȡ������ӦΪ100������:==\n");
		} else if (n > users[user_num].limit) {
			printf("===������ȡ���ѳ����������ޣ����������===\n");
		} else if (n > users[user_num].daylimit) {
			printf("=====������ȡ���ѳ������ޣ������ȡ��=====\n");
		} else if (n <= users[user_num].limit && n % 100 == 0 && n <= users[user_num].Money && n <= users[user_num].daylimit) {
			users[user_num].Money = users[user_num].Money - n;
			users[user_num].daylimit = users[user_num].daylimit - n;
			printf("==========����ȡ����Ժ󡣡���==========\n");
			Sleep(390);
			printf("================ȡ��ɹ���================\n");
			break;
		}
	}
	Userinf();
	printf("============����0���ع��ܴ���=============\n");
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		functionhall();
	}
}
int y;//���ת���˻����

//ת�˹���()
void transmoney() {
	getuser();
	printf("===============׼���С�����===============\n");
	Sleep(390);
	printf("============������ת���û��˺�============\n");
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
			printf("======���˺Ų����ڣ��������������======\n");
		} else {
			break;
		}
	}
	printf("===========���ٴ������˺Ų�ȷ��===========\n");
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
			printf("=====�����˺Ų�һ�£��������������=====\n");
		} else {
			printf("===������ת�˽��:�������Ϊ100��������===\n");
			break;
		}
	}
	while (1) {
		long long g;
		cin >> g;
		if (g > users[user_num].Money) {
			printf("======�˻����㣬�����������======\n");
		} else if (g % 100 != 0) {
			printf("==����������ת�˽����ӦΪ100������:==\n");
		} else if (g > users[user_num].limit) {
			printf("===������ת���ѳ����������ޣ����������===\n");
		} else if (g > users[user_num].daylimit) {
			printf("===�����������ܶ��ѳ������ޣ������ת��===\n");
		} else if (g <= users[user_num].limit && g % 100 == 0 && g <= users[user_num].Money && g <= users[user_num].daylimit) {
			users[user_num].Money = users[user_num].Money - g;
			users[user_num].daylimit = users[user_num].daylimit - g;
			users[y].Money = users[y].Money + g;
			printf("==========����ת�ˣ����Ժ󡣡���==========\n");
			Sleep(390);
			printf("================ת�˳ɹ���================\n");
			break;
		}
	}
	Userinf();
	printf("============����0���ع��ܴ���=============\n");
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		functionhall();
	}
}

//�޸�����
void changepsw() {
	getuser();
	printf("=================����׼��=================\n");
	printf("===============������ԭ����===============\n");
	while (1) {
		int b;
		cin >> b;
		if (b != users[user_num].Password) {
			printf("========�����������������ԭ����========\n");
		} else {
			printf("===============������������===============\n");
			break;
		}
	}
	int B;
	cin >> B;
	printf("==============���ٴ���������==============\n");
	while (1) {
		int C;
		cin >> C;
		if (C != B) {
			printf("=======��������������ٴ���������=======\n");
		} else {
			printf("==============�����޸ĳɹ���==============\n");
			break;
		}
	}
	users[user_num].Password = B;
	Userinf();
	printf("============����0���ع��ܴ���=============\n");
	int y;
	cin >> y;
	if (y == 0) {
		system("cls");
		Sleep(390);
		functionhall();
	}
}

//���ܽ���
void functionhall() {
	getuser();
	printf("=��ӭ�������ܴ�������ѡ�����ѡ��ǰ���֣�=\n");
	printf("================[1]����ѯ===============\n");
	printf("================[2]ȡ���===============\n");
	printf("================[3]ת�˹���===============\n");
	printf("================[4]�޸�����===============\n");
	printf("================[5]�����˻�===============\n");
	printf("================[6]�˳�����===============\n");
	printf("================[7]���µ�¼===============\n");
	int n;
	cin >> n;
	switch (n) {
		case 1:
			printf("===========������ת���Ժ󡣡���===========\n");
			Sleep(390);
			system("cls");
			view();
			break;
		case 2:
			printf("===========������ת���Ժ󡣡���===========\n");
			Sleep(390);
			system("cls");
			getmoney();
			break;
		case 3:
			printf("===========������ת���Ժ󡣡���===========\n");
			Sleep(390);
			system("cls");
			transmoney();
			break;
		case 4:
			printf("===========������ת���Ժ󡣡���===========\n");
			Sleep(390);
			system("cls");
			changepsw();
			break;
		case 5:
			printf("===========������ת���Ժ󡣡���===========\n");
			Sleep(390);
			system("cls");
			create_user();
			break;
		case 6:
			printf("===========�����˿����Ժ󡣡���===========\n");
			Sleep(390);
			system("cls");
			printf("=====��л����ʹ�ã��ڴ��´����Ĺ��٣�=====\n");
			break;
		case 7:
			printf("===========������ת���Ժ󡣡���===========\n");
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
	printf("|=      �й�ũҵ���������ѧ��Ϫ����     =|\n");
	printf("|=                                       =|\n");
	printf("|=                                       =|\n");
	printf("|=           =��ӭʹ��ATM��̨��=         =|\n");
	printf("|=           =����1ע�����û�!=          =|\n");
	printf("|=              =����2��¼=              =|\n");
	printf("|=                                       =|\n");
	printf("|=                                       =|\n");
	printf("+=========================================+\n");
	int j;
	cin >> j;
	system("cls");
	//��¼����
	if (j == 1) {
		create_user();
	} else if (j == 2) {
		mainmenu();
	}
	Userinf();
	return 0;
}