#include <stdio.h>
#include "pico/stdlib.h"
#include "wren-pico.h"

int main()
{
  stdio_init_all();
  while(getchar_timeout_us(1000) != '\n'); /* Wait for 'return' to start */
  wren_pico_welcome_message();
  WrenConfiguration config;
  wrenInitConfiguration(&config);
  config.writeFn = &wren_pico_writeFn;
  config.errorFn = &wren_pico_errorFn;
  config.bindForeignMethodFn = &wren_pico_bindForeignMethod;
  
  WrenVM* vm = wrenNewVM(&config);

  WrenInterpretResult result = wrenInterpret(vm, "main",
		"class Gpio {\n"
		"  foreign static init(pin)\n"
		"  foreign static set_dir(pin,dir)\n"
		"  foreign static put(pin,val)\n"
		"}");
  if(result != WREN_RESULT_SUCCESS)
    puts("Error!");

  
  while(1) {
    char buffer[256];
    wren_pico_prompt();
    wren_pico_readline(buffer, sizeof(buffer));
    wrenInterpret(vm, "main", buffer);
  }
  wrenFreeVM(vm);
  return 0;
}
