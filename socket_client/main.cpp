#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <printf.h>
#include <iostream>
#include <unistd.h>


using namespace std;

// ----------------------------- 10.0.2.15
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main() {

    struct sockaddr_in server ;
    struct addrinfo addr;
    char host_buf[256];
    int portno = 14880;                         //
    int sd = socket(AF_INET,SOCK_STREAM,0);

    if (sd < 0)
        error("ERROR opening socket");

    memset(&server, 0, sizeof( server ));
    server.sin_family = AF_INET;
    server.sin_port = htons(portno);
    if (inet_aton("10.0.2.15", &server.sin_addr) <= 0 ) {      //
        error("Incorrect IP");
    }

    if (connect(sd,(struct sockaddr *) &server,sizeof(server)) < 0)
        error("ERROR connecting");
    string command;
    cout << "Enter a command ( t; d; h; m and your word; ): ";
    cin >> command;
    char comm[1024];
    strcpy(comm, command.c_str());

    for (;;) {

        char buf[1024] = {*comm}
                         ;
        send(sd, buf, strlen (buf ), 0 );
        printf("Sent: %s\n", buf);
        sleep(2);
    }
}

