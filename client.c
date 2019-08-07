#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>



#define BUF_SIZE 1024



int main(int argc , char * argv[])

{

int sock; //소켓의 파일 디스크립터를 저장할 변수

char message[BUF_SIZE]; //받을 데이터 변수

int str_len; //메시지의 크기를 저장할 변수

struct sockaddr_in serv_adr; //서버 소켓의 정보를 저장할 구조체



if (argc != 3) { // 실행에 필요한 정보를 입력하지 않았을 경우 경고문

printf("Usage : %s <IP> <port>\n",argv[0]);

exit(1);

}



sock = socket (PF_INET , SOCK_STREAM , 0); //소켓 생성(IPv4 , TCP/IP 방식)

if (sock == -1)                                           //소켓 생성 실패시

printf("socket() error\n");


memset(&serv_adr , 0 , sizeof(serv_adr)); // 서버소켓의 정보를 저장할 구조체를 초기화 한다.



        /*

         * 서버 소켓의 정보를 저장하는 구조체의 멤버변수 값 입력

         */

serv_adr.sin_family = AF_INET;

serv_adr.sin_addr.s_addr = inet_addr(argv[1]);

serv_adr.sin_port = htons (atoi (argv[2]));



        // 소켓을 이용해 서버의 정보를 지닌 구조체를 가지고 접속 요청을 한다.

if (connect (sock , (struct sockaddr * )&serv_adr , sizeof(serv_adr)) == -1)

printf("connect() error!\n");

else

puts("Connected.........");


while(1)

{

fputs ("Input message (Q to quit) : " , stdout);

fgets (message , BUF_SIZE , stdin); //입력한 데이터를 message에 넣는다.



if (!strcmp(message , "q\n") || !strcmp (message , "Q\n")) //q 나 Q를 입력하면 종료

break;



write (sock , message , strlen(message)); //서버에 message 변수의 데이터를 전송한다.

str_len = read (sock , message , BUF_SIZE-1); //서버로부터 온 메시지를 message 변수에 넣는다.

message[str_len] = 0;

printf("Message from server : %s" , message); //서버로부터 받은 메시지 출력

}



close (sock); // 소켓을 닫는다.

return 0;

}


