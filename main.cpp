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
vector<string> stopword;     //stopword向量（有一些词出现次数太多，得不偿失，意义不大如 a the）
void Insertword(string voc, string filename, int address, hashTable * Index);//建立索引时要插入元素
void BuildIndex(hashTable *Index);// 建立索引
void collect_stopword();//把stopword加入向量
bool isstopword(string W);//判断stopword
string Filename(int N, int M);//用这种方式获取一个文件名
bool isword(char ch);//判断这个char是否合法

void collect_stopword()
{
	ifstream fp;
	string stop;
	char ch;
	fp.open("stopword.txt", ios_base::in | ios_base::binary);
	if (!fp)
	{
		cout << "读取屏蔽词出错！" << endl;
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

//判断是不是stopword——从上一个函数中取得了所有stopword拼成的字符串，判断是否能在里面找到就行
bool isstopword(string W)
{
	if (find(stopword.begin(), stopword.end(), W) == stopword.end())
		return 0;
	else
		return 1;
}
//判断是否是单词
bool isword(char ch)
{
	//标准：传入ch在A-Z或者a-z中间或者是\（配合n吧）就算
	int D = ((ch >= 'a' && ch <= 'z') || (ch >= 'A'&& ch <= 'Z') || (ch == '\''));
	return ((D == 1) ? TRUE : FALSE);
}

//构造文件名的函数（因为示范文件是10xx x的格式所以这么构造）
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
//整理扫描到的当前单词信息（在哪个文件的哪里），再插入 ， address标志了单词位置
void Insertword(string voc, string filename, int address, hashTable* t)
{
	char p[50];
	strcpy(p, voc.c_str());
	char *fname = (char*)filename.c_str();
	if (findValue(t,p)==NULL)//假如索引里头没有这个词我们就把他加进去
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
	else//有的话就得更新它的数据
	{
		RBRoot *tempRB=findValue(t, p);
		//如果小向量红黑树sour中没有找到当前文件名（意思是现在找到的词是本文件中第一次出现）
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
		//如果小向量sour中找到了当前文件名（意思是现在找到的词在本文件中出现过，NA向量已经建立过了，直接加就行）
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

	//这个双层循环是配合Filename函数（自己写的）完成->读所有文件的任务
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
			while (fp)//以前学过的逐个单词读
			{
				voc = "";


				//不是单词且没到结尾就继续
				while (!isword(ch) && !fp.eof())
				{
					fp.get(ch);
				}

				//到结尾就退出（去下一个文件）
				if (!fp)
					break;

				//是单词的操作就在String vocabulary中连缀上它
				while (isword(ch) && !fp.eof())
				{
					voc += ch;
					fp.get(ch);
				}
				transform(voc.begin(), voc.end(), voc.begin(), tolower);    //转化成小写字母

																			//下标移动（数在第几个位置嘛）
				address++;

				//假如不是屏蔽词汇，就整理单词信息再插入索引（用之前的Insert函数）
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
void test() //测试功能专用
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
	cout << "屏蔽词载入中..." << endl;
	collect_stopword();
	cout << "屏蔽词库建立完成" << endl;
	cout << "倒排索引建立中..." << endl;
	BuildIndex(&t);
	cout << "倒排索引建立完成" << endl;
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