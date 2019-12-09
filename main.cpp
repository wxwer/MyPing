
#include <winsock2.h>
#include <stdio.h>
#include "ping.h"

int main(){
    CPing objPing;
    char* szDestIP;
    printf("请输入IP地址，格式为x.x.x.x\n");
    scanf("%s",szDestIP);
    PingReply reply;
    printf("Pinging %s with %d bytes of data:\n", szDestIP, DEF_PACKET_SIZE);
    int Count=0;
    BOOL rv=0;
    while(1){
        rv=objPing.Ping(szDestIP,&reply);
        if(rv){
            printf("Reply from %s: bytes=%d time=%ld ms TTL=%ld\n", szDestIP, reply.m_dwBytes, reply.m_dwRoundTripTime, reply.m_dwTTL);
        }
        else{
            printf("time out,can't connect to %s\n",szDestIP);
        }
         Sleep(500);
         Count++;
         if(Count>=4)
            break;
    }
    return 0;
}
