
#pragma once
#include <winsock2.h>
#pragma comment(lib,"WS2_32")

#define DEF_PACKET_SIZE 32
#define ECHO_REQUEST 8
#define ECHO_REPLY 0

struct IPHeader{
    BYTE m_byVerHLen;
    BYTE m_byTOS;
    USHORT m_usTotalLen;
    USHORT m_usID;
    USHORT m_usFlagFragOffset; //3位标志+13位片偏移
    BYTE m_byTTL; //TTL
    BYTE m_byProtocol; //协议
    USHORT m_usHChecksum; //首部检验和
    ULONG m_ulSrcIP; //源IP地址
    ULONG m_ulDestIP; //目的IP地址
};

struct ICMPHeader{
    BYTE m_byType;
    BYTE m_byCode;
    USHORT m_usChecksum;
    USHORT m_usID;
    USHORT m_usSeq;
    ULONG m_ulTimeStamp;
};

struct PingReply{
    USHORT m_usSeq;
    DWORD m_dwRoundTripTime;
    DWORD m_dwBytes;
    DWORD m_dwTTL;
};

class CPing{
private:
    SOCKET m_sockRaw;
    WSAEVENT m_event;
    USHORT m_usCurrentProcID;
    char *m_szICMPData;
    BOOL m_bIsInitSucc;
    static USHORT s_usPacketSeq;

public:
    CPing();
    ~CPing();
    BOOL Ping(DWORD dwDestIP,PingReply *pPingReply=NULL,DWORD dwTimeout=2000);
    BOOL Ping(char *szDestIP,PingReply *pPingReply=NULL,DWORD dwTimeout=2000);

private:
    BOOL PingCore(DWORD dwDestIP,PingReply *pPingReply,DWORD dwTimeout);
    USHORT CalCheckSum(USHORT *pBuffer,int nSize);
    ULONG GetTickCountCalibrate();
};
