#include"stdafx.h"
#include"Command.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])   //基于"stdafx.h"的<tchar.h>里_tmain的宏定义     
{
	char *inFile = new char[200];    //分配源文件名空间
	char *outFile = new char[200];   //分配目标文件名空间
	cout<<"Enter source file name (current directory file or specific directory):";
	
	while(1)            //重复输入文件，检验，直到输入文件存在时停止
	{
		gets_s(inFile,200);   //获取源文件名
	  file1.open(inFile);     //打开当前源文件对象
	  if(file1.fail())        //如果文件不存在
	  {
		  cout<<"The current file does not exist, please re-enter the source file name:";
		  file1.close();    
	  }
	  else break;   //源文件存在时，跳出循环
	}
	cout<<"Enter the name of the target file (automatically create a new location to the end of the file):";
	gets_s(outFile,200);
	file2.open(outFile,ios::out|ios::app);  //打开目标文件，输出方式打开，不清除原文件并定位到文件尾
	char command = '\0';          //初始化指令符
	while(GetCommand(command))   //读取指令
	{
		RunCommand(command);     //执行指令
	}
	file2.close();   //关闭源文件
	file1.close();   //关闭目标文件
	return 0;

}
