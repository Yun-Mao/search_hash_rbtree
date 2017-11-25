extern "C" {
#include"hashTable.h"
#include"rbtree.h"
#include"List.h"
}

#include<iostream>
#include <fstream>
#include<algorithm>
#include<vector>
#include<string>
#define TRUE 1
#define FALSE 0
using namespace std;
vector<string> stopword;     //stopword��������һЩ�ʳ��ִ���̫�࣬�ò���ʧ�����岻���� a the��
void Insertword(string voc, string filename, int address, hashTable * Index);//��������ʱҪ����Ԫ��
void BuildIndex(hashTable *Index);// ��������
void collect_stopword();//��stopword��������
bool isstopword(string W);//�ж�stopword
string Filename(int N, int M);//�����ַ�ʽ��ȡһ���ļ���
bool isword(char ch);//�ж����char�Ƿ�Ϸ�

void collect_stopword()
{
	ifstream fp;
	string stop;
	char ch;
	fp.open("stopword.txt", ios_base::in | ios_base::binary);
	if (!fp)
	{
		cout << "��ȡ���δʳ���" << endl;
		return;
	}

	fp.get(ch);
	while (fp)
	{
		stop = "";

		while (!isword(ch) && !fp.eof())
		{
			fp.get(ch);
		}

		if (!fp)
			break;

		while (isword(ch) && !fp.eof())
		{
			stop += ch;
			fp.get(ch);
		}
		transform(stop.begin(), stop.end(), stop.begin(), tolower);

		stopword.push_back(stop);
	}
}

//�ж��ǲ���stopword��������һ��������ȡ��������stopwordƴ�ɵ��ַ������ж��Ƿ����������ҵ�����
bool isstopword(string W)
{
	if (find(stopword.begin(), stopword.end(), W) == stopword.end())
		return 0;
	else
		return 1;
}
//�ж��Ƿ��ǵ���
bool isword(char ch)
{
	//��׼������ch��A-Z����a-z�м������\�����n�ɣ�����
	int D = ((ch >= 'a' && ch <= 'z') || (ch >= 'A'&& ch <= 'Z') || (ch == '\''));
	return ((D == 1) ? TRUE : FALSE);
}

//�����ļ����ĺ�������Ϊʾ���ļ���10xx x�ĸ�ʽ������ô���죩
string Filename(int N, int M)
{
	string res;
	char file[15];
	char chap[10];
	_itoa_s(N, file, 10);
	_itoa_s(M, chap, 10);
	strcat_s(file, 15, " ");
	strcat_s(file, 15, chap);
	strcat_s(file, 15, ".txt");
	res = file;
	return res;
}
int hashfile(char*p)
{
	int i = strlen(p);
	int hash=0;
	int j;
	for (j = 0; j < i; j++)
	{
		if (p[j] >= '0'&&p[j] <= '9')
		{
			hash = hash * 10 + p[j] - '0';
		}
	}
	return hash;
}
//����ɨ�赽�ĵ�ǰ������Ϣ�����ĸ��ļ���������ٲ��� �� address��־�˵���λ��
void Insertword(string voc, string filename, int address, hashTable* t)
{
	char p[50];
	strcpy(p, voc.c_str());
	char *fname = (char*)filename.c_str();
	if (findValue(t,p)==NULL)//����������ͷû����������ǾͰ����ӽ�ȥ
	{
		LinkList L;
		InitList(&L);
		ListInsert(&L, 1, address);
		RBRoot *root;
		root = create_rbtree();
		RBleaf *leaf = (RBleaf*)malloc(sizeof(RBleaf));
		strcpy(leaf->filename, filename.c_str());
		leaf->hashfile = hashfile(fname);
		leaf->index = L;
		insert_rbtree(root, *leaf);
		insertEntry(t, p, root);
		//cout << "haha" << endl;
		//inorder_rbtree(t->bucket[hashfunc(p,strlen(p))].value);
	}
	else//�еĻ��͵ø�����������
	{
		RBRoot *tempRB=findValue(t, p);
		//���С���������sour��û���ҵ���ǰ�ļ�������˼�������ҵ��Ĵ��Ǳ��ļ��е�һ�γ��֣�
		if (rbtree_search(tempRB,hashfile(fname))==NULL)
		{
			LinkList L;
			InitList(&L);
			ListInsert(&L, 1, address);
			RBleaf *leaf = (RBleaf*)malloc(sizeof(RBleaf));
			strcpy(leaf->filename, filename.c_str());
			leaf->hashfile = hashfile(fname);
			leaf->index = L;
			insert_rbtree(tempRB, *leaf);
			//inorder_rbtree(t->bucket[hashfunc(p, strlen(p))].value);
			//insertEntry(t, p, tempRB);
		}
		//���С����sour���ҵ��˵�ǰ�ļ�������˼�������ҵ��Ĵ��ڱ��ļ��г��ֹ���NA�����Ѿ��������ˣ�ֱ�ӼӾ��У�
		else
		{
			RBleaf*templeaf = rbtree_search(tempRB, hashfile(fname));
			ListInsert(&templeaf->index, 1, address);
			//inorder_rbtree(t->bucket[hashfunc(p, strlen(p))].value);
		}
	}
}

void BuildIndex(hashTable *Index)
{
	int cou;
	int num;

	string filename = "";
	ifstream fp;
	string voc = "";
	int address;
	char ch;

	//���˫��ѭ�������Filename�������Լ�д�ģ����->�������ļ�������
	for (cou = 1001; cou <= 1042; cou++)
	{

		for (num = 1; num <= 153; num++)
		{
			filename = Filename(cou, num);
			fp.open("Shakespeare/" + filename, ios_base::in | ios_base::binary);
			if (!fp.is_open())
				continue;
			cout << filename << endl;
			address = 0;
			fp.get(ch);
			while (fp)//��ǰѧ����������ʶ�
			{
				voc = "";


				//���ǵ�����û����β�ͼ���
				while (!isword(ch) && !fp.eof())
				{
					fp.get(ch);
				}

				//����β���˳���ȥ��һ���ļ���
				if (!fp)
					break;

				//�ǵ��ʵĲ�������String vocabulary����׺����
				while (isword(ch) && !fp.eof())
				{
					voc += ch;
					fp.get(ch);
				}
				transform(voc.begin(), voc.end(), voc.begin(), tolower);    //ת����Сд��ĸ

																			//�±��ƶ������ڵڼ���λ���
				address++;

				//���粻�����δʻ㣬����������Ϣ�ٲ�����������֮ǰ��Insert������
				if (!isstopword(voc))
				{
					Insertword(voc, filename, address, Index);
					//getchar();
				}
			}
			fp.close();
		}
	}

}
void test() //���Թ���ר��
{
	LinkList L;
	InitList(&L);
	ListInsert(&L, 1, 10);
	ListInsert(&L, 1, 30);
	hashTable t;
	initHashTable(&t);
	RBRoot *root = NULL;
	root = create_rbtree();
	RBleaf *leaf = (RBleaf*)malloc(sizeof(RBleaf));
	//leaf->filename = "hahah";
	leaf->hashfile = 20;
	leaf->index = L;
	insert_rbtree(root, *leaf);
	leaf = (RBleaf*)malloc(sizeof(RBleaf));
	//leaf->filename = "hahaha";
	leaf->hashfile = 10;
	leaf->index = L;
	insert_rbtree(root, *leaf);
	insertEntry(&t, "son", root);
	insertEntry(&t, "on", root);
	RBRoot *b = findValue(&t, "son");
	inorder_rbtree(b);
	getchar();
}
int main(){
	//test();
	hashTable t;
	initHashTable(&t);
	cout << "���δ�������..." << endl;
	collect_stopword();
	cout << "���δʿ⽨�����" << endl;
	cout << "��������������..." << endl;
	BuildIndex(&t);
	cout << "���������������" << endl;
	while (1) {
		string s;
		cin >> s;
		char *p = (char *)s.c_str();
		inorder_rbtree(t.bucket[hashfunc(p, strlen(p))].value);
	}
	//inorder_rbtree((RBRoot*)t.bucket[hashfunc(p,strlen(p))].value);
	getchar();
	getchar();
}