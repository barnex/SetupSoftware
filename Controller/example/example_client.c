#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <stdint.h>

int initSocket(int *sock, char *server_name, int portno);

static int readfull(int fd, void *buffer, int n)
{
    uint8_t *localBuffer = (uint8_t *) buffer;
    int ret = 0, i = 0;
    ret = read(fd, localBuffer, n);
    if( ret >= 0 && ret != n )
    {
	i = ret;
	while(i < n && ret >= 0)
	{
	    ret = read(fd, &(localBuffer[i]), n-i);
	    i += ret;
	}
    }
    if( ret > 0 )
    {
    return i;
    }
    else
    {
    return ret;
    }
}

int main(int argc, char **argv)
{
    int sockfd = 0;
    initSocket( &sockfd, "dynalab.ugent.be", 2000);

    char cmdString[256];
    int32_t socketBuffer[2] = {0, 0};

    memset(cmdString, 0, 256);
    sprintf(cmdString, "MEAS\n");
    write(sockfd, cmdString, strlen(cmdString));

    int ret = readfull(sockfd, (void *)socketBuffer, 2*sizeof(int32_t));

    printf("ret: %d\tin[0]: %d\tin[1]: %d\n", ret, socketBuffer[0], socketBuffer[1]);

    float floatBuffer[8];
    memset(floatBuffer, 0, sizeof(float)*8);
    ret = readfull(sockfd, floatBuffer, socketBuffer[1]);
    printf("ret: %d\n", ret);
    for(int i = 0; i < 8; i++ )
    {
	printf("channel %d: %f\n", i, floatBuffer[i]);
    }

    memset(cmdString, 0, 256);
    sprintf(cmdString, "SET,POSITION,0.1,0.2,0.3,0.4\n");
    write(sockfd, cmdString, strlen(cmdString));
    ret = readfull(sockfd, (void *)socketBuffer, 2*sizeof(int32_t));
    printf("ret: %d\tin[0]: %d\tin[1]: %d\n", ret, socketBuffer[0], socketBuffer[1]);

    memset(floatBuffer, 0, 8*sizeof(float));
    memset(cmdString, 0, 256);
    sprintf(cmdString, "GET,POSITION\n");
    printf("%s", cmdString);
    write(sockfd, cmdString, strlen(cmdString));
    ret = readfull(sockfd, (void *)socketBuffer, 2*sizeof(int32_t));
    printf("ret: %d\tin[0]: %d\tin[1]: %d\n", ret, socketBuffer[0], socketBuffer[1]);

    if(socketBuffer[0] == 1)
    {
	ret = readfull(sockfd, (void *)floatBuffer, 4*sizeof(float));
	printf("%f\t%f\t%f\t%f\n", floatBuffer[0], floatBuffer[1], floatBuffer[2], floatBuffer[3]);
    }
    else
    {
	char stringBuffer[1024];
	memset(stringBuffer, 0, 1024);
	readfull(sockfd, stringBuffer, socketBuffer[1]);
	printf("error from system: %s\n", stringBuffer);
    } 
    

    memset(cmdString, 0, 256);
    sprintf(cmdString, "STOP\n");
    write(sockfd, cmdString, strlen(cmdString));
    close(sockfd); 

    return EXIT_SUCCESS;
}


int initSocket(int *sock, char *server_name, int portno)
{
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
    printf("Error: Could not create socket\n");
    return -1;
    }
    
    server = gethostbyname(server_name);
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = portno;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
    printf("Error: Could not connect\n");
    return -1;
    }

    *sock = sockfd;

    return EXIT_SUCCESS;
}
