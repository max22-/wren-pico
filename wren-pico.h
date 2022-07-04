#include "wren.h"
void wren_pico_welcome_message();
void wren_pico_prompt();
void wren_pico_writeFn(WrenVM* vm, const char *text);
void wren_pico_errorFn(WrenVM* vm, WrenErrorType errorType,
             const char* module, const int line,
             const char* msg);
void wren_pico_readline(char *buffer, size_t size);
