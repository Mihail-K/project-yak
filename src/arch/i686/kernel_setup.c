#include <stdint.h>

#include "console.h"

void kernel_setup()
{
    uint8_t* ptr = (uint8_t*) 0xB8000;

    console_clear();
    console_writeln("Foo1");
    console_writeln("Foo2");
    console_writeln("Foo3");
    console_writeln("Foo4");
    console_writeln("Foo5");
    console_writeln("Foo6");
    console_writeln("Foo7");
    console_writeln("Foo8");
    console_writeln("Foo9");
    console_writeln("Foo10");
    console_writeln("Foo11");
    console_writeln("Foo12");
    console_writeln("Foo13");
    console_writeln("Foo14");
    console_writeln("Foo15");
    console_writeln("Foo16");
    console_writeln("Foo17");
    console_writeln("Foo18");
    console_writeln("Foo19");
    console_writeln("Foo20");
    console_writeln("Foo21");
    console_writeln("Foo22");
    console_writeln("Foo23");
    console_writeln("Foo24");
    console_writeln("Foo25");
    console_writeln("Foo26");
    console_writeln("Foo27");
    console_writeln("Foo28");
    console_writeln("Foo29");
    console_writeln("Foo30");

    while(1) {}
}
