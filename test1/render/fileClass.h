#pragma once
#if !defined(MAX_CHAR_BUFFER)
#define MAX_CHAR_BUFFER 10485760
#else
#pragma REMIND_ME("��Ȼ������һ��MAX_CHAR_BUFFER�꣡")
#endif
class fileClass {
public :
	~fileClass();//��������
	fileClass(char *);//���캯��
	char * fp;//�ļ����
	int errorCode; //����code
	char * path; //��ǰ�ļ����ļ���ַ
	int size; //д�����ݵĻ����С
	int lines;//����
	vector<long> lineIndex;//ÿһ�е�����
	FILE * fileHandle; //�ļ����

	BOOL openFile(char *); //���ļ�
	//BOOL write(char *); //д���ַ���
	BOOL write(const char *);
	//BOOL write(string); //д���ַ���
	long getIndex(); //��ȡ�ļ��������λ��
	int getLines(); //��ȡ�ж�����
	string readLine(); //��ȡһ������
	string readLine(int lines);//��ȡָ��������
	BOOL toStart(); //���ò����굽��ʼ��
	int toIndex(long index); //�����ļ��������λ��
};