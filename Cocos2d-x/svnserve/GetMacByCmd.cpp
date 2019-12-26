#include <stdio.h>
#include <string.h>
#ifdef linux
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h> 
#include <net/if.h>
#endif

int GetMacByCmd(char *lpszMac) 
{  
    // 初始化返回MAC地址缓冲区
    memset(lpszMac, 0x00, sizeof(lpszMac));

    int sock_mac;  
      
    struct ifreq ifr_mac;     
      
    sock_mac = socket( AF_INET, SOCK_STREAM, 0 );  
    if( sock_mac == -1)  
    {  
        perror("create socket falise...mac/n");  
        return 0;  
    }  
      
    memset(&ifr_mac,0,sizeof(ifr_mac));     
    strncpy(ifr_mac.ifr_name, "eth0", sizeof(ifr_mac.ifr_name)-1);     
  
    if( (ioctl( sock_mac, SIOCGIFHWADDR, &ifr_mac)) < 0)  
    {  
        printf("mac ioctl error/n");  
        return 0;  
    }  
      
    sprintf(lpszMac,"%02x%02x%02x%02x%02x%02x",  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[0],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[1],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[2],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[3],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[4],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[5]);  
      
    close( sock_mac );  
    return 1;  
}

int main()
{
    char mac_addr[100];
    int bret=GetMacByCmd(mac_addr); 
    printf("bret=%d,local mac:%s \n",bret,mac_addr); 
    return 0;
}