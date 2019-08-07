#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>



#define BUF_SIZE 1024



int main(int argc , char * argv[])

{

int sock; //������ ���� ��ũ���͸� ������ ����

char message[BUF_SIZE]; //���� ������ ����

int str_len; //�޽����� ũ�⸦ ������ ����

struct sockaddr_in serv_adr; //���� ������ ������ ������ ����ü



if (argc != 3) { // ���࿡ �ʿ��� ������ �Է����� �ʾ��� ��� ���

printf("Usage : %s <IP> <port>\n",argv[0]);

exit(1);

}



sock = socket (PF_INET , SOCK_STREAM , 0); //���� ����(IPv4 , TCP/IP ���)

if (sock == -1)                                           //���� ���� ���н�

printf("socket() error\n");


memset(&serv_adr , 0 , sizeof(serv_adr)); // ���������� ������ ������ ����ü�� �ʱ�ȭ �Ѵ�.



        /*

         * ���� ������ ������ �����ϴ� ����ü�� ������� �� �Է�

         */

serv_adr.sin_family = AF_INET;

serv_adr.sin_addr.s_addr = inet_addr(argv[1]);

serv_adr.sin_port = htons (atoi (argv[2]));



        // ������ �̿��� ������ ������ ���� ����ü�� ������ ���� ��û�� �Ѵ�.

if (connect (sock , (struct sockaddr * )&serv_adr , sizeof(serv_adr)) == -1)

printf("connect() error!\n");

else

puts("Connected.........");


while(1)

{

fputs ("Input message (Q to quit) : " , stdout);

fgets (message , BUF_SIZE , stdin); //�Է��� �����͸� message�� �ִ´�.



if (!strcmp(message , "q\n") || !strcmp (message , "Q\n")) //q �� Q�� �Է��ϸ� ����

break;



write (sock , message , strlen(message)); //������ message ������ �����͸� �����Ѵ�.

str_len = read (sock , message , BUF_SIZE-1); //�����κ��� �� �޽����� message ������ �ִ´�.

message[str_len] = 0;

printf("Message from server : %s" , message); //�����κ��� ���� �޽��� ���

}



close (sock); // ������ �ݴ´�.

return 0;

}


