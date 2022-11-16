#include <iostream>
#include "widget/application.h"

int main (int argc, char **argv)
{
    plan9::Application application = plan9::Application();
    return application.run(argc, argv);
}
