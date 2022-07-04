#include <string.h>
#include "wren.h"
#include "modules.h"
#include "gpio.h"

WrenForeignMethodFn wren_pico_bindForeignMethod(
    WrenVM* vm,
    const char* module,
    const char* className,
    bool isStatic,
    const char* signature)
{
  if (strcmp(module, "main") == 0) {
    if (strcmp(className, "Gpio") == 0)
      return gpio_method_lookup(vm, isStatic, signature);
  }
  // Other modules...
}
