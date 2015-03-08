#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef void (*test_t)();

int main() {
    void *handle;
    test_t test;
    char *error;

    handle = dlopen ("nibbler_gui_qt.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }

    test = (test_t)dlsym(handle, "test");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }

    test();
    dlclose(handle);
}
