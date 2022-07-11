#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <thread>


#include <chrono>
#include <cmath>
#include <future>
#include <iostream>




struct flightmode
{
    int flightmode;
    float value;   
}fm;

struct healthCheck
{
    int uavID;
    int alive;
}UAV;



void tactical_update1(int sockfd,void *buf,struct sockaddr *src_addr, socklen_t *addrlen, int *returnvalue)
{

    int prev=-1;
    int tactical_change=1;

    while(true)
    {
        int retval = recvfrom(sockfd,buf, 10000, 0,src_addr,addrlen);
        UAV = *(healthCheck*)buf;

        if(retval>0)
        {   
            // std::cout<<"UAV2 on :"<< retval <<std::endl;
            tactical_change = 1*prev;
            *returnvalue = 1; 
            prev = 1;

        }
      
        else
        {
            // std::cout<<"UAV2 off :"<< retval <<std::endl;
            tactical_change = -1*prev;
            *returnvalue = 0;  
            prev = -1;
        }     
        
        // std::cout<<tactical_change<<std::endl;
        if (tactical_change<0)
        {
            std::cout<<""<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<"-----------warning---------"<<std::endl;
            std::cout<<"    UAV Number changed !!! "<<std::endl;
            std::cout<<"please check available UAVs"<<std::endl;
            std::cout<<"          <press 9>        "<<std::endl;
            std::cout<<"---------------------------"<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<""<<std::endl;
            std::cout<<""<<std::endl;
            using std::chrono::seconds;
            using namespace std::this_thread;

                       
        }

    }
}


// void checkUAV(int uav1,int uav2,int uav3,int *number)
// {
//     int UAVhealth1=0;
//     int UAVhealth2=0;
//     int UAVhealth3=0;
    
//     using std::chrono::seconds;
//     using namespace std::this_thread;
//     while(true)
//     {
//         std::cout << uav1 <<" "<< uav2 <<" "<< uav3 <<" "<<std::endl;
//         if(uav1>0)
//         {
//             UAVhealth1 = 1;
//             std::cout<<"UAV 1 is on"<<std::endl;
//         }    
//         if(uav2>0)
//         {
//             UAVhealth2 = 1;
//             std::cout<<"UAV 2 is on"<<std::endl;
//         } 
//         if(uav3>0)
//         {
//             UAVhealth3 = 1;
//             std::cout<<"UAV 3 is on"<<std::endl;
//         } 
//         if(uav1<=0)
//         {
//             UAVhealth1 = 0;
//         } 
//         if(uav2<=0)
//         {
//             UAVhealth2 = 0;
//         } 
//         if(uav3<=0)
//         {
//             UAVhealth3 = 0;
//         }   

//         *number = UAVhealth1 + UAVhealth2 + UAVhealth3;

//         std::cout<<"Number of UAV is: "<<UAVhealth1 + UAVhealth2 + UAVhealth3<<std::endl;

//         sleep_for(seconds(2));
      
//     }
// }



int main(void)
{
    
    int state_UAV1=0;
    int state_UAV2=0;
    int state_UAV3=0;
    int UAVnum=0;


    int socket1;
    struct sockaddr_in servaddr1;
    bzero(&servaddr1,sizeof(servaddr1));
    servaddr1.sin_family = AF_INET;
    servaddr1.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr1.sin_port=htons(32000);
    socket1 = socket(AF_INET, SOCK_DGRAM, 0);

    int socket2;
    struct sockaddr_in servaddr2;
    bzero(&servaddr2,sizeof(servaddr2));
    servaddr2.sin_family = AF_INET;
    servaddr2.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr2.sin_port=htons(32001);
    socket2 = socket(AF_INET, SOCK_DGRAM, 0);

    int socket3;
    struct sockaddr_in servaddr3;
    bzero(&servaddr3,sizeof(servaddr3));
    servaddr3.sin_family = AF_INET;
    servaddr3.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr3.sin_port=htons(32002);
    socket3 = socket(AF_INET, SOCK_DGRAM, 0);

    //UDP for receiving data from UAV 1-------------------------------------------------------------------
    char * Buffer11 = (char *)malloc(1000);
    int dronesock11;
    

    struct sockaddr_in servaddr11, from11;
    socklen_t fromlen11;

    bzero(&from11, sizeof(from11));
    bzero(&servaddr11, sizeof(servaddr11));

    servaddr11.sin_family = AF_INET;
    servaddr11.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr11.sin_port=htons(10100);

    dronesock11 = socket(AF_INET, SOCK_DGRAM, 0);
    struct timeval optVal ={1,0};
    int optLen = sizeof(optVal);
    setsockopt(dronesock11,SOL_SOCKET,SO_RCVTIMEO,&optVal,optLen);
    bind(dronesock11,(struct sockaddr *)&servaddr11,sizeof(servaddr11));
    //UDP for receiving data from UAV 1---------------------------------------------------------------------


    //UDP for receiving data from UAV 2-------------------------------------------------------------------
    char * Buffer22 = (char *)malloc(1000);
    healthCheck UAV;
    int dronesock22;
    

    struct sockaddr_in servaddr22, from22;
    socklen_t fromlen22;

    bzero(&from22, sizeof(from22));
    bzero(&servaddr22, sizeof(servaddr22));

    servaddr22.sin_family = AF_INET;
    servaddr22.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr22.sin_port=htons(20100);

    dronesock22 = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(dronesock22,SOL_SOCKET,SO_RCVTIMEO,&optVal,optLen);
    
    bind(dronesock22,(struct sockaddr *)&servaddr22,sizeof(servaddr22));
    //UDP for receiving data from UAV 2---------------------------------------------------------------------

    //UDP for receiving data from neighbor 3-------------------------------------------------------------------
    char * Buffer33 = (char *)malloc(1000);
    int dronesock33;
    

    struct sockaddr_in servaddr33, from33;
    socklen_t fromlen33;

    bzero(&from33, sizeof(from33));
    bzero(&servaddr33, sizeof(servaddr33));

    servaddr33.sin_family = AF_INET;
    servaddr33.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr33.sin_port=htons(30100);
    dronesock33 = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(dronesock33,SOL_SOCKET,SO_RCVTIMEO,&optVal,optLen);
    
    bind(dronesock33,(struct sockaddr *)&servaddr33,sizeof(servaddr33));
    //UDP for receiving data from neighbor 3---------------------------------------------------------------------

    using namespace std;
    using std::chrono::milliseconds;
    using std::chrono::seconds;
    using std::this_thread::sleep_for;

    thread t1(tactical_update1,dronesock11, Buffer11, (struct sockaddr *)&from11, &fromlen11, &state_UAV1);
    thread t2(tactical_update1,dronesock22, Buffer22, (struct sockaddr *)&from22, &fromlen22, &state_UAV2);
    thread t3(tactical_update1,dronesock33, Buffer33, (struct sockaddr *)&from33, &fromlen33, &state_UAV3);
    
    int mode;
    while(true)
    {   
        // int drone_alive = recvfrom(dronesock11, &Buffer11, 10000, 0, (struct sockaddr *)&from11, &fromlen11);
        // int drone_alive = recvfrom(dronesock, &UAV, sizeof(healthCheck), 0, (struct sockaddr *)&from, &fromlen);
        
        // cout<<drone_alive<<endl;
        // cout<<UAV.uavID<<endl;
        // cout<<UAV.alive<<endl;

        cout<<"\n";
        cout<<"\n";
        cout<<"\n";
        cout<<"------------------------------------------------------------------\n";
        cout<<" Number of UAV: "<<state_UAV1+state_UAV2+state_UAV3<<endl;
        cout<<" 1:Arming 2:Takeoff 3:Land 4:Origin 5:Follow 6:Circum 7:Formation \n";
        cout<<"------------------------------------------------------------------\n";
        cout<<"chose flight mode: "<<endl;
        cin>> mode;
        fm.flightmode = mode;
        

        int retval1 = sendto(socket1,(char *)&fm, sizeof(fm),0, (struct sockaddr *)&servaddr1,sizeof(servaddr1));



        int retval2 = sendto(socket2,(char *)&fm, sizeof(fm),0, (struct sockaddr *)&servaddr2,sizeof(servaddr2));
        int retval3 = sendto(socket3,(char *)&fm, sizeof(fm),0, (struct sockaddr *)&servaddr3,sizeof(servaddr3));      
    }
    cout << "\n\n";

    
    return 0;
}