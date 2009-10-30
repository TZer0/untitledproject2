#ifndef LOG_H
#define LOG_H

#include <string>
#include <stdio.h>
#include <stdarg.h>

enum LOG_ID {
	LOG_ID_SCREEN = 0,
	LOG_ID_CORE,
	LOG_ID_INIT,
	LOG_ID_LOAD,
	LOG_ID_ID,
	LOG_ID_LUA,

	LOG_ID_COUNT
};

enum {
	LERR = 0,
	LWARN,
	LNOTE,
	LDEBUG,

	LOG_MAX
};

#define LOG_DIR "log/"

// Macros
#define LOG mLog.log

class cmLog {
	public:
		cmLog() {}

		int init(int loglevel);
		void log(int logtype, int level, const char *format, va_list argptr);
		int deinit(void);
		void set_prefix(int,const char *);
		void set_indent(int,int);

		int is_active[LOG_ID_COUNT];
		FILE *p[LOG_ID_COUNT];
		std::string pref[LOG_ID_COUNT];
		int indent[LOG_ID_COUNT];
		int loglevel;

		int argc;
		char **argv;
};

#define LOGDEF(name) void name(int level, const char *format, ...);
LOGDEF(LOGS)
LOGDEF(LOGC)
LOGDEF(LOGI)
LOGDEF(LOGL)
LOGDEF(LOGID)
LOGDEF(LOGU)

extern class cmLog mLog;

#endif
