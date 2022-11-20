//
// Created by 刘科 on 2022/11/20.
//

#ifndef SHANKS_MAIN_WINDOW_H
#define SHANKS_MAIN_WINDOW_H

#include <memory>

namespace plan9
{
    class MainWindow {
    public:
        explicit MainWindow();
        void show();
    private:
        class MainWindowImpl;
        std::shared_ptr<MainWindowImpl> impl_;
    };
}


#endif //SHANKS_MAIN_WINDOW_H
