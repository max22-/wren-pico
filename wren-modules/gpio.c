#include <string.h>
#include "pico/stdlib.h"
#include "wren.h"

static void wren_gpio_init(WrenVM* vm)
{
  const uint pin = wrenGetSlotDouble(vm, 1);
  printf("gpio_init(%d)\n", pin);
  gpio_init(pin);
  puts("done!");
}

static void wren_gpio_set_dir(WrenVM* vm)
{
  const uint pin = wrenGetSlotDouble(vm, 1);
  const uint dir = wrenGetSlotDouble(vm, 2);
  gpio_set_dir(pin, dir);
}

static void wren_gpio_put(WrenVM* vm)
{
  const uint pin = wrenGetSlotDouble(vm, 1);
  const uint val = wrenGetSlotDouble(vm, 2);
  gpio_put(pin, val);
}


WrenForeignMethodFn gpio_method_lookup(WrenVM *vm, bool isStatic, const char *signature)
{
  if(isStatic && strcmp(signature, "init(_)") == 0)
    return wren_gpio_init;
  else if(isStatic && strcmp(signature, "set_dir(_,_)") == 0)
    return wren_gpio_set_dir;
  else if(isStatic && strcmp(signature, "put(_,_)") == 0)
    return wren_gpio_put;
  else
    return NULL;
}
