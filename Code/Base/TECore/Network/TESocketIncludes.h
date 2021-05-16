#if TE_WINDOWS
#include <WinSock2.h>
#include <ws2tcpip.h>
#elif TE_LINUX
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif
