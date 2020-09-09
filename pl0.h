#pragma once

#include <stdio.h>

#define norw 13     /* �����ָ��� */
#define txmax 100   /* ���ֱ����� */
#define nmax 14     /* ���ֵ����λ�� */
#define al 10       /* ��ʶ������󳤶� */
#define amax 2047   /* �������ֵ */
#define levmax 3    /* ����������Ƕ���������� [0,  levmax]*/
#define cxmax 500   /* ��������������� */
#define stacksize 500    /* ����ִ��ʱʹ�õ�ջ */

//��16��������������13�������ֻ������֡���ʶ������
enum symbol {
    nul, ident, number,
    becomes, plus, minus, times, slash,
    eql, neq, lss, leq, gtr, geq,
    lparen, rparen, comma, semicolon, period,
    beginsym, endsym, ifsym, thensym, whilesym,
    dosym, varsym, constsym, oddsym, procsym, callsym,
    readsym, writesym,
};
#define symnum 32	/* ������ */

/* ��������� */
enum fct {
    lit, opr, lod,
    sto, cal, inte,
    jmp, jpc,
};
#define fctnum 8	/* ����������� */

/* ���������ṹ */
struct instruction
{
    enum fct f; /* ���������ָ�� */
    int l;      /* ���ò���������Ĳ�β� */
    int a;      /* ����f�Ĳ�ͬ����ͬ */
};

FILE* fas;  /* ������ֱ� */
FILE* fa;   /* ������������ */
FILE* fa1;  /* ���Դ�ļ�������ж�Ӧ���׵�ַ */
FILE* fa2;  /* ������ */

FILE* mips; //���mips������

bool listswitch;    /* ��ʾ������������ */
bool tableswitch;   /* ��ʾ���ֱ���� */
char ch;            //���ڴʷ���������������һ�δ��ļ��ж������ַ�,getchʹ��
enum symbol sym;    // �ʷ�������������֮�ã�������һ��ʶ������� ����token ������
char id[al + 1];    // �ʷ�������������֮�ã���ǰident, �����һ���ֽ����ڴ��0
int num;            // �ʷ�������������֮�ã���ǰnumber
int cc, ll;          // getchʹ�õļ�������cc��ʾ��ǰ�ַ�(ch)��λ�ã����л���������ָ��,llΪ�л���������
int cx;             // ���������ָ��, ȡֵ��Χ[0, cxmax-1],��������ģ������ cx ��ָλ�������µĴ���
char line[81];      //�л����������ڴ��ļ�����һ�У����ʷ�������ȡ����ʱ֮��
char a[al + 1];       /* �ʷ���������������ʱ������ڷ����Ĵ�, �����һ���ֽ����ڴ��0 */
struct instruction code[cxmax]; /* ��ű���õ����� PCODE�������������� */
char word[norw][al];        /* ������ */
enum symbol wsym[norw];     /* �����ֶ�Ӧ�ķ���ֵ */
enum symbol ssym[256];      /* ���ַ��ķ���ֵ */
char mnemonic[fctnum][5];   //�� PCODE ָ�����Ƿ���
bool declbegsys[symnum];    /* ��ʾ������ʼ�ķ��ż��� */
bool statbegsys[symnum];    /* ��ʾ��俪ʼ�ķ��ż��� */
bool facbegsys[symnum];     /* ��ʾ���ӿ�ʼ�ķ��ż��� */

/* ���ű��е����� */
enum object {
    constant,
    variable,
    procedur,
    array       //lkz���Ӳ���
};
/* ���ű�ṹ */
struct tablestruct
{
    char name[al];      /* ���� */
    enum object kind;   /* ���ͣ�const, var, array or procedure */
    int val;            /* ��ֵ����constʹ�� */
    int level;          /* ����Ǳ������������,��Ų�ƫ�Ƶ�ַ�ʹ�С*/
    int adr;            /* ��ַ����const��ʹ�� */
    int size;           /* ��Ҫ������������ռ�, ��procedureʹ�� */
};

struct tablestruct table[txmax]; /* ���ű� */

FILE* fin;
FILE* fout;
char fname[al];
int err; //���������

#pragma region ���Ǻ�����������������һ��


/* �������лᷢ��fatal errorʱ������-1��֪�������ĺ����������˳����� */
#define getsymdo                      if(-1 == getsym()) return -1
#define getchdo                       if(-1 == getch()) return -1
#define testdo(a, b, c)               if(-1 == test(a, b, c)) return -1
#define gendo(a, b, c)                if(-1 == gen(a, b, c)) return -1
#define expressiondo(a, b, c)         if(-1 == expression(a, b, c)) return -1
#define factordo(a, b, c)             if(-1 == factor(a, b, c)) return -1
#define termdo(a, b, c)               if(-1 == term(a, b, c)) return -1
#define conditiondo(a, b, c)          if(-1 == condition(a, b, c)) return -1
#define statementdo(a, b, c)          if(-1 == statement(a, b, c)) return -1
#define constdeclarationdo(a, b, c)   if(-1 == constdeclaration(a, b, c)) return -1
#define vardeclarationdo(a, b, c)     if(-1 == vardeclaration(a, b, c)) return -1
#pragma endregion
#pragma region ������
void error(int n);
int getsym();
int getch();
void init();
int gen(enum fct x, int y, int z);
int test(bool* s1, bool* s2, int n);
int inset(int e, bool* s);
int addset(bool* sr, bool* s1, bool* s2, int n);
int subset(bool* sr, bool* s1, bool* s2, int n);
int mulset(bool* sr, bool* s1, bool* s2, int n);
int block(int lev, int tx, bool* fsys);
void interpret();
int factor(bool* fsys, int* ptx, int lev);
int term(bool* fsys, int* ptx, int lev);
int condition(bool* fsys, int* ptx, int lev);
int expression(bool* fsys, int* ptx, int lev);
int statement(bool* fsys, int* ptx, int lev);
void listcode(int cx0);
int vardeclaration(int* ptx, int lev, int* pdx);
int constdeclaration(int* ptx, int lev, int* pdx);
int position(char* idt, int tx);
void enter(enum object k, int* ptx, int lev, int* pdx);
int base(int l, int* s, int b);
#pragma endregion


//������Ϣ����
const char* err_msg[] = {
    "",//0
    "'='д����':='",//1
    "'='����Ҫ��һ������",//2
    "��ʶ������Ҫ��һ����=��",//3
    "��const��var��procedure����Ҫ��һ����ʶ��",//4
    "ȱ��','����';'",//5
    "����������",//6
    "��Ҫ����",//7
    "���������һ������ȷ�ķ���",//8
    "����'.'�������޷���������",//9
    "����';'",//10
    "����δ�����ı�ʶ����",//11
    "�Ƿ���ֵ",//12
    "����':='",//13
    "call֮��ȱ�ٱ�ʶ����",//14
    "call֮���ʶ�����ǹ��̣�",//15
    "����then",//16
    "ȱ��';'����end",//17
    "����do",//18
    "���Ŵ���",//19
    "���������δ���ֲ���������#��>���ȣ�",//20
    "���ܰѹ��̵ı�ʶ�����ڱ��ʽ�",//21
    "",//22
    "���ź��治�ܸ���<����>",//23
    "���Ų�����Ϊ<���ʽ>�Ŀ�ʼ��",//24
    "",//25
    "",//26
    "",//27
    "",//28
    "",//29
    "���ֹ���",//30
    "���������ɶ�������ֵ��",//31
    "������������Ƕ�ײ���������̫������",//32
    "��ʽ����Ӧ��������')'",//33
    "��ʽ����Ӧ��������'('",//34
    "read�ﲻ�Ǳ�ʶ��ID,��ñ�ʶ��δ����",//35
};

//�������ɻ�����ʱ����
char immediate[20];
