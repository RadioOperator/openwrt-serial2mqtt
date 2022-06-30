#ifndef MUTEX_H
#define MUTEX_H


class Mutex
{
    public:
        Mutex();
        virtual ~Mutex();
        static void lock();
        static void unlock();
    protected:
    private:
};

#endif // MUTEX_H
