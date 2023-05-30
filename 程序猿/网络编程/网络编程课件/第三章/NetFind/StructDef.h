struct PingInfo
{
	char timeout[30];
	char agent[30];
	char ByteCount[30];
	char requestcount[30];
	HWND hWnd;
	UINT DevNo;
};

//==============
// The IP header
//==============
typedef struct iphdr 
{
	unsigned int h_len:4;          // length of the header
	unsigned int version:4;        // Version of IP
	unsigned char tos;             // Type of service
	unsigned short total_len;      // total length of the packet
	unsigned short ident;          // unique identifier
	unsigned short frag_and_flags; // flags
	unsigned char  ttl; 
	unsigned char proto;           // protocol (TCP, UDP etc)
	unsigned short checksum;       // IP checksum
	unsigned int sourceIP;
	unsigned int destIP;

}IpHeader;

//=============
// ICMP header
//=============
typedef struct _ihdr 
{
  BYTE i_type;    // ICMP����
  BYTE i_code;    // ICMP��
  USHORT i_cksum; // ICMPУ���
  USHORT i_id;    //��ʶ�� 
  /* This is not the std header, but we reserve space for time */
  ULONG timestamp;//
}IcmpHeader;

typedef struct{
	char * pcIp;
	char * pcCommunity;
	UINT uTimeout;
	UINT uRetries;
	UINT uOidCount;				//���뺯����Oid�ĸ���
	char* apcOid[6];
	char* pcOidType;
}Input;

typedef struct{
	UINT uOidCount;				//����������Oid�ĸ������봫�뺯����Oid�ĸ�����ͬ
	LONG lErrorIndex;
	char* apcOid[6];
	char* apcValue[6];
}Output;

typedef struct{
	char IP[25];
	bool PingTong;
}PingStatus;