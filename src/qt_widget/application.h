//
// Created by 刘科 on 2022/11/20.
//

#ifndef SHANKS_APPLICATION_H
#define SHANKS_APPLICATION_H
#include <memory>

namespace plan9
{
    class Application {
    public:
        explicit Application();
        explicit Application(int argc, char** argv);
        int run();
    private:
        class ApplicationImpl;
        std::shared_ptr<ApplicationImpl> impl_;
    };
}


#endif //SHANKS_APPLICATION_H
