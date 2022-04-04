#ifndef _LOG_H_
#define _LOG_H_


#define PRINT_LOG_ERRO(format, ...) \
        fprintf(stderr, "[ERRO|%s@%s:%d] " format "\n", \
             __func__, __FILE__, __LINE__, ##__VA_ARGS__ )

#define PRINT_LOG_INFO(format, ...) \
        fprintf(stderr, "[INFO|%s@%s:%d] " format "\n", \
             __func__, __FILE__, __LINE__, ##__VA_ARGS__ )
#endif