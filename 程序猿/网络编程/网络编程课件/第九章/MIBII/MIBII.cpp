// MIBII.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <iostream.h>
#include <conio.h>
#include <malloc.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <time.h>
#include <snmp.h>
#include <mgmtapi.h>
#include <winbase.h>

#include "MIBII.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

int InitializeVarBinding( char * strOid,
						 RFC1157VarBindList &varBindings )
{	//��ʼ��������
	AsnObjectIdentifier reqObject;
	if (SnmpMgrStrToOid(strOid, &reqObject)==NULL){
		cout<<"ת��OID����!!"<<endl;
		return 1;	//ת��OID����
	}
	else
	{//��ʼ��������
		varBindings.len++; //���ñ����󶨳���
		if ((varBindings.list=(RFC1157VarBind *) SNMP_realloc(varBindings.list,sizeof(RFC1157VarBind)*varBindings.len))==NULL)
			return 2;	//�������ڴ�������
		varBindings.list[varBindings.len-1].name=reqObject; //NOTE!  structure copy
		varBindings.list[varBindings.len-1].value.asnType=ASN_NULL;//��ʼ��������ֵ������
	}
	return 0;
}

int CreateSession( LPSNMP_MGR_SESSION &session,	LPSTR Agent, LPSTR Community, INT TimeOut )
{	//�����Ự����
	if ((session = SnmpMgrOpen( Agent, Community, TimeOut, RETRIES ))==NULL){
		cout<<"���󣺽����Ựʧ�ܴ���! ����ţ�"<<GetLastError()<<endl;
		return 3;
	}
	return 0;
}

int ProvideAlarm()
{
	int nErrors = 0;
	DWORD  retCode;                      // Return code.
	CHAR   errorBuf[LINE_LEN] = "";      // Error message buffer.
	CHAR   outBuf[OUT_BUF_SIZE]  = "";   // Buffer trapping message to send.
	CHAR   sendBuf[OUT_BUF_SIZE] = "";   // Buffer used to modify message.
	DWORD  bytesWritten;                 // Used for WriteFile().
	CHAR   FileName[LINE_LEN+NAME_SIZE+2]; // Used to modify pipe/file name.
	DWORD  lastError;                    // Used to get returns from GetLastError.
	static HANDLE hPipe;                 // File or Pipe handle.
	static OVERLAPPED OverLapWrt;        // Overlapped structure
	static HANDLE     hEventWrt;         // Event handle for overlapped writes.
	sprintf( FileName, "%s%s%s", "\\\\", ".", "\\PIPE\\broker" );
	hPipe = CreateFile ( FileName,              // Pipe name.
					   GENERIC_WRITE          // Generic access, read/write.
					   | GENERIC_READ,
					   FILE_SHARE_READ        // Share both read and write.
					   | FILE_SHARE_WRITE,
					   NULL,                  // No security.
					   OPEN_EXISTING,         // Fail if not existing.
					   FILE_FLAG_OVERLAPPED,  // Use overlap.
					   NULL );                 // No template.
	if ((DWORD)hPipe == 0xFFFFFFFF){	//�жϹܵ��Ƿ�����������
		retCode = GetLastError();
		if ((retCode == ERROR_SEEK_ON_DEVICE) || (retCode == ERROR_FILE_NOT_FOUND))	nErrors = 13;	//Server�˹ܵ�û�з��ִ���Client�ˣ�
		else nErrors = 14;   //δ֪������
	}
	hEventWrt = CreateEvent (NULL, TRUE, FALSE, NULL);	//Ϊд������������ʼ��ʱ�佻��ṹ
	OverLapWrt.hEvent = hEventWrt;
	retCode = WriteFile (hPipe, "ClntName", BYTES_WRITE, &bytesWritten, &OverLapWrt);	//�������ܵ�Server��д
	if (!retCode){	//�����Ҫ�Ļ����ȴ�ʱ�佻��
		lastError = GetLastError();
		if (lastError == ERROR_IO_PENDING)	WaitForSingleObject (hEventWrt, (DWORD)-1);	//��ȴ�д����
	 }
	CloseHandle (hPipe);
	CloseHandle (hEventWrt);
	return nErrors;
}

int GetData( LPSNMP_MGR_SESSION &session,
			 BYTE requestType,
			 RFC1157VarBindList &variableBindings )
{	//�ɼ�����
	AsnInteger	errorStatus;
	AsnInteger	errorIndex;
	if (SnmpMgrRequest(session, requestType, &variableBindings,&errorStatus, &errorIndex)==NULL){
		cout<<"����SnmpGetȡ����ʧ�ܣ�ȡ������Ϊ�գ�����! ����ţ�"<< GetLastError()<<endl;
		return 4;
	}
	else{
		if (errorStatus > 0){	// The API succeeded, errors may be indicated from the remote agent.
			cout<<"���� Զ�˴����������! ����״̬��"<<errorStatus<<"������������"<<errorIndex<<endl;
			return 5;
		}
		//else cout<<"success"<<endl;
	}
	return 0;
}

int GetPortNumber( LPSNMP_MGR_SESSION session, AgentParam * varAgentParam )
{	//��ȡ�˿ڸ���
	int nError = 0;
	BYTE requestType;
	RFC1157VarBindList varBindings;
	varBindings.list = NULL;	//��ʼ����������
	varBindings.len = 0;
	nError = InitializeVarBinding( ".1.3.6.1.2.1.2.1.0", varBindings);
	if ( nError ) return nError;
	//׼������SnmpGet����
	requestType = SNMP_PDU_GET;	
	//����SnmpGet������ȡ��wtPortNumber��ֵ(�˿ڸ���)��MIB II�� ifspeed����
	nError = GetData( session, requestType, varBindings );
	if ( nError ) return nError;
	//��ȡ����ֵ�浽��Ӧ�Ĳ����ṹ��ȥ
	varAgentParam->IfNumber = varBindings.list[0].value.asnValue.number;	//MIB 2֧�ֵĶ˿���
	// �ͷű�����ռ�ı�����
	SnmpUtilVarBindListFree( &varBindings );
	return nError;
}

int GetMIB2Param( LPSNMP_MGR_SESSION session, AgentParam * varAgentParam, time_t &pPickTime )
{
	int nError = 0;
	BYTE		requestType;
	char strOid[14][100] ={
		".1.3.6.1.2.1.2.2.1.1", ".1.3.6.1.2.1.2.2.1.5",	".1.3.6.1.2.1.2.2.1.8", ".1.3.6.1.2.1.2.2.1.10",	
		".1.3.6.1.2.1.2.2.1.11", ".1.3.6.1.2.1.2.2.1.12", ".1.3.6.1.2.1.2.2.1.13", 
		".1.3.6.1.2.1.2.2.1.14", ".1.3.6.1.2.1.2.2.1.16", ".1.3.6.1.2.1.2.2.1.17", ".1.3.6.1.2.1.2.2.1.18",
		".1.3.6.1.2.1.2.2.1.19", ".1.3.6.1.2.1.2.2.1.20", ".1.3.6.1.2.1.2.2.1.21"
	};
	RFC1157VarBindList varBindings[2];
	//��ʼ����������
	varBindings[0].list = NULL;
	varBindings[0].len = 0;
	varBindings[1].list = NULL;
	varBindings[1].len = 0;
	int i;
	for (i=0; i<7; i++)	nError = InitializeVarBinding( strOid[i], varBindings[0] );
	if ( nError ) return nError;
	for (i=7; i<14; i++)	nError = InitializeVarBinding( strOid[i], varBindings[1] );
	if ( nError ) return nError;
	//׼������SnmpGetNext����
	requestType = SNMP_PDU_GETNEXT;
	struct MIBIIPortTablePointer * pFore;	//ǰָ��
	struct MIBIIPortTablePointer * pBack;	//��ָ��
	pBack = pFore = &(varAgentParam->TableParam);
	for ( i=0; i<varAgentParam->IfNumber; i++ )	{
		cout<<"Now Processing,Waiting ..."<<varAgentParam->IfNumber-i<<endl;
		nError = GetData(session,requestType,varBindings[0]);
		if ( nError ) return nError;
		nError = GetData(session,requestType,varBindings[1]);
		if ( nError ) return nError;
		//��ȡ�������ݴ浽��Ӧ�Ĳ����ṹ��ȥ
		pFore->ifIndex = varBindings[0].list[0].value.asnValue.number;
		pFore->ifSpeed = varBindings[0].list[1].value.asnValue.gauge;
		pFore->ifOperStatus = varBindings[0].list[2].value.asnValue.number;
		pFore->ifInOctets = varBindings[0].list[3].value.asnValue.counter;
		pFore->ifInUcastPkts = varBindings[0].list[4].value.asnValue.counter;
		pFore->ifInNUcastPkts = varBindings[0].list[5].value.asnValue.counter;
		pFore->ifInDiscards = varBindings[0].list[6].value.asnValue.counter;
		
		pFore->ifInErrors = varBindings[1].list[0].value.asnValue.counter;
		pFore->ifOutOctets = varBindings[1].list[1].value.asnValue.counter;
		pFore->ifOutUcastPkts = varBindings[1].list[2].value.asnValue.counter;
		pFore->ifOutNUcastPkts = varBindings[1].list[3].value.asnValue.counter;
		pFore->ifOutDiscards = varBindings[1].list[4].value.asnValue.counter;
		pFore->ifOutErrors = varBindings[1].list[5].value.asnValue.counter;
		pFore->ifOutQLen = varBindings[1].list[6].value.asnValue.gauge;
		pBack=pFore;
		pFore=new struct MIBIIPortTablePointer;
		pFore->pNext=NULL;
		pBack->pNext=pFore;
	}
	if (i>0){
		free(pFore);
		pBack=NULL;
	}
	time(&pPickTime);
	// �ͷű�����ռ�ı�����
	SnmpUtilVarBindListFree( &varBindings[0] );
	SnmpUtilVarBindListFree( &varBindings[1] );
	return nError;
}
//���ִﵽ��ֵ�Ĳ�������������Ϣ
int  DealAlarmInfo( char * strIP, FaultUnit * FaultArrary, int nFaults )
{
	int nError = 0;
	SQLHENV  henv;
	SQLHDBC  hdbc;
	SQLHSTMT hstmt;
	SQLRETURN  retcode;
	//Allocate environment handle 
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);  
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {// Set the ODBC version environment attribute 
		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {// Allocate connection handle 
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {	// Set login timeout to 5 seconds.
				SQLSetConnectAttr(hdbc, 5,(void*)SQL_LOGIN_TIMEOUT, 0);
				// Connect to data source 
				retcode = SQLConnect(hdbc, (SQLCHAR*) "PerformanceMonitor", SQL_NTS, (SQLCHAR*) "sa", SQL_NTS, (SQLCHAR*) "", SQL_NTS);
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){	// Allocate statement handle 
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){   // Process data 
						struct tm pNowTime;
						time_t nNowTime;	//������ʱ�����
						time( &nNowTime );
						pNowTime = * localtime( &nNowTime ); 
						char strSQL[511] ;
						for (int i=0; i<nFaults; i++){
							sprintf( strSQL, "insert faultinfo values('%s', %d, %d, '%d-%d-%d %d:%d:%d', %d)", strIP, FaultArrary[i].gzPort, FaultArrary[i].gzID, pNowTime.tm_year+1900, pNowTime.tm_mon+1, pNowTime.tm_mday, pNowTime.tm_hour, pNowTime.tm_min, pNowTime.tm_sec, 0 );
							SQLRETURN rc = ::SQLExecDirect(hstmt,(unsigned char *)strSQL,SQL_NTS);
							if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) nError = 11;
						}
						ProvideAlarm();
					}
					else nError = 10;
					SQLDisconnect(hdbc); 
				}
				else nError = 9;
				SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
			}
			else nError = 8;
		}
		else nError = 7;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}
	else nError = 6;
	return nError;
}
//����X��Yʱ�̵Ĳ���������������
int GetResultParam( long TimeSlot, char * strIP, AgentParam * AgentParamX, AgentParam * AgentParamY, ResultParam * varResultParam, ParamValve * varValve, time_t &pPickTimeX, time_t &pPickTimeY )
{
	int nError = 0;
	int i;
	struct MIBIIPortTablePointer * pForeX;
	struct MIBIIPortTablePointer * pForeY;
	struct ResultPortPointer * pFore;	//ǰָ��
	struct ResultPortPointer * pBack;	//��ָ��
	pForeX = &(AgentParamX->TableParam);
	pForeY = &(AgentParamY->TableParam);
	pBack = pFore = varResultParam;
	double TimeSpan;
	TimeSpan = difftime( pPickTimeY, pPickTimeX );
	if (AgentParamX->IfNumber == AgentParamY->IfNumber){
		for ( i=0; i<AgentParamY->IfNumber; i++ ){
			if ((pForeY->ifOperStatus == pForeX->ifOperStatus)&&(pForeY->ifOperStatus=1)){//Port "up"
				FaultUnit FaultArray[5];	//��������
				int nFaults = 0;
				unsigned long InTotalBytes, OutTotalBytes;
				unsigned long FrameDiscarded, FrameErrors, UcastFramesSwitched, NUcastFramesSwitched;
				InTotalBytes = pForeY->ifInOctets-pForeX->ifInOctets;
				OutTotalBytes = pForeY->ifOutOctets-pForeX->ifOutOctets;
				pFore->ttl = (double)(InTotalBytes + OutTotalBytes) / (TimeSpan * 1000.0);
				if (pForeY->ifSpeed != 0) pFore->lyl = (  pFore->ttl * 1000.0 * 8 ) / ( double ) pForeY->ifSpeed;
				else pFore->lyl = 0.0;
				if (pFore->lyl >= varValve->lylValve){ //�˿������ʴﵽ���ޱ���ֵ
						FaultArray[nFaults].gzID = 1;	//����ID
						FaultArray[nFaults].gzPort = i;	//���ֱ����Ķ˿�
						nFaults++;
				}
				//�������
				FrameDiscarded = pForeY->ifInDiscards -pForeX->ifInDiscards;
				FrameErrors = pForeY->ifInErrors - pForeX->ifInErrors;
				UcastFramesSwitched = pForeY->ifInUcastPkts - pForeX->ifInUcastPkts;
				NUcastFramesSwitched = pForeY->ifInNUcastPkts - pForeX->ifInNUcastPkts;
				if ((UcastFramesSwitched + NUcastFramesSwitched) != 0){
					pFore->srdql = (double)FrameDiscarded/(double)(UcastFramesSwitched + NUcastFramesSwitched);
					pFore->srcwl = (double)FrameErrors/(double)(UcastFramesSwitched + NUcastFramesSwitched);
				}
				else{
					pFore->srdql = 0.0;
					pFore->srcwl = 0.0;
				}
				if (pFore->srdql >= varValve->srdqlValve){ //�˿����붪���ʴﵽ���ޱ���ֵ
						FaultArray[nFaults].gzID = 2;	//����ID
						FaultArray[nFaults].gzPort = i;	//���ֱ����Ķ˿�
						nFaults++;
				}
				if (pFore->srcwl >= varValve->srcwlValve){ //�˿���������ʴﵽ���ޱ���ֵ
						FaultArray[nFaults].gzID = 4;	//����ID
						FaultArray[nFaults].gzPort = i;	//���ֱ����Ķ˿�
						nFaults++;
				}
				//�������
				FrameDiscarded = pForeY->ifOutDiscards -pForeX->ifOutDiscards;
				FrameErrors = pForeY->ifOutErrors - pForeX->ifOutErrors;
				UcastFramesSwitched = pForeY->ifOutUcastPkts - pForeX->ifOutUcastPkts;
				NUcastFramesSwitched = pForeY->ifOutNUcastPkts - pForeX->ifOutNUcastPkts;
				if ((UcastFramesSwitched + NUcastFramesSwitched)!=0){
					pFore->scdql = (double)FrameDiscarded/(double)(UcastFramesSwitched + NUcastFramesSwitched);
					pFore->sccwl = (double)FrameErrors/(double)(UcastFramesSwitched + NUcastFramesSwitched);
				}
				else{
					pFore->scdql = 0.0;
					pFore->sccwl = 0.0;
				}
				if (pFore->scdql >= varValve->scdqlValve){ //�˿���������ʴﵽ���ޱ���ֵ
						FaultArray[nFaults].gzID = 3;	//����ID
						FaultArray[nFaults].gzPort = i;	//���ֱ����Ķ˿�
						nFaults++;
				}
				if (pFore->sccwl >= varValve->sccwlValve){ //�˿���������ʴﵽ���ޱ���ֵ
						FaultArray[nFaults].gzID = 5;	//����ID
						FaultArray[nFaults].gzPort = i;	//���ֱ����Ķ˿�
						nFaults++;
				}
				if ( nFaults > 0 ) DealAlarmInfo( strIP, FaultArray, nFaults );	//
				pBack=pFore;
				pFore=new struct ResultPortPointer;
				pFore->pNext=NULL; pFore->ttl=0; pFore->lyl=pFore->sccwl=pFore->scdql=pFore->srcwl=pFore->srdql=0.0;
				pBack->pNext=pFore;
				pForeX=pForeX->pNext; pForeY=pForeY->pNext;
			}
			else {//�˿�״̬��һ��OR����down
				pBack=pFore;
				pFore=new struct ResultPortPointer;
				pFore->pNext=NULL; pFore->ttl=0; pFore->lyl=pFore->sccwl=pFore->scdql=pFore->srcwl=pFore->srdql=0.0;
				pBack->pNext=pFore;
				pForeX=pForeX->pNext; pForeY=pForeY->pNext;
			}
		}
		if (i>0){
			free(pFore);
			pBack->pNext=NULL;
		}
	}
	else{ //�˿���Ϊ0
	}
	return nError;
}

int StoreResultParam( char *strIP, long PortNumber, ResultParam * varResultParam )
{
	int nError = 0;
	SQLHENV  henv;
	SQLHDBC  hdbc;
	SQLHSTMT hstmt;
	SQLRETURN  retcode;
	//Allocate environment handle 
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);  
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {// Set the ODBC version environment attribute 
		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {// Allocate connection handle 
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {	// Set login timeout to 5 seconds.
				SQLSetConnectAttr(hdbc, 5,(void*)SQL_LOGIN_TIMEOUT, 0);
				// Connect to data source 
				retcode = SQLConnect(hdbc, (SQLCHAR*) "PerformanceMonitor", SQL_NTS, (SQLCHAR*) "sa", SQL_NTS, (SQLCHAR*) "", SQL_NTS);
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){	// Allocate statement handle 
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){   // Process data 
						struct ResultPortPointer * pFore;	//ǰָ��
						pFore = varResultParam;
						for (int i=0;i<PortNumber;i++){
							struct tm pNowTime;
							time_t nNowTime;	//������ʱ�����
							time( &nNowTime );
							pNowTime = * localtime( &nNowTime ); 
							char strSQL[511] ;
							sprintf( strSQL, "insert MIBIIPerformance values('%s',%ld,'%d-%d-%d %d:%d:%d',%g,%g,%g,%g,%g,%g)",strIP, i, pNowTime.tm_year+1900, pNowTime.tm_mon+1, pNowTime.tm_mday, pNowTime.tm_hour, pNowTime.tm_min, pNowTime.tm_sec, pFore->ttl, pFore->lyl, pFore->srdql, pFore->scdql, pFore->srcwl, pFore->sccwl );
							SQLRETURN rc = ::SQLExecDirect(hstmt,(unsigned char *)strSQL,SQL_NTS);
							if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) nError = 11;
							pFore=pFore->pNext;
						}
					}
					else nError = 10;
					SQLDisconnect(hdbc); 
				}
				else nError = 9;
				SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
			}
			else nError = 8;
		}
		else nError = 7;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}
	else nError = 6;
	return nError;
}

//�����ݿ��л�ȡ��ֵ����
int GetParamValve( ParamValve * varValve, char * strIP )
{
	int nError = 0;
	SQLHENV  henv;
	SQLHDBC  hdbc;
	SQLHSTMT hstmt;
	SQLRETURN  retcode;
	//��Ӧ�뷧ֵ�����ĳ���
	SQLINTEGER  cblyl, cbsrdql, cbscdql, cbsrcwl,cbsccwl;
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);  //Allocate environment handle 
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
	{	// Set the ODBC version environment attribute
		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
		{	// Allocate connection handle 
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
			{	// Set login timeout to 5 seconds. 
				SQLSetConnectAttr(hdbc, 5,(void*)SQL_LOGIN_TIMEOUT, 0);
				retcode = SQLConnect(hdbc, (SQLCHAR*) "PerformanceMonitor", SQL_NTS, (SQLCHAR*) "sa", SQL_NTS, (SQLCHAR*) "", SQL_NTS);
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				{	// Allocate statement handle 
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
					{	// Process data 
						char sql[511];
						sprintf(sql,"select lylfz, srdqlfz, scdqlfz, srcwlfz, sccwlfz from MIBIIValve where ip='%s'",strIP);
						SQLExecDirect(hstmt, (unsigned char *)sql, SQL_NTS);
						SQLBindCol(hstmt, 1, SQL_C_DOUBLE, &varValve->lylValve, 0, &cblyl);
						SQLBindCol(hstmt, 2, SQL_C_DOUBLE, &varValve->srdqlValve, 0, &cbsrdql);
						SQLBindCol(hstmt, 3, SQL_C_DOUBLE, &varValve->scdqlValve, 0, &cbscdql);
						SQLBindCol(hstmt, 4, SQL_C_DOUBLE, &varValve->srcwlValve, 0, &cbsrcwl);
						SQLBindCol(hstmt, 5, SQL_C_DOUBLE, &varValve->sccwlValve, 0, &cbsccwl);
						if ((retcode=SQLFetch(hstmt)) == SQL_NO_DATA) nError = 12;
						SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
					}
					else nError = 10;
					SQLDisconnect(hdbc); 
				}
				else nError = 9;
				SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
			}
			else nError = 8;
		}
		else nError = 7;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}
	else nError = 6;
	return nError;
}	
int	GetOperParam( char *strLocalIP, char *strIP, OperParam *varOperParam )
{
	int nError = 0;
	SQLHENV  henv;
	SQLHDBC  hdbc;
	SQLHSTMT hstmt;
	SQLRETURN  retcode;
	//��Ӧ����������ĳ���
	SQLINTEGER cbTimeOut, cbCommunity, cbTimeSpace;
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);  /*Allocate environment handle */
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
	{	// Set the ODBC version environment attribute
		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
		{	// Allocate connection handle 
			retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc); 
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
			{	// Set login timeout to 5 seconds.
				SQLSetConnectAttr(hdbc, 5,(void*)SQL_LOGIN_TIMEOUT, 0);
				retcode = SQLConnect(hdbc, (SQLCHAR*) "PerformanceMonitor", SQL_NTS, (SQLCHAR*) "sa", SQL_NTS, (SQLCHAR*) "", SQL_NTS);
				if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
				{	// Allocate statement handle 
					retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 
					if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
					{	// Process data 
						char sql[511];
						sprintf( sql, "select timeout, community, timespace from CollectParam where collectip='%s' and collectedip='%s'", strLocalIP, strIP );
						SQLExecDirect(hstmt, (unsigned char *)sql, SQL_NTS);
						SQLBindCol(hstmt, 1, SQL_C_SLONG, &varOperParam->TimeOut, 0, &cbTimeOut );
						SQLBindCol(hstmt, 2, SQL_C_CHAR, &varOperParam->Community, 50, &cbCommunity );
						SQLBindCol(hstmt, 3, SQL_C_SLONG, &varOperParam->TimeSpace, 0, &cbTimeSpace );
						if ((retcode=SQLFetch(hstmt)) == SQL_NO_DATA) nError = 12;
						for (int i= cbCommunity-1; i>0;i--)	if (isalnum(varOperParam->Community[i])) break;
						varOperParam->Community[i+1] = '\0';
						SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
					}
					else nError = 10;
					SQLDisconnect(hdbc); 
				}
				else nError = 9;
				SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
			}
			else nError = 8;
		}
		else nError = 7;
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	}
	else nError = 6;
	return nError;
}

MIBII_API int Begin_Collect( char * strIP, char * strLocalIP, char *FlagIP, int *Flag )
{
	//ϵͳ���ͱ���
	int					nError=0;
	LPSTR	Agent;
	LPSTR	Community;
	INT		TimeOut;
	LPSNMP_MGR_SESSION	session;
	long				PollingTime;
	time_t				pPickTimeX, pPickTimeY;
	ParamValve			varValve;
	AgentParam			AgentParamX, AgentParamY;	/*�ռ���Ĳ����ṹ*/
	ResultParam			varResultParam;
	OperParam			varOperParam;
	BOOL ExitFlag = FALSE;
	AgentParamX.TableParam.pNext = AgentParamY.TableParam.pNext = NULL;
	varResultParam.pNext = NULL;	varResultParam.ttl=0;
	varResultParam.lyl=varResultParam.sccwl=varResultParam.scdql=varResultParam.srcwl=varResultParam.srdql=0.0;
	GetOperParam( strLocalIP, strIP, &varOperParam );	//
	PollingTime = varOperParam.TimeSpace * 1000;
	time(&pPickTimeX);
	time(&pPickTimeY);
	//׼������һ���Ự����session
	Agent = (LPSTR)SNMP_malloc(strlen(strIP) + 1);	//��ʼ��agent address...
	strcpy( Agent, strIP);
	Community = (LPSTR)SNMP_malloc(strlen((const char *)varOperParam.Community) + 1);	//��ʼ��agent community...
	strcpy( Community, (const char *)varOperParam.Community);
	TimeOut = varOperParam.TimeOut;
	nError = CreateSession( session, Agent, Community,TimeOut );	//�����Ự����
	if (nError)	return nError;
	//ȡ��Xʱ��Ĳ���
	nError = GetPortNumber( session, &AgentParamX );		//�˿ڸ�������
	if (nError)	return nError;
	nError = GetMIB2Param( session, &AgentParamX, pPickTimeY );		//MIB 2�еı����
	if (nError)	return nError;
	//��Ϣһ����ѭ���ڵ�ʣ�ಿ��
	cout<<"sleeping,please waiting..."<<endl;
	Sleep( PollingTime );
	while ( (!nError) && ( !ExitFlag ) )
	{	
		//ȡ��Yʱ��Ĳ���
		nError = GetPortNumber( session, &AgentParamY );		//�˿ڸ�������
		if (nError) return nError;
		nError = GetMIB2Param( session, &AgentParamY, pPickTimeY );		//MIB 2�еı����
		if (nError)	return nError;
		nError = GetParamValve( &varValve, strIP );	//�ӷ�ֵ��������ȡ�÷�ֵ����
		if (nError!=0)	varValve.lylValve = varValve.sccwlValve = varValve.scdqlValve = varValve.srcwlValve = varValve.srdqlValve =1.0;
		nError = GetResultParam( PollingTime, strIP, &AgentParamX, &AgentParamY, &varResultParam, &varValve, pPickTimeX, pPickTimeY ); //����X��Yʱ�̵Ĳ������õ��������
		if ((nError!=0)&&(nError!=16))	return nError;
		nError = StoreResultParam( strIP, AgentParamY.IfNumber, &varResultParam); //����������洢�����ݿ���
		if (nError)	return nError;
		AgentParamX = AgentParamY; //��Yʱ�̵Ĳ������浽Xʱ����ȥ	
		if ( (*Flag==3) && (!strcmp(strIP,FlagIP)) ){
			ExitFlag = TRUE;
			return nError;
		}
		if ((*Flag==1) && (!strcmp(strIP,FlagIP))){ //��ȡ�ռ������еĲ���
			GetOperParam( strLocalIP, strIP, &varOperParam );	//
			PollingTime = varOperParam.TimeSpace * 1000;		//
			Agent = (LPSTR)SNMP_malloc(strlen(strIP) + 1);		//��ʼ��agent address...
			strcpy( Agent, strIP);								//
			Community = (LPSTR)SNMP_malloc(strlen((const char *)varOperParam.Community) + 1);	//��ʼ��agent community...
			strcpy( Community, (const char *)varOperParam.Community);
			TimeOut = varOperParam.TimeOut;
			nError = CreateSession( session, Agent, Community,TimeOut );	//�����Ự����
			*Flag = 0;	//
		}
		cout<<"sleeping,please waiting..."<<endl;
		Sleep(PollingTime);
	}
	
	return nError;
}

