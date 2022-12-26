//
// Created by 刘科 on 2022/11/20.
//

#include "application.h"
#include <QApplication>
#include <QWidget>
#include "main_window.h"
#include "main_window_manager.h"
#include <QFile>

class LoadQtQrc {
public:
    explicit LoadQtQrc(std::shared_ptr<QApplication> app) {
        Q_INIT_RESOURCE(widget);

        load_style(std::move(app));
    }
    ~LoadQtQrc() {
        Q_CLEANUP_RESOURCE(widget);
    }
private:
    void load_style(const std::shared_ptr<QApplication> app) {
        QFile file(":/style/style.qss");
        if (file.open(QFile::ReadOnly)) {
            QString string = QString(file.readAll());
            app->setStyleSheet(string);
        }
        file.close();
    }
};

namespace plan9
{
    class Application::ApplicationImpl {
    public:
        explicit ApplicationImpl(int argc, char **argv) : app_(std::make_shared<QApplication>(argc, argv)) {
            main_window_ = std::make_shared<MainWindow>();
            load_qrc_ = std::make_shared<LoadQtQrc>(app_);
            main_window_manager_ = std::make_shared<MainWindowManager>(main_window_);
            main_window_manager_->show();
        }

        int run() {
            return app_->exec();
        }
    private:
        std::shared_ptr<QApplication> app_;
        std::shared_ptr<MainWindow> main_window_;
        std::shared_ptr<MainWindowManager> main_window_manager_;
        std::shared_ptr<LoadQtQrc> load_qrc_;


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