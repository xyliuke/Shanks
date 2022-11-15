//
// Created by 刘科 on 2022/11/14.
//

#include "application.h"
#include <gtkmm.h>
#include "main_window.h"
#include "resource.h"
#include <iostream>

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
            add_action("new_menu",
                       sigc::mem_fun(*this, &application_impl::on_menu_file_new_generic));

            auto builder = resource::getMenuBarBuilder();
            auto menu = builder->get_object<Gio::Menu>("menubar");
            set_menubar(menu);
        }

        void on_activate() override {
            Application::on_activate();
            window = std::make_shared<MainWindow>();
            add_window(*(window->get_window()));
            window->show();
        }

    private:
        std::shared_ptr<MainWindow> window;
        void on_menu_file_new_generic() {
            std::cout << "A File|New menu item was selected." << std::endl;
        }
    };

    Application::Application() {
        impl_ = std::make_shared<application_impl>();
    }

    int Application::run() {
        return impl_->run();
    }
}