#pragma once
#define RED        0    // ��ɫ�ڵ�
#define BLACK    1    // ��ɫ�ڵ�
#include "List.h"

typedef struct RBleaf {
	int hashfile;
	char filename[50];
	LinkList index;
}RBleaf;
// ������Ľڵ�
typedef struct RBTreeNode {
	unsigned char color;        // ��ɫ(RED �� BLACK)
	RBleaf key;                    // �ؼ���(��ֵ)
	struct RBTreeNode *left;    // ����
	struct RBTreeNode *right;    // �Һ���
	struct RBTreeNode *parent;    // �����
}Node, *RBTree;

// ������ĸ�
typedef struct rb_root {
	Node *node;
}RBRoot;

// ���������������"������ĸ�"��
RBRoot* create_rbtree();

// ���ٺ����
void destroy_rbtree(RBRoot *root);

// �������뵽������С�����ɹ�������0��ʧ�ܷ���-1��
int insert_rbtree(RBRoot *root, RBleaf key);

// ɾ�����(keyΪ�ڵ��ֵ)
void delete_rbtree(RBRoot *root, RBleaf key);


// �������"�����"
void inorder_rbtree(RBRoot *root);

// (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ㡣�ҵ��Ļ�������0�����򣬷���-1��
RBleaf* rbtree_search(RBRoot *root, int hashkey);
// ��ӡ�����
void print_rbtree(RBRoot *root);