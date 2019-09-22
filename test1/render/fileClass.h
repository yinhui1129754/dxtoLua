#pragma once
#if !defined(MAX_CHAR_BUFFER)
#define MAX_CHAR_BUFFER 10485760
#else
#pragma REMIND_ME("竟然定义了一个MAX_CHAR_BUFFER宏！")
#endif
class fileClass {
public :
	~fileClass();//析构函数
	fileClass(char *);//构造函数
	char * fp;//文件句柄
	int errorCode; //错误code
	char * path; //当前文件的文件地址
	int size; //写入数据的缓存大小
	int lines;//行数
	vector<long> lineIndex;//每一行的索引
	FILE * fileHandle; //文件句柄

	BOOL openFile(char *); //打开文件
	//BOOL write(char *); //写入字符串
	BOOL write(const char *);
	//BOOL write(string); //写入字符串
	long getIndex(); //获取文件操作标的位置
	int getLines(); //获取有多少行
	string readLine(); //读取一行数据
	string readLine(int lines);//读取指定行数据
	BOOL toStart(); //设置操作标到开始点
	int toIndex(long index); //设置文件操作标的位置
};