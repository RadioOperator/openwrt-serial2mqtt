/* 
 * File:   Pool.h
 * Author: lieven2
 *
 * Created on 21 september 2013, 23:23
 */

#ifndef POOL_H
#define	POOL_H
#include <stdint.h>
#define POOL_SIZE 5

class Pool {
public:
    Pool();
    Pool(const Pool& orig);
    virtual ~Pool();
    static uint16_t put(void *pv);
    static void* get(uint16_t handle);
    static void* alloc(uint32_t size);
    static void free(void *pv);
private:
    static void* _busy[POOL_SIZE];
    static void* _free[POOL_SIZE];
};

#endif	/* POOL_H */

