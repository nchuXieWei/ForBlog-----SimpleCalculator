#include <stdio.h>  //get()��Ҫʹ�õ�ĳЩ�����������
#include <ctype.h>  //get()��Ҫ�������е������жϺ���
#include "Calculator.h" //�Զ���ͷ�ļ��������ṹ����������������


//�������ʽ���飬Infix��ͷ���ݴ���׺���ʽ��Postfix��ͷ�Ĵ洢���ڼ���ĺ�׺���ʽ
Elem InfixExpression[SIZE];
Elem PostfixExpression[SIZE];

//������ջ��topOperָ�������ջ��ջ������ջ���������Ǹ�Ԫ�ص������Ǹ���λ�ã�
char StackOper[SIZE];
size_t topOper = 0;

//������ջ��push
void pushOper(char oper)    
{
	StackOper[topOper++] = oper;
}
//������ջ��pop
char popOper()
{
	return StackOper[--topOper];
}

//���ڼ����׺���ʽ�Ĳ�����ջ��topNumָ�������ջ��ջ��
//ջ��Ԫ��Ϊdouble����Ϊint/int�п��ܵó�С��
double StackNum[SIZE];
size_t topNum = 0;
//������ջ��push
void pushNum(double e)
{
	StackNum[topNum++] = e;
}
//������ջ��pop
double popNum()
{
	return StackNum[--topNum];
}


//get()�����Ķ��壬get()���ô���Calculator.hͷ�ļ���
bool get()
{
	//���ڱ����û�����ġ��ַ�������û�С����롱�Ʊ��ʽ���û����룩
	char input[SIZE * 10];

	//�����ʾ��Ϣ�����ϣ����ֹ������������'n'
	printf("Please enter expression,end with '='\n(if you want to stop calculator,enter 'n'):\n");
	//ͨ��fgets������ȡ�û�����
	fgets(input, sizeof(input) / sizeof(char), stdin);


	//���жϣ�����û��������'n'�򷵻�false������������get()����ֵ������������
	if (input[0] == 'n')
		return false;

	//���û�û�м���'n'��Ĭ���û�������ȷ����׺���ʽ
	//num���ڡ�ת�����û�����������ַ��������÷�����
	int num = 0;

	//��������input���飬��Ȼ������һ����;�ͻ�����
	for (size_t i = 0, j = 0;i < SIZE * 10;i++)
	{
		//����ǰ�ַ�Ϊ�����ַ����������ǰ�����ַ����䡰���ҡ��������ַ�һ�������һ��ʲô��
		if (isdigit(input[i]))
		{
			num = num * 10 + input[i] - '0';  //num��ʾ����ǰ���֡�����ʼֵΪ0�������Ե����ٴΡ�����һ�������ַ�ʱ����Ȼ��Ҫ����ǰ���֡�����10����λ���ټ����µ������ַ���Ӧ������
		}
		//����ǰ�ַ����������ַ�����������Ҫ�ж�����ʲô�ַ�
		else
		{
			//����ǰ�ַ�Ϊ'='���ʾ���ʽ��������ʱ������Ҫ����һЩ�����ж�
			if (input[i] == '=')
			{
				//�����ʽ'='֮ǰ���Ǹ��ַ�����')'���Ȼ��һ�������ַ������������Ҫ��ȡ���Ǹ������ַ����䡰���ҡ������ַ���ɵ���
				if (input[i - 1] != ')')
				{
					InfixExpression[j].IsNum = true;
					InfixExpression[j++].num = num;
					num = 0;   //��ȡ�������ַ���ɵ���������Ҫ��num������������һ�Ρ�ת���������ַ�
				}
				//����'='ǰһ���ַ��������ַ�����')'�����Ƕ���Ҫ��'='������׺���ʽ���鲢������input[]�ı���
				InfixExpression[j].IsNum = false;
				InfixExpression[j++].oper = '=';
				break;
			}
			//'('���������һ������'('��ǰһ���ַ���ӦΪ��������������ǲ���Ҳ���á���ȡ��num��ֵ
			else if (input[i] == '(')
			{
				InfixExpression[j].IsNum = false;
				InfixExpression[j++].oper = '(';
			}
			else if (input[i] == ')'&& input[i-1] == ')')
			{
				
					InfixExpression[j].IsNum = false;
					InfixExpression[j++].oper = ')';
			
			}
			//��ȥ�������������������������')'����ǰһ���ַ���ӦΪ�����ַ������������Ҫ����ȡ��num��ֵ��Ȼ�󽫲�����Ҳ������������num
			else
			{
				InfixExpression[j].IsNum = true;
				InfixExpression[j++].num = num;
				num = 0;
				InfixExpression[j].IsNum = false;
				InfixExpression[j++].oper = input[i];
			}
		}
	}


	//����ѭ��Ϊ�����Եģ�Ч���������׺���ʽ�д洢�ı��ʽ����������Ļ���Ӧ��ʹ����������ͬ
	for (size_t i = 0;i < SIZE;++i)
	{
		if (!InfixExpression[i].IsNum&&InfixExpression[i].oper == '=')
		{
			printf("%c\n", '=');
			break;
		}
		else if (InfixExpression[i].IsNum)
		{
			printf("%d", InfixExpression[i].num);
		}
		else
		{
			printf("%c", InfixExpression[i].oper);
		}

	}
	//����true�����������û�û�м���'n'
	return true;
}






//����translate()��һЩ����������ջ����
//����׺ת��Ϊ��׺ʱ�������������������ô������Ҫ�Բ����������ж�Ȼ�������Ӧ�ģ�ջ������
//������Щ�������ǵ�������ͬ������ʱ���õĲ�ͬ��������������
void IsAdd(size_t *j);
void IsSub(size_t *j);
void IsMulti();
void IsDiv();
void IsLeft();
void IsRight(size_t *j);
void IsEqual(size_t *j);


//translate()�����Ķ��壬����;˵����Calculator.h��
void translate()
{
	//������׺���ʽ���飬�����д洢����׺���ʽת��Ϊ��׺���ʽ�������׺���ʽ����
	//iΪ��׺���ʽ����ġ���ǰ�±ꡱ����ǰ���жϵ�Ԫ�أ���jΪ��׺���ʽ����ġ���ǰ�±ꡱ���������׺����Ԫ��Ӧ�����λ�ã����м����߲���ͬ��
	for (size_t i = 0, j = 0;i < SIZE;++i)
	{
		//����ǰ��׺����׺���ʽ�ļ�ƣ�Ԫ��Ϊ����������ֱ�ӽ��䡰���������׺���ʽ
		if (InfixExpression[i].IsNum)
		{
			PostfixExpression[j].IsNum = true;
			PostfixExpression[j++].num = InfixExpression[i].num;
		}
		//����ǰ��׺Ԫ�ز������֣���������Ҫ�����䡰ֵ������Ӧѡ���ջ����������Ҳ����׺�±�i�ͺ�׺�±�j��ͬ����ԭ�����֮��
		else
		{
			switch (InfixExpression[i].oper)
			{
			case '(':
				IsLeft();  //��ǰԪ��Ϊ'('ʱ�����ǵ���IsLeft()����Ϊ'('��Ȼ��ֱ����ջ���������ǵ�j���ᷢ���仯
				break;
			case ')':
				IsRight(&j); //��ǰԪ��Ϊ')'ʱ����IsRight()����Ϊ')'���ܵ������Ԫ������׺���ʽ��������Ҫ֪����׺���±�j������j���ܻᷢ���仯�����ǽ�j�ĵ�ַ���ݹ�ȥ
				break;
			case '+':
				IsAdd(&j);  //��ǰԪ��Ϊ'+'ʱ����IsAdd()����Ϊ'+'���ܵ������Ԫ������׺���ʽ��������Ҫ֪����׺���±�j������j���ܻᷢ���仯�����ǽ�j�ĵ�ַ���ݹ�ȥ
				break;
			case '-':
				IsSub(&j);  //��ǰԪ��Ϊ'-'ʱ����IsSub()����Ϊ'-'���ܵ������Ԫ������׺���ʽ��������Ҫ֪����׺���±�j������j���ܻᷢ���仯�����ǽ�j�ĵ�ַ���ݹ�ȥ
				break;
			case '*':
				IsMulti();  //��ǰԪ��Ϊ'*'ʱ����IsMult()����Ϊ'*'ֱ����ջ������j���ᷢ���仯������Ҫ����
				break;
			case '/':
				IsDiv();  //��ǰԪ��Ϊ'/'ʱ����IsDiv()����Ϊ'/'ֱ����ջ������j���ᷢ���仯������Ҫ����
				break;
			case '=':   //��ǰԪ��Ϊ'='ʱ����IsEqual()����Ϊ'='�ᵼ�����Ԫ������׺���ʽ��������Ҫ֪��j��������ֻ��Ҫj��ֵ��Ϊ���ʽҪ�����ˣ������ǻ��Ǵ�����j�ĵ�ַ������������޸Ĩr(�s_�t)�q
				IsEqual(&j);
				return;
			}
		}
	}
}

//�����'('��ֱ��pushOper()
void IsLeft()
{
	pushOper('(');
}

//�����')'�򵯳�ջ��Ԫ��ֱ��ջ��Ԫ��Ϊ'('����ջ��Ԫ��Ϊ'('ʱ����������
void IsRight(size_t *j)
{
	char oper;
	//�������ȷ�ı��ʽ��������)ʱջ��һ����(����ʱѭ��������ʵû����
	while (topOper > 0)
	{
		//��ȡջ��Ԫ��
		oper = popOper();

		//�����'('�򷵻أ���Ϊ'('���������Կ��Բ����
		if (oper == '(')
			return;
		//�������'('�򽫸ò����������������׺���ʽ
		else
		{
			PostfixExpression[(*j)].IsNum = false;
			PostfixExpression[(*j)++].oper = oper;
		}
	}
}

void IsAdd(size_t *j)
{
	char oper;
	while (topOper > 0)
	{
		oper = popOper();
		if (oper == '(')
		{
			pushOper(oper);
			break;
		}
		else
		{
			PostfixExpression[(*j)].IsNum = false;
			PostfixExpression[(*j)++].oper = oper;
		}
	}

	pushOper('+');
}

void IsSub(size_t *j)
{
	char oper;
	while (topOper > 0)
	{
		oper = popOper();
		if (oper == '(')
		{
			pushOper(oper);
			break;
		}
		else
		{
			PostfixExpression[(*j)].IsNum = false;
			PostfixExpression[(*j)++].oper = oper;
		}

	}

	pushOper('-');
}

void IsMulti()
{
	pushOper('*');
}

void IsDiv()
{
	pushOper('/');
}

void IsEqual(size_t *j)
{
	char oper;
	while (topOper > 0)
	{
		oper = popOper();
		PostfixExpression[(*j)].IsNum = false;
		PostfixExpression[(*j)++].oper = oper;
	}
	PostfixExpression[(*j)].IsNum = false;
	PostfixExpression[(*j)++].oper = '=';
}


//��Ȼ���ǵĽṹ����ʹ�õ���int������int/intҲ�п��ܳ���С�����������Ƿ���ֵʹ��double
double calculate()
{
	//������׺���ʽ���飬�����׺���ʽ��û������Ŀ�ģ�ֻ�Ƿ������ǡ���顱һ�º�׺���ʽ
	for (size_t i = 0;i < SIZE;++i)
	{
		if (!PostfixExpression[i].IsNum && PostfixExpression[i].oper == '=')
		{
			printf("%c\n", '=');
			break;
		}
		else if (PostfixExpression[i].IsNum)
		{
			printf("%d", PostfixExpression[i].num);
		}
		else
		{
			printf("%c", PostfixExpression[i].oper);
		}
	}

	//��׺���ʽ�ļ�����̣�����������׺���ʽ���飬������������;������'='�������������û�У��ðɣ�����Ҫ������
	for (size_t i = 0;i < SIZE;++i)
	{
		//�����ǰԪ�ز�����������oper=='='����˵�����ʽ��ĩβ�ˣ���ʱ���ǵ���ջ��Ԫ�أ���ӦΪΨһһ������Ϊ����������
		if (!PostfixExpression[i].IsNum&&PostfixExpression[i].oper == '=')
		{
			return popNum();
		}
		//�����ǰԪ��Ϊ���֣������ǽ���ת��Ϊdouble�Ͳ���ջ
		else if (PostfixExpression[i].IsNum)
		{
			pushNum((double)(PostfixExpression[i].num));
		}
		//�����ǰԪ�ز�������Ҳ������oper=='='��˵������һ������������������ţ���׺���ʽû�����ţ�
		//��ʱ���ǰ����㷽ʽpop��ջ����Ԫ�ؽ��м��㲢���������ѹ��ջ
		else
		{
			//temp�����ݴ�ջ����Ԫ�صļ�����
			double temp = 0.0;
			//ע�⣬��һ��popNum�õ���Ӧ��Ϊ�Ҳ��������ڶ���popNum�õ�����Ϊ������������Ƿֱ��Ϊrear��front
			double rear = popNum();
			double front = popNum();

			//���ݵ�ǰԪ��ѡ��Ӧ���е����㣬���������ջ
			switch (PostfixExpression[i].oper)
			{
			case '+':
				temp = front + rear;
				pushNum(temp);
				break;
			case '-':
				temp = front - rear;
				pushNum(temp);
				break;
			case '*':
				temp = front*rear;
				pushNum(temp);
				break;
			case '/':
				temp = front / rear;
				pushNum(temp);
				break;
			}
		}
	}

	return 0;
}