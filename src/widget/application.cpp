//
// Created by 刘科 on 2022/11/14.
//

#include "application.h"
#include <gtkmm.h>
#include "main_window.h"

namespace plan9
{
    class Application::application_impl : public Gtk::Application {
    public:
        application_impl() : Gtk::Application("com.shanks") {
            Glib::set_application_name("shanks");
        }

    protected:
        void on_startup() override {
            Application::on_startup();
        }

        void on_activate() override {
            Application::on_activate();
            window = std::make_shared<MainWindow>();
            add_window(*(window->get_window()));
            window->show();
        }

    private:
        std::shared_ptr<MainWindow> window;
    };

    Application::Application() {
        impl_ = std::make_shared<application_impl>();
    }

    int Application::run() {
        return impl_->run();
//        auto app = Gtk::Application::create("com.shanks");
//        app->make_window_and_run<application::application_impl>(0, nullptr);
    }
}