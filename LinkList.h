#pragma once
/* 构建双向链表  */
#include"node.h"
#include<iostream>
using namespace std;

class LinkList
{
private:
	Node* head;  //头指针
	Node* tail;  //尾指针
	Node* cur;  //当前指针
	int count;  //当前行数,1开始算
public:
	LinkList();  //构造函数
	~LinkList();   //析构
	bool Insert(int number, string newline);  //插入新行到指定行后面
	bool Delete(int lineNumber);   //删除指定行
	bool Begin();   //到缓冲区第一行
	bool End();		//到缓冲区最后一行
	bool ToGivenLine(int lineNumber);   //到指定行
	bool Display();		//显示缓冲区全部内容
	bool Statistics();    //显示缓冲区所包含的行数和字符数
	bool Replace(string s1, string s2);   //将s1替换成s2
	bool SearchLine(string s);  //查找s所在第一行
	bool NextLine();  //下一行
	bool LastLine();  //上一行
	int GetCount();   //获取count值
	Node* GetCur();   //获取cur指针
	Node* GetHead();  //获取head指针
	
};

LinkList::LinkList()
{
	head = tail = cur = new Node();
	count = 0;
	if (!head)
	{
		cout << "error!" << endl;//内存分配失败
	}   
}

bool LinkList::Insert(int number, string newline)
{
	if (!(number >= 0 && number <= count))
		return false;
	Node* Line = new Node();
	if (!Line) return false;   //内存分配错误
	Line->s = newline;
	Line->lineNumber = number + 1;
	Node* temp = head;
	if (!temp) return false;  //内存分配错误
	for (int i = 0;i < number; i++)
	{
		temp = temp->next;      //temp指向要插入的行
	}

	Line->last = temp;
	Line->next = temp->next;
	temp->next = Line;
	if (Line->next != NULL)        //插入节点不是尾节点
		Line->next->last = Line;     //新插入行的下一行
	cur = Line;   //当前行变为新插入行
	if (cur->next == NULL) tail = cur;    //尾行
	temp = Line->next;
	count++;    //行数加1
	while (temp)
	{
		temp->lineNumber++;   //改变插入行之后的行号
		temp = temp->next;
	}
	return true;
}

LinkList::~LinkList() {}   //待写函数

bool LinkList::Delete(int number)
{
	if (!(number >0 && number <= count))
		return false;           //删除行不存在
	count--;   //行数减1
	cur = head;
	for (int i = 0;i < number; i++)
	{
		cur = cur->next;    //cur指向待删除行
	}
	cur->last->next = cur->next;   //cur前继节点
	if (cur->next)
		cur->next->last = cur->last;
	Node* temp = cur;
	cur = cur->next;   //移到删除行的下一行,注意cur可能为null
	if (cur == NULL)  //删除的是最后一行
		tail = temp->last;   //tail指向删除行的前继
	delete temp;      //删除行
	temp = cur;
	while (temp)
	{
		temp->lineNumber--;
		temp = temp->next;
	}
	if (cur == NULL)
		cur = tail;
	return true;
}
bool LinkList::Begin()
{
	if (count == 0)     //行数为0
		return false;
	cur = head->next;   //移到首行
	return true;
}
bool LinkList::End()
{
	if (count == 0)		//行数为0
		return false;
	cur = tail;    //移到尾行
	return true;
}
bool LinkList::ToGivenLine(int lineNumber)
{
	if (lineNumber < 1 || lineNumber > count)     //行号越界
		return false;
	Node* temp = head;
	for (int i = 0;i < lineNumber; i++)
		temp = temp->next;    //temp指向指定行号
	cur = temp;     //移到指定行号
	return true;
}

bool LinkList::Display()
{
	if (count == 0)   //行数为0
		return false;
	Node* temp = head->next;
	while (temp)
	{
		cout <<"The row"<< temp->lineNumber << "'s content is:" << temp->s << endl;   //遍历
		temp = temp->next;
	}
	return true;
}

bool LinkList::Statistics()
{
	if (count == 0)   //行数为0
		return false;
	Node* temp = head->next;
	int countChar = 0, countParagraph = 0;
	while (temp)
	{
		countParagraph++ ;
		countChar += size(temp->s);
		temp = temp->next;
	}
	cout << "sum of rows" << countParagraph << "\nsum of characters：" << countChar << endl;

	return true;
}

string& replace_all_distinct(string& str, const  string& old_value, const string& new_value);   //子串替代函数声明
bool LinkList::Replace(string s1, string s2)
{
	for (cur = head;cur->next; cur = cur->next)
	{
		if (cur->s.find(s1) != string::npos)    //查找失败返回npos
		replace_all_distinct(cur->s, s1, s2);   //s1替换成s2
	}
	return true;
}

string& replace_all_distinct(string& str, const string& old_value, const  string& new_value)  //来自网上
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())
	{
		if ((pos = str.find(old_value, pos)) != string::npos)
		{
			str.replace(pos, old_value.length(), new_value);
		}
		else { break; }
	}
	return   str;
}


bool LinkList::SearchLine(string s)
{
	if (!head) return false;   //head为null
	Node* temp = head->next;    //从第一行开始
	while (temp)
	{
		if (temp->s.find(s) != string::npos)   //找到目标串s
		{
			cur = temp;  return true;   //找到含目标串的第一行
		}
		temp = temp->next;
	}

	return false;   //未找到目标串
}

bool LinkList::NextLine()
{
	if (!cur->next)
		return false;    //当前已经是最后一行
	cur = cur->next;     //移到下一行
	return true;
}

bool LinkList::LastLine()
{
	if (cur->last == head)  //已经是首行
		return false;
	cur = cur->last;    //移到上一行
	return true;
}

int LinkList::GetCount()
{
	return count;
}

Node* LinkList::GetCur()
{
	return cur;
}

Node* LinkList::GetHead()  //获取head指针
{
	return head;   //返回头指针
}
