#include "message.h"

int main(int argc, char *argv[])
{
	int initTemp = argv[2];
	int numNodes = argv[3];

	mqd_t my_msqid, your_msqid;
	MESSG msg_rcvd, msg_send;
	unsigned int type;
	pid_t pid;

	float previousAveValue = 0;

	if (argc < 2)
	{
		printf("Usage: avg_server <initial_value>\n");
		exit(1);
	}

	//just in case it is still there (if we quit using ^C for example)
	if (mq_unlink(SERVER_NAME) == 0)
		printf("SRV: Message queue %s removed.\n", SERVER_NAME);

	//float avg = strtol(argv[1], NULL, 0);
    double sumOfReportedValues = 0.0;
    long numberOfReports = 0;
	bool stable = false;

	//initialize the queue attributes
	struct mq_attr attr;

	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;
	attr.mq_flags = 0;

	if ((my_msqid = mq_open(SERVER_NAME, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR, &attr)) < 0)
		oops("SRV: Error opening a server queue.", errno);

		printf("SRV: Message queue %s created.\n", SERVER_NAME);
	for(int i=0; i<3; i++){
   		pid = fork();

		if (pid < 0) // error occurred
			{
				oops("Fork Failed!", errno);
			}
		if (pid == 0) // child
		{
			if (execlp("./node", "node", itoa(i), argv[i +3], NULL) < 0) //executable, node for nodename, node id #, inital start temp, Null because...
				{
					oops("Execlp Failed!", errno);
				}
		}
	}

	while (!stable)
	{
		if (mq_receive(my_msqid, (char*) &msg_rcvd, MAX_MSG_SIZE, &type) >= 0)
		{
			printf("SRV: %s REPORTS: %.2f\n", &(msg_rcvd.sender_name[1]), msg_rcvd.averageValue); // skip '/'
			
			previousAveValue = sumOfReportedValues;
			sumOfReportedValues += msg_rcvd.averageValue;

			if(previousAveValue == sumOfReportedValues){
				stable = true;
			}

			strcpy(msg_send.sender_name, SERVER_NAME);
			msg_send.averageValue = sumOfReportedValues/++numberOfReports;
			msg_send.numberOfReports = numberOfReports;
			msg_send.stable = stable;

			printf("SRV: CURRENT AVERAGE: %.2f\n", msg_send.averageValue);

			if ((your_msqid = mq_open(msg_rcvd.sender_name, O_WRONLY)) < 0)
				oops("SRV: Error opening a client's queue.", errno);

			if (mq_send(your_msqid, (const char*) &msg_send, sizeof(msg_send), (unsigned int) TYPE) < 0)
				oops("SRV: Cannot respond to a client.", errno);
		}
		else
			oops("SRV: Error receiving data.", errno);
	}

	mq_unlink(SERVER_NAME);

	exit(EXIT_SUCCESS);
}
