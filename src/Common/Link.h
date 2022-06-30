#ifndef LINK_H
#define LINK_H

// #include "Event.h"
//#include "MqttIn.h"
#include "Handler.h"

class Link : public Handler
{
    public:
//	static const int CONNECTED,DISCONNECTED,RXD,MESSAGE,ERROR;
        Link(const char* s) : Handler(s) {};
        Link();
        virtual ~Link();
        virtual bool isConnected() { return _isConnected; }
        virtual void isConnected(bool val) { _isConnected = val; }

        virtual uint8_t read()=0;
        virtual uint32_t hasData()=0;
//        virtual Erc recv(Bytes& bytes)=0;
        virtual Erc send(Bytes& bytes)=0;
        virtual Erc connect()=0;
        virtual Erc disconnect()=0;
    protected:
    private:
        bool _isConnected;
};

#endif // LINK_H
