#pragma once
#define RED        0    // 红色节点
#define BLACK    1    // 黑色节点
#include "List.h"

typedef struct RBleaf {
	int hashfile;
	char filename[50];
	LinkList index;
}RBleaf;
// 红黑树的节点
typedef struct RBTreeNode {
	unsigned char color;        // 颜色(RED 或 BLACK)
	RBleaf key;                    // 关键字(键值)
	struct RBTreeNode *left;    // 左孩子
	struct RBTreeNode *right;    // 右孩子
	struct RBTreeNode *parent;    // 父结点
}Node, *RBTree;

// 红黑树的根
typedef struct rb_root {
	Node *node;
}RBRoot;

// 创建红黑树，返回"红黑树的根"！
RBRoot* create_rbtree();

// 销毁红黑树
void destroy_rbtree(RBRoot *root);

// 将结点插入到红黑树中。插入成功，返回0；失败返回-1。
int insert_rbtree(RBRoot *root, RBleaf key);

// 删除结点(key为节点的值)
void delete_rbtree(RBRoot *root, RBleaf key);


// 中序遍历"红黑树"
void inorder_rbtree(RBRoot *root);

// (递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
RBleaf* rbtree_search(RBRoot *root, int hashkey);
// 打印红黑树
void print_rbtree(RBRoot *root);