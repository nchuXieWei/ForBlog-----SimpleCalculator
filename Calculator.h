#ifndef CALCULATE   //���ڷ�ֹͷ�ļ�����ΰ��������Ķ�ζ�������
#define CALCULATE

//SIZE���ڶ�����ϣ���ջ�Ĵ�С�����ʽ����Ĵ�С
#define SIZE 1000

//���ʽ�ĵ���Ԫ����ʹ�õĽṹ��
typedef struct elem {
	int num = 0;
	char oper = '=';
	bool IsNum = false;
}Elem;

//get()���ڻ�ȡ�û����룬���û�����ת��Ϊ��׺���ʽ�洢��calculate.cpp����׺���ʽ������
bool get();
//translate()���ڽ���׺���ʽ�����е���׺���ʽת��Ϊ��׺���ʽ���洢����׺���ʽ������
void translate();
//calculate()�����ú�׺���ʽ�����еĺ�׺���ʽ��������ʽ���������
double calculate();
#endif

