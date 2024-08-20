//#include <iostream>
#include "context.h"
#include "diagnostics.h"

int main()
{
    Context context;
    context.init(640, 480, "My Little Window");

    diagnostics::Environment();

    while (!context.shouldClose()) {
        context.tick();
        context.clear();
    }

    context.terminate();
    return 0;
}
