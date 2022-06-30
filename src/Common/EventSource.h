#ifndef EVENTSOURCE_H
#define EVENTSOURCE_H
#include <stdint.h>
class EventListener
{
};

template <class EL>
class EventSource
{
public:
//   EventSource();
//   ~EventSource();
    EventSource()
    {
        //ctor
        _listenerCount=0;
    }

    void addListener(EL* listener)
    {
        _listeners[_listenerCount++] = listener;
    }

    EL* firstListener()
    {
        return _listeners[0];
    }


    EL* nextListener(EL* prev)
    {
        for(uint32_t i=0; i<_listenerCount-1; i++)
            if ( prev == _listeners[i]) return _listeners[i+1];
        return 0;
    }

protected:
    EL* _listeners[2];
    uint32_t _listenerCount;
private:
};

/*


EventSource::~EventSource()
{
    //dtor
}

*/




#endif // EVENTSOURCE_H
