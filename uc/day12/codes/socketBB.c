#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>	/*1*/
#include <arpa/inet.h>

main()
{
	int fd;
	struct sockaddr_in addr;/*2.*/
	int r;	
	/*1.建立socket:socket*/
	fd=socket(AF_INET,SOCK_DGRAM,0); /*3*/
	if(fd==-1) printf("socket:%m\n"),exit(-1);
	printf("socket OK!\n");
	
	/*2.构造通信地址:struct sockaddr_un*/
	addr.sin_family=AF_INET; /*4*/
	addr.sin_addr.s_addr=inet_addr("192.168.180.67");
	addr.sin_port=htons(9999);
		
	/*3.连接到通信地址:connect*/
	r=connect(fd,(struct sockaddr*)&addr,sizeof(addr));
	if(r==-1) printf("connect:%m\n"),close(fd),exit(-1);
	printf("成功连接到socket文件!\n");
	
	/*4.发送数据到目标:write*/
	while(1){
		write(fd,"靓崽!",strlen("靓崽!"));
		sleep(1);
	}
	
	/*5.关闭socket:close*/
	close(fd);
}
