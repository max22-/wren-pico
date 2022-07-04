#include <stdio.h>
#include "pico/stdlib.h"
#include "wren.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

void writeFn(WrenVM* vm, const char *text)
{
  printf("%s", text);
}

void errorFn(WrenVM* vm, WrenErrorType errorType,
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

void readline(char *buffer, size_t size)
{
  char c = 0;
  int n = 0;
  while(c != '\n') {
    /*sleep_ms(1000);
      printf("?");*/
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

void prompt()
{
  printf("> ");
}

int main()
{
  stdio_init_all();

  for(int i = 10; i >= 0; i--) {
    printf("%d\n", i);
    sleep_ms(1000);
  }
  puts("Go!");
  
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.writeFn = &writeFn;
  config.errorFn = &errorFn;
  
  WrenVM* vm = wrenNewVM(&config);
  WrenInterpretResult result = wrenInterpret(vm, "repl", "System.print(\"Hello, world! from Wren!\")");
  

  while(1) {
    char buffer[256];
    prompt();
    readline(buffer, sizeof(buffer));
    wrenInterpret(vm, "repl", buffer);
  }
  wrenFreeVM(vm);
  return 0;
}
