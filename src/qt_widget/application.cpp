//
// Created by 刘科 on 2022/11/20.
//

#include "application.h"
#include <QApplication>
#include <QWidget>

namespace plan9
{
    class Application::ApplicationImpl {
    public:
//        explicit ApplicationImpl() : app(std::make_shared<QApplication>(0, nullptr)) {

//        }
        explicit ApplicationImpl(int argc, char **argv) : app(std::make_shared<QApplication>(argc, argv)) {
            QWidget *widget = new QWidget();
            widget->setWindowTitle("Shanks");
            widget->show();
        }

        int run() {
            return app->exec();
        }
    private:
        std::shared_ptr<QApplication> app;
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