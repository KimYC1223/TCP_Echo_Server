#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/socket.h>



#define BUF_SIZE 1024



int main(int argc , char * argv[])

{

int serv_sock , clnt_sock;    //���� ���� , Ŭ���̾�Ʈ ������ ����

char message[BUF_SIZE];   //�޾Ƶ��� �޽����� ������ ����

int str_len , i;                    // �޽����� ���̸� ������ str_len , for���� ����� i ���� 



struct sockaddr_in serv_adr; //���� ���� ������ ������ ����ü

struct sockaddr_in clnt_adr;  // Ŭ���̾�Ʈ ���� ������ ������ ����ü

socklen_t clnt_adr_sz;         // Ŭ���̾�Ʈ ���� ������ ������ ����ü�� ���̸� ������ ���� 



if (argc != 2) {     // ����� �ʿ��� ��Ʈ��ȣ�� �Է����� �ʾ��� ��� �����ϴ� ���� ����

printf("Usage : %s <port>\n" , argv[0]);

exit(1);

}



serv_sock = socket (PF_INET , SOCK_STREAM , 0); //���� ���� ����(IPv4 , TCP/IP ���)



if (serv_sock == -1) //���� ���� ������ �޽���

{

printf("socket() error\n");

}



memset (&serv_adr , 0 , sizeof(serv_adr)); //���� ������ ������ ���� ����ü�� 0���� �ʱ�ȭ �Ѵ�.



        /*

         * ���� ������ ������ �����ϴ� ����ü�� ������� �� �Է�

         */

serv_adr.sin_family = AF_INET; //IPv4 �� ���

serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); //��� �������� ������ ���. 16������ �����ؼ� ����

serv_adr.sin_port = htons(atoi(argv[1])); //���α׷� ����� �Էµ� ��Ʈ��ȣ�� 10������ �����ؼ� ����





        // ����ü�� ������ �̿��ؼ� ���� ���Ͽ� bind

if (bind(serv_sock , (struct sockaddr *)&serv_adr , sizeof(serv_adr)) == -1)

printf("bind() error\n");



        // �޾Ƶ��� �غ� �Ѵ�. ���ڿ� 5��� ���ڴ� ��� Ŭ���̾�Ʈ�� ���ڰ� �ִ� 5����� �ǹ��̴�.

if (listen (serv_sock , 5) == -1)

printf("listen() error\n");



clnt_adr_sz = sizeof(clnt_adr); //Ŭ���̾�Ʈ ����ü�� ũ�⸦ ���Ѵ�.



for (i = 0; i < 5; i++)

{

               //Ŭ���̾�Ʈ�� �������κ��� �����͸� �޾Ƶ��δ�.

clnt_sock = accept (serv_sock , (struct sockaddr *)&clnt_adr , &clnt_adr_sz);

if(clnt_sock == -1)

printf("accept() error\n");



else

printf("Connected client %d\n" , i+1);



                //���� �����͸� Ŭ���̾�Ʈ ������ ���� �ٽ� �����ش�.

while ((str_len = read (clnt_sock , message , BUF_SIZE)) != 0)

write (clnt_sock , message , str_len);



close(clnt_sock); //���� �Ϸ� �� Ŭ���̾�Ʈ���� ������ �����Ѵ�.

}



close (serv_sock);       //���������� �ݴ´�.

return 0;

}

