//
// Created by 刘科 on 2022/11/23.
//

#ifndef SHANKS_MAIN_WINDOW_MANAGER_H
#define SHANKS_MAIN_WINDOW_MANAGER_H

#include <memory>
#include "main_window.h"

namespace plan9
{
    class MainWindowManager {
    public:
        explicit MainWindowManager(std::shared_ptr<MainWindow> window);
        void show();
    private:
        class MainWindowManagerImpl;
        std::shared_ptr<MainWindowManagerImpl> impl_;
    };

}


#endif //SHANKS_MAIN_WINDOW_MANAGER_H
