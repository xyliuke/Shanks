//
// Created by 刘科 on 2022/11/20.
//

#ifndef SHANKS_MAIN_WINDOW_H
#define SHANKS_MAIN_WINDOW_H

#include <memory>
class QWidget;
namespace plan9
{
    class MainWindow {
    public:
        explicit MainWindow();
        void show();
        void set_index_view(QWidget *widget);
        void update_content_view(QWidget *widget);
    private:
        class MainWindowImpl;
        std::shared_ptr<MainWindowImpl> impl_;
    };
}


#endif //SHANKS_MAIN_WINDOW_H
