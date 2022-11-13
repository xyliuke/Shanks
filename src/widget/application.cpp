//
// Created by 刘科 on 2022/11/14.
//

#include "application.h"
#include <gtkmm.h>

namespace plan9
{
    class application::application_impl : public Gtk::Window {
    public:
        application_impl() {
            set_title("hello");
            set_default_size(800, 600);
        }
    };

    application::application() {
//        impl_ = std::make_shared<application_impl>();
    }

    void application::show() {
        auto app = Gtk::Application::create("com.shanks");
        app->make_window_and_run<application::application_impl>(0, nullptr);
    }
}