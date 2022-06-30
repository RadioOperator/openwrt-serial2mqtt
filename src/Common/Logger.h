#ifndef LOGGER_H
#define LOGGER_H

#define LOG_FILE __FILE__
#define LOG_DATE __DATE__
typedef enum {
	FLUSH, LOG_DEBUG, LOG_INFO, LOG_ERROR, LOG_WARN, LOG_HEX, LOG_DEC
} LogCmd;

#ifndef __cplusplus
extern void uart0WriteWait(uint8_t TxChar);
#define LOGNOW(ch) uart0WriteWait(ch)
#define ASSERT(xxx) if ((xxx)==0) INFO(" ASSERT FAILED " # xxx)
#define INFO(fmt,...) SysLogger(LOG_INFO,__FILE__,__FUNCTION__ ,fmt,##__VA_ARGS__)
#define ERROR(fmt,...) SysLogger(LOG_INFO,__FILE__,__FUNCTION__ ,fmt,##__VA_ARGS__)
#define WARN(fmt,...) SysLogger(LOG_INFO,__FILE__,__FUNCTION__ ,fmt,##__VA_ARGS__)
void SysLogger(int level, const char* file, const char* function,
		const char * format, ...);
#else
#include <time.h>
#include <Str.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
extern "C" void uart0WriteWait(uint8_t TxChar);


#define PERROR()  Logger::logger->header(__FILE__,__FUNCTION__).log("line : %d - System failure : %d : %s ",__LINE__,errno,strerror(errno))
#undef ASSERT
#define ASSERT(xxx) if ((xxx)==0) INFO(" ASSERT FAILED " # xxx)

class Logger: public Str {
public:
	enum Level {
		L_DEBUG, L_INFO, L_WARN, L_ERROR, L_FATAL
	};
	static Logger* logger;

	Logger(int size);

	Logger& level(int level);
	void setLevel(Level l);
	Logger& header(const char* file_source, const char* function);
	Logger& operator<<(LogCmd cmd);

	Logger& operator<<(const char *s);
	Logger& operator<<(int i);
	Logger& operator<<(uint32_t i);
	Logger& operator<<(uint64_t i);
	Logger& operator<<(float f);
	Logger& operator<<(Bytes& b);
	Logger& dump(Bytes& bytes);
	Logger& operator<<(Str& str);
	Logger& vlog(const char * format, va_list args);
	Logger& log(const char *fmt, ...);

	Logger& flush();
	Logger& debug();
	Logger& warn();
	Logger& info();
	Logger& error();
	Logger& fatal();
	Logger& hex();
	Logger& dec();
	Logger& perror(const char* s);
	const char* logTime();

private:

	int _level;
	int _logLevel;
	enum {
		FORMAT_DEC, FORMAT_HEX
	} _format;
	const char* _module;
	Str _str;
};
#endif // __cplusplus

#endif // LOGGER_H
