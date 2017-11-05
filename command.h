#pragma once
/*  定义command函数  */

#include"LinkList.h"
using namespace std;
LinkList linkList;   //双向链表代表缓冲区
ifstream file1;      //输入文件
ofstream file2;      //输出文件

void CommandRead()   //读取文件到缓冲区
{
	file1.seekg(0, ios::beg);
	char temp[200] = { 0 };  //暂时存放读取的行，规定每行最多200个字符
	int i = 0;               //行标记
	while (!file1.eof())     //文件未到结尾时
	{
		file1.getline(temp, 200, '\n');  //读入当前行内容直到换行号
		linkList.Insert(i, temp);        //插入每行至缓冲区
		i++;   //进入下一行
	}
}

void CommandInsert() //插入行
{
	cout << "Enter the number of row in the insert sentence (the new row in the insert sentence below the specified row):";
	int lineNum = 0;  //插入的行号
	cin >> lineNum;   //读取行号
	while (lineNum < 0 || lineNum > linkList.GetCount())
	{
		cout << "error: Specified row does not exist!\n Please re-enter the number of row in the insert sentence:";    //行号非法
		cin >> lineNum;
	}
	string s;
	cout << "Enter the new sentence:";    //提示用户输入字符串
	cin >> s;
	linkList.Insert(lineNum, s);   //插入该行
}

void CommandDelete()   //删除当前行
{
	int curNum = linkList.GetCur()->lineNumber;  //获取当前行号
	linkList.Delete(curNum);   //删除当前行并移到下一行
}

void CommandFind()   //查找包含用户指定串的第一行
{
	cout << "Enter the sentence to be looked up (returns the first row appears in the sentence to be looked up):";   //提示用户输入指定串
	string str;
	cin >> str;
	if (!linkList.SearchLine(str))
		cout << "error:The sentence doesn't exist!" << endl;   //未找到目标串
}

void CommandChange()   //在当前行将目标串替换为指定文本
{
	cout << "Enter sentence to be replaced:";  //提示用户输入一个子串
	string s1;
	cin >> s1;
	cout << "Enter the target substitution sentence:";   //提示输入指定文本
	string s2;
	cin >> s2;
	if (!linkList.Replace(s1, s2))  //替换失败
		cout << "error:Unknown wrong!" << endl;
}

void CommandQuit()   //退出编辑器
{
	exit(0);
}

void CommandHelp()   //显示帮助信息
{
	cout << "--------------------------------HELP-------------------------------------\n"
		 << "|  r:读取文本到缓冲区  w:将缓冲区写入文本  i:插入单个新行  d:删除当前行  |\n"
		 << "|  f:查找含目标串的第一行  c:全局替换语句  q:退出编辑器   m:替换指定段落 |\n"
		 << "|h 或 ?:显示帮助信息  v:查看缓冲区所有内容  s:查看缓冲区内的行数和字符数 |\n" 
		 << "|     n:缓存区下一行  l:缓存区上一行  b:到首行  e：到尾行  g:到指定行    |\n"
		 << "--------------------------------------------------------------------------"
		 << endl;
}

void CommandNext() //缓冲区中进一行
{
	linkList.NextLine();
}

void CommandLast()   //缓冲区中退一行
{
	linkList.LastLine();
}

void CommandBegin()  //移到首行
{
	linkList.Begin();
}

void CommandEnd()  //移到尾行
{
	linkList.End();
}

void CommandGoto()  //到用户指定行号
{
	cout << "Please enter number of row:";   //提示用户输入指定的行号
	int lineNum = 0;   //行号
	cin >> lineNum;
	if (!linkList.ToGivenLine(lineNum)) //移到指定行
		cout << "error: Row does not exist！" << endl;    //行号越界
}

void CommandView()  //显示缓冲区全部内容
{
	cout << "..........................\n";
	if (!linkList.Display())   //遍历缓冲区
		cout << "error: Buffer is empty！" << endl;
	cout << "..........................\n";
}

void CommandWrite()   //将缓冲区写入输出文本
{
	Node *temp = linkList.GetHead();   //temp初始指向头结点
	if (!temp)
		return;
	temp = temp->next;   //指向第一行
	while (temp)
	{
		file2 << temp->s << endl;    //向输出文本输出当前行
		temp = temp->next;    //移到下一行
	}
}

void CommandStatistics()
{
	if(!linkList.Statistics())
		cout << "error: Buffer is empty！！" << endl;
}

void CommandMove()
{
	cout << "Enter the number of row where the sentence is to be replaced:";
	int lineNum = 0;  //插入的行号
	cin >> lineNum;   //读取行号
	while (lineNum < 0 || lineNum > linkList.GetCount())
	{
		cout << "error: Specified row does not exist!\n Please re-enter the number of row where the sentence is to be replaced:";    //行号非法
		cin >> lineNum;
	}
	string s;
	cout << "Enter the target substitution sentence:";    //提示用户输入字符串
	cin >> s;
	linkList.Insert(lineNum, s);   //插入该行
	linkList.Delete(lineNum);      //删除原行
}



bool GetCommand(char &c)
{
	if (linkList.GetCount() == 0)   //缓冲区为空
	{
	
		CommandRead();
		CommandView();
	}
	else
	{
		Node *cur = linkList.GetCur();   //获取当前行
		cout << "The row" << cur->lineNumber << "'s content is: " << cur->s << endl;   //输出当前行号及内容
	}
	cout << "Enter a new order:";
	char command;  //指令字符
	char ch;   //处理无用输入字符
	cin >> command;
	if (command >= 'A' && command <= 'Z') command += 32;    //如果是大写字母，则转换为小写
	c = command;    //返回读取的命令
	while ((ch = cin.get()) != '\n');  //删除指令字符后面多余的内容
	return true;
}

bool RunCommand(char command)
{
	switch (command)
	{
	case 'r':  CommandRead();  break;    //读取源文件到缓冲区
	case 'i':  CommandInsert(); break;	 //插入行，用户需根据提示输入插入行号
	case 'd':  CommandDelete(); break;   //删除当前行并移到下一行
	case 'f':  CommandFind(); break;     //查找包含用户请求的目标串的第一行
	case 'c':  CommandChange(); break;   //将用户指定字符串改为替换文本
	case 'n':  CommandNext();  break;    //在缓冲区中进一行
	case 'l':  CommandLast(); break;     //在缓冲区中退一行
	case 'b':  CommandBegin(); break;    //开始，到缓冲区第一行
	case 'e':  CommandEnd(); break;	     //结束，到缓冲区最后一行
	case 'g':  CommandGoto(); break;	 //到用户指定的行号
	case 'v':  CommandView();  break;    //遍历缓存区,显示其内容
	case 'w':  CommandWrite(); break;    //从缓冲区写入到目标文件
	case 'q':  CommandQuit(); break;	 //退出该文本编辑器
	case 'h':
	case '?':
	case'？':  CommandHelp(); break;       //显示所有命令的帮助信息
	case's' :  CommandStatistics(); break; //显示缓冲区内所包含的行数和字符数
	case'm' :  CommandMove(); break;       //替换指定行内容
	default :  break;
	}
	return true;
}
