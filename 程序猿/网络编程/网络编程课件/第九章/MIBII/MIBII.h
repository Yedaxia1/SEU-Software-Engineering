#ifdef MIBII_EXPORTS
#define MIBII_API __declspec(dllexport)
#else
#define MIBII_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <windows.h>

#define RETRIES		3			//���ӳ��Դ���
// Buffers and pipe symbolic constants.
#define TIME_OUT			0		//�趨��ʱʱ��
#define LINE_LEN			80		//�趨�г���
#define NAME_SIZE			25		//�趨�ܵ�������
#define BYTES_READ			1000	//
#define IN_BUF_SIZE			1000
#define BYTES_WRITE			1000
#define OUT_BUF_SIZE		1000
#define MAX_PIPE_INSTANCES	100

typedef struct MIBIIPortTablePointer{
	unsigned int ifIndex;	//�˿�����
	unsigned int ifSpeed;	//�˿ڲ�����ʽ
	unsigned int ifOperStatus;	//�˿ڲ���״̬
	unsigned int ifInOctets;	//ATM�������״̬
	unsigned int ifInUcastPkts;
	unsigned int ifInNUcastPkts;
	unsigned int ifInDiscards;
	unsigned int ifInErrors;
	unsigned int ifOutOctets;
	unsigned int ifOutUcastPkts;
	unsigned int ifOutNUcastPkts;
	unsigned int ifOutDiscards;
	unsigned int ifOutErrors;
	unsigned int ifOutQLen;
	struct MIBIIPortTablePointer * pNext;
}MIBIIPortTable;

typedef struct {
	int IfNumber;
	MIBIIPortTable TableParam;
}AgentParam;

typedef struct ResultPortPointer{
	double ttl;				//�˿�������
	double lyl;				//�˿�����������
	double srdql;			//���붪����
	double scdql;			//���������
	double srcwl;			//���������
	double sccwl;			//���������
	struct ResultPortPointer * pNext;
}ResultParam;	//�����������

typedef struct{
	SQLDOUBLE	lylValve;		//���������ʵķ�ֵ
	SQLDOUBLE	srdqlValve;		//���붪���ʵķ�ֵ
	SQLDOUBLE	scdqlValve;		//��������ʵķ�ֵ
	SQLDOUBLE	srcwlValve;		//��������ʵķ�ֵ
	SQLDOUBLE	sccwlValve;		//��������ʵķ�ֵ
}ParamValve;	//��ֵ��������

typedef struct{
	SQLINTEGER	TimeOut;		//ATM�˿����������ʵķ�ֵ
	SQLINTEGER	TimeSpace;		//ATM���˿ڵ���Ԫ�����ʵķ�ֵ
	SQLCHAR 	Community[50];	//ATM���˿ڵ���Ԫ�����ʵķ�ֵ
}OperParam;		//��ֵ��������

typedef struct{
	int		gzPort;				//����˿�
	int		gzID;				//����ID
}FaultUnit;

MIBII_API int Begin_Collect( char * strIP, char * strLocalIP, int *Flag );

int ProvideAlarm();
