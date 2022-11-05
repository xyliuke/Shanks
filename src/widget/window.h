//
// Created by 刘科 on 2022/11/4.
//

#ifndef SHANKS_WINDOW_H
#define SHANKS_WINDOW_H
#include <memory>

namespace plan9 {

    class window {
    public:
        explicit window();
        void show() const;
    private:
        class window_impl;
        std::shared_ptr<window_impl> impl_;
    };

} // plan9

#endif //SHANKS_WINDOW_H
