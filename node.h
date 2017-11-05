#pragma once

#include<string>
using namespace std;

struct Node
	//链表节点
{
	string s;   //一行内容
	Node* last;  //指向上一节点
	Node* next;  //指向下一节点
	int lineNumber;  //当前行号
	Node();
};
Node::Node()
{
	last = next = NULL;
	lineNumber = 0;
}
