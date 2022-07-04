#include "gpio.h"

WrenForeignMethodFn wren_pico_bindForeignMethod(
    WrenVM* vm,
    const char* module,
    const char* className,
    bool isStatic,
    const char* signature);
