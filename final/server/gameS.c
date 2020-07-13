/*
 SYSTEM PROGRAMMING FINAL PROJECT 
 SUBMITTED BY DEEPESH PATEL AND RAKESH ROBY

*/




#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>



void child(int);

int main(int argc, char *argv[]){  
  int sd, client, portNumber, status;
  struct sockaddr_in servAdd;      // client socket address
  
 if(argc != 2){
    printf("Call model: %s <Port Number>\n", argv[0]);
    exit(0);
  }
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "Cannot create socket\n");
    exit(1);
  }
  sd = socket(AF_INET, SOCK_STREAM, 0);
  servAdd.sin_family = AF_INET;
  servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
  sscanf(argv[1], "%d", &portNumber);
  servAdd.sin_port = htons((uint16_t)portNumber);
  
  bind(sd, (struct sockaddr *) &servAdd, sizeof(servAdd));
  listen(sd, 1);

  while(1){
   // printf("Waiting for a client to chat with\n");
    client = accept(sd, NULL, NULL);
   printf("Got a Player, starting game with player\n");
    
    if(!fork())
      child(client);

    close(client);
    waitpid(0, &status, WNOHANG);
  }
}

void child(int sd){
	char message[255];
	int n;
        int Server_Score_total=0,Client_Score_total=0;
		int Server_Score,Client_Score;
		int dice=6;
		long int ss=0;
	   //fprintf(stderr,"total client score: %d\n", Client_Score_total);
	   //fprintf(stderr,"total Server score: %d\n", Server_Score_total);

       write(sd, "Game is Starting soon : ", 24);

	  /* sending messages to the client  */
	   while(1)
	   {
		//fprintf(stderr,"total client score: %d\n", Client_Score_total);
	    //fprintf(stderr,"total Server score: %d\n", Server_Score_total);
	    if(Server_Score_total>=100 || Client_Score_total>=100)
		{
			if(Server_Score_total>=100)
			{
				write(sd, "Refreee--> Game over: you lost the game ", 40);
			}
			else
				write(sd, "Refreee--> Game over: you won the game ", 40);
			
			close(sd);
			
			exit(0);
						
		}
		else
	   { 
		sleep(1);
	    
	      write(sd, "Refreee --> Game on: you can now play your dice ", 48);
	      
	    }
		sleep(1);
		{
		  Server_Score=(int) time(&ss)%dice + 1;;
			//itoa(Server_Score,message,10);
			sprintf(message,"%d", Server_Score);
	     
			write(sd,message,255);
			Server_Score_total+=Server_Score;
		  
	     
	    }
		sleep(1);
		if(n=read(sd, message, 255))
	   {
          //message[n]='\0';
		  Client_Score=atoi(message);
		  //          fprintf(stderr,"client Score :       %d\n", Client_Score);
		  Client_Score_total+=Client_Score;
		  // fprintf(stderr,"Client Total Score : %d\n\n", Client_Score_total);
          if(!strcasecmp(message, "Bye\n")){
	    //  kill(pid, SIGTERM);
             exit(0);
           
		  }
	   }
		/*
		if(n=read(sd, message, 255)){
	    // message[n]='\0';
	    // fprintf(stderr,"%s", message);
		 Client_Score=atoi(message);
		 Client_Score_total+=Client_Score;
		 fprintf(stderr,"%d\n", Client_Score);
	     if(!strcasecmp(message, "Bye\n")){
	       //	        kill(pid, SIGTERM);
	        exit(0);
	     }
	   }
	   */
	   }
}
