#include <iostream>
#include "qt_widget/application.h"

int main (int argc, char **argv)
{
    plan9::Application application = plan9::Application(argc, argv);
    return application.run();
}
