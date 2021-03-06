#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>


int main(int argc, char *argv[]){
  char message[255];
  int server, portNumber, pid, n;
  struct sockaddr_in servAdd;     // server socket address
  
 if(argc != 3){
    printf("Call model: %s <IP Address> <Port Number>\n", argv[0]);
    exit(0);
  }

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
     fprintf(stderr, "Cannot create socket\n");
     exit(1);
  }

  servAdd.sin_family = AF_INET;
  sscanf(argv[2], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);

  if(inet_pton(AF_INET, argv[1], &servAdd.sin_addr) < 0){
  fprintf(stderr, " inet_pton() has failed\n");
  exit(2);
}

 if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd))<0){
  fprintf(stderr, "connect() has failed, exiting\n");
  exit(3);
 }

  read(server, message, 255);
  fprintf(stderr, " %s\n", message);
        int Server_Score_total=0,Client_Score_total=0;
		int Server_Score,Client_Score;
		long int ss=0;
		int dice=6;
     while(1)
	 {		 /* reading server's messages */
       if(n=read(server, message, 255))
	   {
		   
          message[n]='\0';
          fprintf(stderr,"%s\n\n", message);
          if(!strcasecmp(message, "Bye\n"))
		  {
	    //  kill(pid, SIGTERM);
             exit(0);
           
		  }
	   }
		 	 /* reading server's messages */
       if(n=read(server, message, 255))
	   {
          //message[n]='\0';
		  Server_Score=atoi(message);
          fprintf(stderr,"Server Score :       %d\n", Server_Score);
		  Server_Score_total+=Server_Score;
		  fprintf(stderr,"Server Total Score : %d\n\n", Server_Score_total);
          if(!strcasecmp(message, "Bye\n")){
	    //  kill(pid, SIGTERM);
             exit(0);
           
		  }
	   }
	   
	    fprintf(stderr, "Hit enter to play the dice and obtain the score\n");
	   if(n=read(0, message, 255)){
         message[n]='\0';
         
         if(!strcasecmp(message, "Bye\n")){
           // kill(getppid(), SIGTERM);
            exit(0);
          }
      }
	   
	        //sleep(.5);
		//	for(int j=0;j<rand()%dice;j++)
                   	   Client_Score=(int) time(&ss)%6 + 1;
			//itoa(Server_Score,message,10);
			sprintf(message,"%d",Client_Score);
			fprintf(stderr,"My score :           %d\n", Client_Score);
			write(server,message,255);
			Client_Score_total+=Client_Score;
			fprintf(stderr,"My Total score :     %d\n\n", Client_Score_total);
	     
			
			
		  
		  }

  
}

