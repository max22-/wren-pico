#include <stdio.h>
#include "pico/stdlib.h"
#include "wren.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

void wren_pico_welcome_message()
{
  printf("\\/\"-\n");
  printf("\\_/   wren v" WREN_VERSION_STRING "\n");
}

void wren_pico_prompt()
{
  printf("> ");
}

void wren_pico_writeFn(WrenVM* vm, const char *text)
{
  printf("%s", text);
}

void wren_pico_errorFn(WrenVM* vm, WrenErrorType errorType,
             const char* module, const int line,
             const char* msg)
{
  switch (errorType)
  {
    case WREN_ERROR_COMPILE:
    {
      printf("[%s line %d] [Error] %s\n", module, line, msg);
    } break;
    case WREN_ERROR_STACK_TRACE:
    {
      printf("[%s line %d] in %s\n", module, line, msg);
    } break;
    case WREN_ERROR_RUNTIME:
    {
      printf("[Runtime Error] %s\n", msg);
    } break;
  }
}

void wren_pico_readline(char *buffer, size_t size)
{
  char c = 0;
  int n = 0;
  while(c != '\n') {
    c = getchar_timeout_us(1000);
    if(c != PICO_ERROR_TIMEOUT && c != 0 && c != 255) {
      printf("%c", c);
      if(c == '\n')
	break;
      else if(c == '\b') {
	printf("\b");
	n = max(0, n-1);
      }
      else
	buffer[n++] = c;
    }
  }
  buffer[n] = 0;
}




