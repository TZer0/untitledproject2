#include "log.h"
#include "../port.h"
#include <time.h>

#define get_ptime() (double(clock())/double(CLOCKS_PER_SEC))

class cmLog mLog;

const char *logfile[LOG_ID_COUNT] =
	{ ":/stdout", "core.log", "init.log", "load.log", "id.log", "lua.log" };
const char *llevel[LOG_MAX] = {"ERROR:  ", "WARNING:", "NOTIFY: ", "DEBUG:  "};

/**
 * Sets the logging level to use.
 */
int cmLog::init(int ll)
{
	int i;

	for(i=0;i<LOG_ID_COUNT;i++) {
		is_active[i] = 0;
		indent[i] = 0;
	}
	
	loglevel = ll;
	
	return 1;
}

/**
 * Logs a message to the desired logging file
 * @arg logtype The logging type to use, as defined by the enum LOG_ID
 */
void cmLog::log(int logtype, int level, const char *format, va_list argptr)
{
	char buf[1024];
	struct tm *t;
	time_t taim;
	std::string fn;

	// Check if the logging level is acceptable
	if(!(level <= loglevel)) {
		return;
	}
	
	// TODO: Add some error checking here?
	
	// Opens the file for reading if it isn't already opened
	if(is_active[logtype]==0) {
		// Test for special cases
		if(strcmp(logfile[logtype],":/stdout")==0) {
			// This logging type is direct output to the screen
			is_active[logtype]=2;
			
			taim = time(NULL);
			t = localtime(&taim);
			printf("Logging started at %s", asctime(t));
		}
		
		// This is just a normal file
		else {
			memset(buf,0,sizeof(buf));
			is_active[logtype]=1;
			get_executable_name(buf,sizeof(buf)); // TODO: Figure out why this doesnt work!
			replace_filename(buf,buf, "", sizeof(buf));
			fn = std::string(buf) + std::string(LOG_DIR) + std::string(logfile[logtype]);
			p[logtype] = fopen(fn.c_str(), "wb");
			printf("%s\n", fn.c_str());
			if (p[logtype] == NULL) {
				printf("Unable to open log file.\n%s\n", fn.c_str());
				printf("Log will not be saved to file, make sure the directory exists.\n");	// TODO: Make a snippet to check if the directory exists and if not either create it or create the logfile in root dir.
				return;
			}
			taim = time(NULL);
			t = localtime(&taim);
			fprintf(p[logtype],"Logging started at %s", asctime(t));
			
		}
	}

	// Prepares indentation level
	std::string ind;
	ind.clear();
	ind.insert(ind.begin(), indent[logtype], '\t');

	// Print actual log
	if(is_active[logtype]==2) {		// Prints to console
		printf("(%08.2f)%s %s%s", get_ptime(), llevel[level], ind.c_str(), pref[logtype].c_str());
		vprintf(format, argptr);
		printf("\n");
	}else {							// Prints to file
		fprintf(p[logtype], "(%08.2f)%s %s%s", get_ptime(), llevel[level], ind.c_str(), pref[logtype].c_str());
		vfprintf(p[logtype], format, argptr);
		fputs("\n", p[logtype]);
		fflush(p[logtype]);
	}
	
	return;
}

/**
 * Closes down files and resets data
 */
int cmLog::deinit(void)
{
	int i;
	
	for(i=0;i<LOG_ID_COUNT;i++) {
		if(is_active[i] != 0 && strcmp(logfile[i],":/stdout")!=0) {
			fputs("\n\n", p[i]);
			fclose(p[i]);
			p[i] = NULL;
			is_active[i] = 0;
		}
	}
	
	return 1;
}

/**
 * Sets the prefix to use in front of messages of the logging type specified
 */
void cmLog::set_prefix(int logtype, const char *str)
{
	pref[logtype] = std::string(str);
}

/**
 * Sets the indentation level relative to current
 */
void cmLog::set_indent(int logtype, int depth)
{
	indent[logtype] += depth;
}

// Shortcut log function macro
#define LOG_FUNCTION(name, id)					\
	void name(int level, const char *format, ...) {		\
		va_list argptr; va_start(argptr,format);	\
		mLog.log(id,level,format,argptr);		\
		va_end(argptr); 				\
	}

// Shortcut log functions
LOG_FUNCTION(LOGC,LOG_ID_CORE)
LOG_FUNCTION(LOGS,LOG_ID_SCREEN)
LOG_FUNCTION(LOGI,LOG_ID_INIT)
LOG_FUNCTION(LOGL,LOG_ID_LOAD)
LOG_FUNCTION(LOGID,LOG_ID_ID)
LOG_FUNCTION(LOGU,LOG_ID_LUA)

