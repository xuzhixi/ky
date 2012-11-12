#include <stdio.h>

#include <ky_log.h>

int main()
{
	//ky_log_t log;
	//ky_log_redirect_std("ky.log", "a");
	//ky_log_open(&log, "ky.log", "w+", KY_LOG_LEVEL_INFO);

	//fprintf(stderr, "start------------------start\n");
	//KY_LOG_ERROR(&log, "testId: %d", 100);
	//KY_LOG_WARN(&log, "testId: %d", 100);
	//fprintf(stderr, "mid----------------------mid\n");
	//KY_LOG_INFO(&log, "testId: %d", 100);
	//fprintf(stderr, "end----------------------end\n");

	//ky_log_close( &log );


	//ky_log_std_init(KY_LOG_LEVEL_WARN);
	//ky_log_redirect_std("ky.log", "a");

	//fprintf(stderr, "start------------------start\n");
	//KY_LOG_ERROR("testId: %d", 100);
	//KY_LOG_WARN("testId: %d", 100);
	//fprintf(stderr, "mid----------------------mid\n");
	//KY_LOG_INFO("testId: %d", 100);
	//fprintf(stderr, "end----------------------end\n");

	int i;
	//g_ky_log_default = ky_log_open("stdout", "w", KY_LOG_LEVEL_ALL, 0, 0);
	//g_ky_log_default = ky_log_open("ky.log", "w", KY_LOG_LEVEL_ALL, 1, 0);
	//g_ky_log_default = ky_log_open("ky.log", "w", KY_LOG_LEVEL_ALL, 2, 5 * 1024 * 1024);
	for (i=0; i<1; i++)
	{
		KY_LOG_ERROR("testId: %d", 100);
		KY_LOG_WARN("testId: %d", 100);
		KY_LOG_INFO("testId: %d", 100);
		KY_LOG_DEBUG("testId: %s %s", __DATE__, __TIME__);
	}
	//ky_log_close( g_ky_log_default );

	return 0;
}

