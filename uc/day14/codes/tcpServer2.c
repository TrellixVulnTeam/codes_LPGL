#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
main()
{
	int serverfd;
	struct sockaddr_in addr;
	int r;
	int buf;	
	/*1.����������socket*/
	serverfd=socket(PF_INET,SOCK_STREAM,0);
	if(serverfd==-1) printf("socket:%m\n"),exit(-1);
	printf("����socket�ɹ�!\n");
	
	/*2.��inetͨ�ŵ�ַ*/
	addr.sin_family=PF_INET;
	addr.sin_port=htons(8888);
	inet_aton("192.168.180.67",&addr.sin_addr);
	r=bind(serverfd,(struct sockaddr*)&addr,sizeof addr);
	if(r==-1) printf("bind:%m\n"),close(serverfd),exit(-1);	
	printf("�󶨵�ַ�ɹ�!\n");
	
	/*3.����������socket*/
	r=listen(serverfd,10);
	if(r==-1) printf("listen:%m\n"),close(serverfd),exit(-1);
	printf("�����ɹ���\n");
	
	/*4.���ܿͻ�������*/
	struct sockaddr_in fromaddr;
	socklen_t len=sizeof(fromaddr);
	
	
	int fd=accept(serverfd,(struct sockaddr*)&fromaddr,&len);
	if(fd==-1) {
		printf("accept:%m\n");
		exit(-1);
	}
	printf("�пͻ�����:%s\n",inet_ntoa(fromaddr.sin_addr));
	/*5.���ܸÿͻ�������*/
	while(1){
		/*Ϊʲô��MSG_WAITALL,��ʲô���ã�*/
		r=recv(fd,&buf,sizeof(buf),MSG_WAITALL);
		if(r==0){
			printf("�ͻ����ӹر�!\n");
			break;
		}
		if(r==-1){
			printf("�������!\n");
			break;
		}
		if(r>0){			
			printf("���Կͻ�����:%d\n",buf);
			printf("=======================\n");
		}
	}
		/*6.�ر�����*/	
	close(fd);
	
	/*7.�رշ�����socket*/
	close(serverfd);
}