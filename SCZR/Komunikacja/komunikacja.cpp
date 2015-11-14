@author Tomasz Bochnski, Jakub Guzek


/* sigaction */
#include <signal.h>
/* EOK, ENOSYS */
#include <errno.h>
/* printf */
#include <stdio.h>
/* pthread_t, pthread_create, pthread_join, pthread_cancel, pthread_exit */
#include <pthread.h>
/* cout */
#include <iostream>
/* string, getline */
#include <string>
/* strncpy */
#include <cstring>
/* EXIT_SUCCESS, EXIT_FAILURE */
#include <stdlib.h>
/* name_open, name_close, name_attach, name_detach, msgReceive, msgSend, msgReply */
#include <sys/iofunc.h>
#include <sys/dispatch.h>

/**
 * channels names 
 */
const char* my_channel;
const char* stranger_channel;

/**
 * pointer to structure filled by name_attach()
 */
name_attach_t *attach;

/**
 * (side-channel) Connection ID, returned by name_open()
 */
int coid;

/**
 * header of the message filled with pulse info
 */
typedef struct _pulse msg_header_t;

/**
 * Proper structure of my message 
 */
typedef struct _my_data {
	/** 
	 * header that contains pulse info in message
	 */ 
	msg_header_t header;
	/**
	 * buffer for proper data for message
	 */
	char data[32];
} my_data_t;

/** 
 * Value filled by function pthread_create
 */
pthread_t client, server;

/**
 * This function represents server thread. Thanks to this function we can
 * receive data send by client.
 *
 * @param nth - not used but demanded by pthread_create() convencion
 * @return no value returned
 */
void* receive (void* nth) {
	my_data_t msg;
	int rcvid;
	/* Trying to register and create channel */
	if ((attach = name_attach(NULL, my_channel, 0)) == NULL) {
		std::cerr<< "Can't create Channel\n";
		exit(-1);
	}
	
	/* main loop - receiving messages */
	while(true) {
		rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);
		
		/* checking if message was received correctly */
		if (rcvid == -1) {
			std::cerr<<"Error in receiving message. \n";
			break;
		}
		
		/* checking if message is a pulse */
		if (rcvid == 0) {
			switch (msg.header.code) {
				case _PULSE_CODE_DISCONNECT:
					/* Canceling client thread */
					pthread_cancel(client);
					/* Waiting for thread to finish executing */
					pthread_join(client, NULL);
					/* Closing connection and destroying channel */
					name_close(coid);
					name_detach(attach, 0);
					/* Finish server thread */
					pthread_exit (0);
			}
		}
		
		/* check if message is connection request */
		if (msg.header.type == _IO_CONNECT) {
			MsgReply(rcvid, EOK, NULL, 0);
			continue;
		}
		
		/* chcek id message is unimplemented system communicate */
		if (msg.header.type > _IO_BASE && msg.header.type <= _IO_MAX) {
			MsgError (rcvid, ENOSYS);
			continue;
		}
		printf("\n");
		printf("[%s]: %s\n", stranger_channel, msg.data);
		printf("[%s]: ", my_channel);
		fflush(stdout);
		//std::cout<<"Server received: " << msg.data<< "\n ";
		MsgReply(rcvid, EOK, NULL, 0);
	}
}


/**
 * This function represents client thread. Thanks to this function we can send
 * data to serwer.
 *
 * @param nth - not used but demanded by pthread_create() convencion
 * @return no value returned
 */
void* send(void* nth) {
	my_data_t msg;
	
	std::string buffer;
	
	/* We trying to open connection with channel, store coid value */
	while((coid = name_open(stranger_channel, 0)) == -1) {
		std::cout<<"Waiting for the server to be created. \n";
		sleep(2);
	}
	
	msg.header.type = 0x00;
	msg.header.subtype = 0x00;
	
	/* main loop - sending data */
	while(true) {
		//std::cout<<"["<<my_channel<<"]: ";
		printf("[%s]: ", my_channel);
		fflush(stdout);
		std::getline(std::cin, buffer);
		std::strncpy(msg.data, buffer.c_str(), 32);
		msg.data[31]='\0';
		
		if(MsgSend(coid, &msg, sizeof(msg), NULL, 0) == -1) {
			std::cerr<<"Error while sending message\n";
			exit(-1);
		}
	}
}

/**
 * @param sig - not used but demanded by sigaction() convenction
 */
extern "C" {
	void handle_signal(int sig) {
		/* Canceling server and client threads */
		pthread_cancel(client);
		pthread_cancel(server);
		
		/* Waiting for threads to finish executing */
		pthread_join(client, NULL);
		pthread_join(server, NULL);
		
		/* Closing connection and destroying channel */
		name_close(coid);
		name_detach(attach, 0);
	}
}

/**
 * Main function, program execution starts here. 
 * In this function we create two threads: one for server and one for client,
 * and we stop the main thread until they end.
 * We also add handle for SIGINT (CONTROL+C) by sigaction.
 *
 * @param argc - the number of elements in array argv
 * @param argv - array of aray of chars
 * @return EXIT_FAILURE when error, otherwise returns EXIT_SUCCESS
 */
int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr<<"Wrong number of args\n";
		return EXIT_FAILURE;
	}
	
	/* Read arguments - channels names */
	my_channel = argv[1];
	stranger_channel = argv[2];
	
	/* Add action for SIGINT (CRTL + C) */
	struct sigaction act;
	sigset_t set;
	sigemptyset(&set);
	act.sa_flags=0;
	act.sa_mask = set;
	act.sa_handler = &handle_signal;
	sigaction(SIGINT, &act, NULL);
	
	/* Create threads */
	pthread_create(&server, NULL, receive, NULL);
	pthread_create(&client, NULL, send, NULL);
	
	/* Waiting for threads to finish executing */
	pthread_join(server, NULL);
	pthread_join(client, NULL);
	
	std::cout<<"FINISHED\n";
	return EXIT_SUCCESS;
}
		
		