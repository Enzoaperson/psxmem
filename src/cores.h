#ifndef CORES
#define CORES

enum CORE_TYPE {RIDGE_RACER};

char run_core(enum CORE_TYPE core, unsigned char *data);
enum CORE_TYPE find_core(unsigned char *id);

char ridge_racer(unsigned char *data);
#endif
