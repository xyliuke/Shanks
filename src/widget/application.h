//
// Created by 刘科 on 2022/11/14.
//

#ifndef SHANKS_APPLICATION_H
#define SHANKS_APPLICATION_H

#include <memory>

namespace plan9
{
    class Application {
    public:
        Application();
        int run();
    private:
        class application_impl;
        std::shared_ptr<application_impl> impl_;
    };
}


#endif //SHANKS_APPLICATION_H
