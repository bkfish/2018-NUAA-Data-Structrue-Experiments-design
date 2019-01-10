/*
16、【2】算术表达式求值 (选做) （栈）
[问题描述]
　　一个算术表达式是由操作数(operand)、运算符(operator)和界限符(delimiter)组成的。假设操作数是正实数，运算符只含加减乘除等四种运算符，界限符有左右括号和表达式起始、结束符“#”，如：#6+15*（21-8/4）#。引入表达式起始、结束符是为了方便。编程利用“运算符优先法”求算术表达式的值。
[基本要求]
（1） 从键盘或文件读入一个合法的算术表达式，输出正确的结果。
（2） 显示输入序列和栈的变化过程。
（3） 考虑算法的健壮性，当表达式错误时，要给出错误原因的提示。
（4） 实现非整数的处理。*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<fstream>
#include<cmath>
#include<cstring>
#include<string.h>
#include<iomanip>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAX_N INT_MAX
using namespace std;
typedef struct
{
	double *base;
	double *top;
	int stacksize;
}doubleSqStack;

typedef struct
{
	char *base;
	char *top;
	int stacksize;
}charSqStack;

void InitdoubleStack(doubleSqStack& S)
{
    S.base=(double*)malloc(STACK_INIT_SIZE*sizeof(double));
    if(!S.base)
        exit(ERROR);
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
}

void doublePush(doubleSqStack &S,double &e)
{
    if(S.top-S.base>=S.stacksize)
    {
        S.base=(double*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(double));
        if(!S.base)
            exit(0);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top = e;
    ++S.top;
}

bool doublePop(doubleSqStack &S,double &e)
{
    if(S.top==S.base)
        return false;
    S.top--;
    e=*S.top;
    return true;
}
double doubleGetTop(doubleSqStack S)
{
    if(S.top==S.base)
    {
        cout<<"error";
        exit(0);
    }
    return *(S.top-1);
}

bool doubleTraverse(doubleSqStack &S)
{
    if(!S.base || !S.top || S.base == S.top)
    {
        cout << "遍历失败！" << endl;
        return ERROR;
    }
    double *base = S.base;
    double *top = S.top;
    while(top != base)
    {
        cout << "元素值为：" << *(top-1)<<endl;
        top--;
    }
    return OK;
}

void InitcharStack(charSqStack& S)
{
    S.base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!S.base)
        exit(0);
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
}

void charPush(charSqStack& S,char e)
{
    if(S.top-S.base>=S.stacksize)
    {
        S.base=(char*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(char));
        if(!S.base)
            exit(0);
        S.top=S.base+S.stacksize;
        S.stacksize+=STACKINCREMENT;
    }
    *S.top=e;
    ++S.top;
}

char charGetTop(charSqStack S)
{
    if(S.top==S.base)
    {
        cout<<"error";
        exit(0);
    }
    return *(S.top-1);
}

bool charPop(charSqStack &S,char &e)
{
    if(S.top==S.base)
        return false;
    S.top--;
    e=*S.top;
    return true;
}
bool charTraverse(charSqStack &S)
{
    if(!S.base || !S.top || S.base == S.top)
    {
        cout << "遍历失败！" << endl;
        return ERROR;
    }
    char *base = S.base;
    char *top = S.top;
    while(top != base)
    {
        cout << "元素值为：" << *(top-1)<<endl;
        top--;
    }
    return OK;
}

char Precede(char a,char b)
{
    char ch[7] = {'+','-','*','/','(',')','#'};
    int ch1,ch2;
    char pre[7][10];
    strcpy(pre[0],">><<<>>");
    strcpy(pre[1],">><<<>>");
    strcpy(pre[2],">>>><>>");
    strcpy(pre[3],">>>><>>");
    strcpy(pre[4],"<<<<<= ");
    strcpy(pre[5],">>>> >>");
    strcpy(pre[6],"<<<<< =");
    for(int i = 0;i < 7;i++)
    {
        if(ch[i] == a)
            ch1 = i;
        if(ch[i] == b)
            ch2 = i;
    }
    return pre[ch1][ch2];
}
bool isOPTR(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return OK;
    else
        return ERROR;
}

bool isMARK(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#' || ch == '.')
        return OK;
    else
        return ERROR;
}
double Operate(double &a,char theta,double &b)
{
    if(theta == '+')
        return a+b;
    else if(theta == '-')
        return a-b;
    else if(theta == '*')
        return a*b;
    else if(theta == '/')
    {
        if(b == 0)
        {
            cout << "ERROR :无法除0！" << endl;
            return MAX_N;
        }
        return a/b;
    }
}
double Pow(double x,int y)
{
    double result = 1;
    for(int i = y;y <0;y++)
    {
        result = result/x;
    }
    return result;
}
bool GetValue(string s)
{
    doubleSqStack OPND;
    charSqStack OPTR;
    InitcharStack(OPTR);
    InitdoubleStack(OPND);
    charPush(OPTR,'#');
    int count1 = 0;
    int count2 = 0;
    if(s[0] != '#' || s[s.length()-1] != '#')
    {
        cout << "界限符'#'错误（首尾应为#）！" << endl;
        cout << "****************************"<<endl<<endl;
        return ERROR;
    }
    if(isOPTR(s[1]))
    {
        cout << "运算符不能放在首位！" << endl;
        cout << "****************************"<<endl<<endl;
        return ERROR;
    }
    if(isOPTR(s[s.length()-2]))
    {
        cout << "运算符不能放在末位！" << endl;
        cout << "****************************"<<endl<<endl;
        return ERROR;
    }
    for(int i = 1;i <= s.length()-2;i++)
    {
        if(s[i] == '#')
        {
            cout << "界限符'#'错误（表达式内部不应有#）！" << endl;
            cout << "****************************"<<endl<<endl;
            return ERROR;
        }
        if(isOPTR(s[i]) && (isOPTR(s[i-1]) || isOPTR(s[i-1])))//运算符前后是运算符
        {
            cout << "运算符前后不能为运算符！" << endl;
            cout << "****************************"<<endl<<endl;
            return ERROR;
        }
        if(s[i] == '(')
        {
            count1++;
            if(!isOPTR(s[i-1]) && s[i-1] != '#' && s[i-1] != '(')
            {
                cout << "左括弧前只能为运算符或'#'和'('！ " << endl;
                cout << "****************************"<<endl<<endl;
                return ERROR;
            }
            if(isOPTR(s[i+1]))
            {
                cout << "左括弧后不能直接接运算符！" << endl;
                cout << "****************************"<<endl<<endl;
                return ERROR;
            }
            else if(s[i+1] == ')')
            {
                cout << "括弧内不能为空！" << endl;
                cout << "****************************"<<endl<<endl;
                return ERROR;
            }

        }
        else if(s[i] == ')')
        {
            count2++;
            if(isOPTR(s[i-1]))
            {
                cout << "右括弧前不能直接接运算符！" << endl;
                cout << "****************************"<<endl<<endl;
                return ERROR;
            }
            if(!isOPTR(s[i+1]) && s[i+1] != '#' && s[i+1] != ')')
            {
                cout << "右括弧后只能接运算符或者'#'和')'！" << endl;
                cout << "****************************"<<endl<<endl;
                return ERROR;
            }
        }
        if(s[i] == '.' && (isMARK(s[i+1]) || isMARK(s[i-1])))
        {
            cout << "小数点前后应为数字！" << endl;
            cout << "****************************"<<endl<<endl;
            return ERROR;
        }
    }
    if(count1 != count2)
    {
        if(count1 > count2)
        {
            cout << "右括弧缺失！" << endl;
            cout << "****************************"<<endl<<endl;
            return ERROR;
        }
        else
        {
            cout << "左括弧缺失！" << endl;
            cout << "****************************"<<endl<<endl;
            return ERROR;
        }
    }
    int count = 1;
    char theta;
    double a,b;
    int flag = 0;
    while((s[count] != '#' || charGetTop(OPTR)!='#') && count <= s.length()-1)
    {
        cout << endl;
        if(!isMARK(s[count]))
        {
            double num1 = 0;
            double num2 = 0;
            while(!isMARK(s[count]))
            {
                num1 = num1*10 + (s[count]-'0');
                count++;
                //cout << s[count];
            }//当count位置上的元素为字符时停止
            if(s[count] == '.')
            {
                count ++;
                int i = -1;
                while(!isMARK(s[count]))
                {
                    num2 = num2 + (double)(s[count]-'0')*Pow(10.0,i);
                    i--;
                    count++;
                    //cout << s[count];
                }
            }
            double num = num1 + num2;
            //cout <<endl<< "num:" <<num<<endl;
            //cout << "num1:" << num1<<"  num2:" << num2<<endl;
            doublePush(OPND,num);
        }
        else
        {
            switch(Precede(charGetTop(OPTR),s[count]))
            {
                case '<':
                    {
                        charPush(OPTR,s[count]);
                        count++;
                        break;
                    }
                case '=':
                    {
                        charPop(OPTR,theta);
                        count++;
                        break;
                    }
                case '>':
                    {
                        charPop(OPTR,theta);
                        doublePop(OPND,b);
                        doublePop(OPND,a);
                        double result = Operate(a,theta,b);
                        if(result == MAX_N)
                            return ERROR;
                        else
                            doublePush(OPND,result);
                        break;
                    }
            }
        }

        cout  << endl << "运算符栈：";
        cout << "从栈顶到栈尾依次为：" << endl;
        charTraverse(OPTR);
        cout << "运算数栈：";
        cout << "从栈顶到栈尾依次为：" << endl;
        doubleTraverse(OPND);
    }
    double result = doubleGetTop(OPND);
    cout << "运算结果为：" << result << endl;
    return OK;
}

int main()
{
    ifstream infile("data.txt",ios::in);
    if(!infile.is_open())
    {
        cout << "文件无法打开！" << endl;
        exit(ERROR);
    }
    string expression[20];
    int ExpressionNum = 1;
    while(!infile.eof())
    {
        getline(infile,expression[ExpressionNum]);
        cout << ExpressionNum << ": " << expression[ExpressionNum] << endl;
        ExpressionNum++;
    }
    ExpressionNum--;
    cout << "ExpressionNum:"<<ExpressionNum<<endl;
    for(int i = 1;i <= ExpressionNum;i++)
    {
        cout << "****************************"<<endl;
        cout << i << ": ";
        GetValue(expression[i]);
    }
    system("pause"); 
    infile.close();
}
