//
// Created by 刘科 on 2022/11/20.
//

#include "main_window.h"
#include <QWidget>

namespace plan9
{

    class MainWindow::MainWindowImpl {
    public:
        explicit MainWindowImpl() : widget(std::make_shared<QWidget>()) {
            widget->setWindowTitle("Shanks");
            widget->resize(1280, 960);
        }
        void show() {
            widget->show();
        }
    private:
        std::shared_ptr<QWidget> widget;
    };

    MainWindow::MainWindow() {
        impl_ = std::make_shared<MainWindowImpl>();
    }

    void MainWindow::show() {
        impl_->show();
    }
}