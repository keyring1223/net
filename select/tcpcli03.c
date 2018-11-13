/* Test shutdown(fd,SHUT_RD) and see what happens */
#include	"../lib/unp.h"
#include <stdarg.h>
void err_doit1(int errnoflag,int error,const char *fmt,va_list ap)
{
	char buf[MAXLINE];
	vsnprintf(buf,MAXLINE-1,fmt,ap);
	if(errnoflag)
		snprintf(buf+strlen(buf),MAXLINE-strlen(buf)-1,":%s",strerror(error));
	strcat(buf,"\n");
	fflush(stdout);
	fputs(buf,stderr);
	fflush(NULL);
}
void err_quit1(const char *fmt,...){
	va_list ap;
	va_start(ap,fmt);
	err_doit1(0,0,fmt,ap);
	va_end(ap);
	exit(1);
}

int main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit1("usage: tcpcli03 <IPaddress>");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(19);		/* chargen server */
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	shutdown(sockfd, SHUT_RD);

	pause();

	exit(0);
}
