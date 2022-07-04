#include <stdio.h>
#include "pico/stdlib.h"
#include "wren-pico.h"

int main()
{
  stdio_init_all();

  for(int i = 10; i >= 0; i--) {
    printf("%d\n", i);
    sleep_ms(1000);
  }
  puts("Go!");
  wren_pico_welcome_message();
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.writeFn = &wren_pico_writeFn;
  config.errorFn = &wren_pico_errorFn;
  
  WrenVM* vm = wrenNewVM(&config);
  WrenInterpretResult result = wrenInterpret(vm, "repl", "System.print(\"Hello, world! from Wren!\")");
  
  while(1) {
    char buffer[256];
    wren_pico_prompt();
    wren_pico_readline(buffer, sizeof(buffer));
    wrenInterpret(vm, "repl", buffer);
  }
  wrenFreeVM(vm);
  return 0;
}
