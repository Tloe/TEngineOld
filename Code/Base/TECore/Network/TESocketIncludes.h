#if TE_WINDOWS
    #include <WinSock2.h>
    #include <ws2tcpip.h>
#elif TE_LINUX
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <arpa/inet.h>
    #include <fcntl.h>
#endif
