//
// Created by 刘科 on 2022/11/20.
//

#include "application.h"
#include <QApplication>
#include <QWidget>
#include "main_window.h"

namespace plan9
{
    class Application::ApplicationImpl {
    public:
        explicit ApplicationImpl(int argc, char **argv) : app_(std::make_shared<QApplication>(argc, argv)) {
            main_window_ = std::make_shared<MainWindow>();
            main_window_->show();
        }

        int run() {
            return app_->exec();
        }
    private:
        std::shared_ptr<QApplication> app_;
        std::shared_ptr<MainWindow> main_window_;
    };

    Application::Application() {
        impl_ = std::make_shared<ApplicationImpl>(0, nullptr);
    }

    Application::Application(int argc, char **argv) {
        impl_ = std::make_shared<ApplicationImpl>(argc, argv);
    }

    int Application::run() {
        return impl_->run();
    }
}