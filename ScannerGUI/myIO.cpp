#include "myIO.h"

int myReadfull(QTcpSocket * socket, void *buffer, int nbytes )
{
    memset( buffer, 0, nbytes );
    char *buffercast = (char *) buffer;
    int bytesread = 0;
    bytesread = socket->read(buffercast, nbytes);
    while( bytesread < nbytes && bytesread >= 0 )
    {
        bytesread += socket->read(&(buffercast[bytesread]), nbytes - bytesread);
    }
    assert(bytesread > 0);
    return bytesread;
}
