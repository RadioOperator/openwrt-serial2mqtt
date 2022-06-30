#include <Sys.h>
#include <Log.h>
#include <string.h>
#include <unistd.h>

uint64_t Sys::_upTime;
char Sys::_hostname[30] = "";
uint64_t Sys::_boot_time = 0;

//_____________________________________________________________ LINUX and CYGWIN
#if defined(__linux__) || defined(__CYGWIN__) || defined ( __APPLE__ )
#include <chrono>
#include <time.h>

uint64_t Sys::millis()   // time in msec since boot, only increasing
{
    using namespace std::chrono;
    milliseconds ms =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    Sys::_upTime = ms.count();//system_clock::now().time_since_epoch().count() / 1000000;
    return _upTime;
}

void Sys::init()
{
    gethostname(_hostname, sizeof(_hostname) - 1);
}

void Sys::hostname(const char* hostname)
{
    strncpy(_hostname, hostname, sizeof(_hostname));
}

const char* Sys::hostname()
{
    if (_hostname[0] == 0)
        Sys::init();
    return _hostname;
}

void Sys::delay(uint32_t msec)
{
    struct timespec ts;
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec - ts.tv_sec * 1000) * 1000000;
    nanosleep(&ts, NULL);
};

#endif

//________________________________________________________ ARDUINO

#ifdef ARDUINO

#include <Arduino.h>
uint64_t Sys::millis()   // time in msec since boot, only increasing
{
    return ::millis();
}

uint32_t Sys::getFreeHeap()
{
    return ESP.getFreeHeap();
}

void Sys::hostname(const char* hostname)
{
    strncpy(_hostname, hostname, sizeof(_hostname));
}

const char* Sys::hostname()
{
    return _hostname;
}
void Sys::delay(unsigned int delta)
{
    uint32_t end = Sys::millis() + delta;
    while(Sys::millis() < end)
        ;
}
#endif

#ifdef __ESP8266__

void Sys::delay(uint32_t delta)
{
    uint64_t t1 = Sys::millis() + delta;
    while (Sys::millis() < t1)
        ;
}

#endif

#if defined(ESP_OPEN_RTOS) || defined(ESP8266_RTOS_SDK)
#ifdef ESP_OPEN_RTOS
#include <espressif/esp_system.h>
#include <espressif/esp_wifi.h>
#include <FreeRTOS.h>
#include <task.h>

#endif

#ifdef ESP8266_RTOS_SDK
#include <esp_system.h>
#endif
#include <Log.h>
#include <Sys.h>
#include <stdint.h>
#include <sys/time.h>

const char* Sys::getProcessor()
{
    return "ESP8266";
}
const char* Sys::getBuild()
{
    return __DATE__ " " __TIME__;  
} 

void Sys::init()
{
    // uint8_t cpuMhz = sdk_system_get_cpu_frequency();
}
uint32_t Sys::getFreeHeap()
{
    return esp_get_free_heap_size();
};

uint64_t Sys::millis()
{
    /*
    timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);*/
    return Sys::micros() / 1000000;
}

uint32_t Sys::sec()
{
    return millis() / 1000;
}
extern "C" void vPortEnterCritical(void);
extern "C" void vPortExitCritical();
uint64_t Sys::micros()
{

    static uint32_t lsClock = 0;
    static uint32_t msClock = 0;


    vPortEnterCritical();
    uint32_t ccount;
    __asm__ __volatile__("esync; rsr %0,ccount" : "=a"(ccount));
    if(ccount < lsClock) {
        msClock++;
    }
    lsClock = ccount;
    vPortExitCritical();

    uint64_t micros = msClock;
    micros <<= 32;
    micros += lsClock;

    return micros / 80;
}

uint64_t Sys::now()
{
    return _boot_time + Sys::millis();
}

void Sys::setNow(uint64_t n)
{
    _boot_time = n - Sys::millis();
}

void Sys::hostname(const char* h)
{
    strncpy(_hostname, h, strlen(h) + 1);
}

void Sys::setHostname(const char* h)
{
    strncpy(_hostname, h, strlen(h) + 1);
}

void Sys::delay(unsigned int delta)
{
    uint32_t end = Sys::millis() + delta;
    while(Sys::millis() < end)
        ;
}

extern "C" uint64_t SysMillis()
{
    return Sys::millis();
}

/*
 *
 *  ATTENTION : LOGF call Sys::hostname, could invoke another call to
 * Sys::hostname with LOGF,....
 *
 *
 *
 */

const char* Sys::hostname()
{

    if(_hostname[0] == 0) {
        #ifdef ESP_OPEN_RTOS
        snprintf(_hostname, sizeof(_hostname), "ESP82-%d", sdk_system_get_chip_id() & 0xFFFF);
        #endif
        #ifdef ESP82666_RTOS_SDK
        uint8_t mac[6];
        esp_efuse_mac_get_default(mac);
        uint32_t l = mac[2]*mac[3]*mac[4]*mac[5];
        snprintf(_hostname, sizeof(_hostname),"ESP82-%u",l); 
        #endif
    }
    return _hostname;
}
const char* Sys::board()
{
        static char buffer[80];

    #ifdef ESP_OPEN_RTOS
    snprintf(buffer, sizeof(buffer), " cpu-id : %X , freq : %d Mhz rom-sdk : %s", sdk_system_get_chip_id(),
             sdk_system_get_cpu_freq(), sdk_system_get_sdk_version());
    sdk_system_print_meminfo();
    #endif
    return buffer;
}

#endif

#ifdef ESP32_IDF
#include <Log.h>
#include <Sys.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdint.h>
#include <sys/time.h>
//#include <espressif/esp_wifi.h>

uint32_t Sys::getSerialId()
{
    union {
        uint8_t my_id[6];
        uint32_t lsb;
    };
    esp_efuse_mac_get_default(my_id);
    //      esp_efuse_mac_get_custom(my_id);
    //   sdk_wifi_get_macaddr(STATION_IF, my_id);
    return lsb;
}

const char* Sys::getProcessor()
{
    return "ESP8266";
}
const char* Sys::getBuild()
{
    return __DATE__ " " __TIME__;
}

uint32_t Sys::getFreeHeap()
{
    return xPortGetFreeHeapSize();
};

const char* Sys::hostname()
{
    if (_hostname[0] == 0) {
        union {
            uint8_t my_id[6];
            uint32_t word[2];
        };
        esp_efuse_mac_get_default(my_id);
        snprintf(_hostname, sizeof(_hostname), "ESP32-%d",
                 (word[0] ^ word[1]) & 0xFFFF);
    }
    return _hostname;
}

void Sys::init() {}

uint64_t Sys::millis()
{
    return Sys::micros() / 1000;
}

uint32_t Sys::sec()
{
    return millis() / 1000;
}

uint64_t Sys::micros()
{
    return esp_timer_get_time();
}

uint64_t Sys::now()
{
    return _boot_time + Sys::millis();
}

void Sys::setNow(uint64_t n)
{
    _boot_time = n - Sys::millis();
}

void Sys::hostname(const char* h)
{
    strncpy(_hostname, h, strlen(h) + 1);
}

void Sys::setHostname(const char* h)
{
    strncpy(_hostname, h, strlen(h) + 1);
}

void Sys::delay(unsigned int delta)
{
    uint32_t end = Sys::millis() + delta;
    while (Sys::millis() < end) {
    };
}

extern "C" uint64_t SysMillis()
{
    return Sys::millis();
}
#endif // ESP32_IDF
