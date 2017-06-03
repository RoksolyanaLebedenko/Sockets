#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <printf.h>
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <ctime>
using namespace std;


int main()
{
    // --------current date and time----//
      time_t rawtime;
      struct tm * timeinfo;
      struct tm * dateinfo;
      char buffer[80];

      time (&rawtime);
      timeinfo = localtime(&rawtime);
      dateinfo = localtime(&rawtime);

      strftime(buffer,sizeof(buffer),"%d-%m-%Y\n",dateinfo);
      string date(buffer);
      strftime(buffer,sizeof(buffer),"%I:%M:%S\n",timeinfo);
      string time(buffer);

      cout << date;
      cout << time;
    //----------------------------------------//
    struct sockaddr_in server ; char buf[1024];
    int sd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server, 0, sizeof( server ));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(2233);

    int res = bind( sd, (struct sockaddr*) &server, sizeof( server ) );


    listen (sd ,1);
    int psd = accept(sd, 0, 0);
    close (sd );
    for (;;) {
        int cc=recv(psd,buf, sizeof(buf, 0), 0);
        if (cc == 0) exit (EXIT_SUCCESS);
        buf[cc] = '\0';
        printf ("message received: %s\n", buf);
    }
}
