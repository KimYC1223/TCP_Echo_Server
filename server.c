#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>



#define BUF_SIZE 1024



int main(int argc , char * argv[])

{

int serv_sock , clnt_sock;    //서버 소켓 , 클라이언트 소켓을 생성

char message[BUF_SIZE];   //받아들일 메시지를 저장할 변수

int str_len , i;                    // 메시지의 길이를 저장할 str_len , for문에 사용할 i 변수 



struct sockaddr_in serv_adr; //서버 소켓 정보를 저장할 구조체

struct sockaddr_in clnt_adr;  // 클라이언트 소켓 정보를 저장할 구조체

socklen_t clnt_adr_sz;         // 클라이언트 소켓 정보를 저장할 구조체의 길이를 저장할 변수 



if (argc != 2) {     // 실행시 필요한 포트번호를 입력하지 않았을 경우 실행하는 오류 문구

printf("Usage : %s <port>\n" , argv[0]);

exit(1);

}



serv_sock = socket (PF_INET , SOCK_STREAM , 0); //서버 소켓 생성(IPv4 , TCP/IP 방식)



if (serv_sock == -1) //소켓 생성 오류시 메시지

{

printf("socket() error\n");

}



memset (&serv_adr , 0 , sizeof(serv_adr)); //서버 소켓의 정보를 담을 구조체를 0으로 초기화 한다.



        /*

         * 서버 소켓의 정보를 저장하는 구조체의 멤버변수 값 입력

         */

serv_adr.sin_family = AF_INET; //IPv4 를 사용

serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); //모든 아이피의 접근을 허용. 16진수로 변경해서 저장

serv_adr.sin_port = htons(atoi(argv[1])); //프로그램 실행시 입력된 포트번호를 10진수로 변경해서 저장





        // 구조체의 정보를 이용해서 서버 소켓에 bind

if (bind(serv_sock , (struct sockaddr *)&serv_adr , sizeof(serv_adr)) == -1)

printf("bind() error\n");



        // 받아들일 준비를 한다. 인자에 5라는 숫자는 대기 클라이언트의 숫자가 최대 5개라는 의미이다.

if (listen (serv_sock , 5) == -1)

printf("listen() error\n");



clnt_adr_sz = sizeof(clnt_adr); //클라이언트 구조체의 크기를 구한다.



for (i = 0; i < 5; i++)

{

               //클라이언트의 소켓으로부터 데이터를 받아들인다.

clnt_sock = accept (serv_sock , (struct sockaddr *)&clnt_adr , &clnt_adr_sz);

if(clnt_sock == -1)

printf("accept() error\n");



else

printf("Connected client %d\n" , i+1);



                //받은 데이터를 클라이언트 소켓을 통해 다시 돌려준다.

while ((str_len = read (clnt_sock , message , BUF_SIZE)) != 0)

write (clnt_sock , message , str_len);



close(clnt_sock); //전송 완료 후 클라이언트와의 연결을 종료한다.

}



close (serv_sock);       //서버소켓을 닫는다.

return 0;

}

