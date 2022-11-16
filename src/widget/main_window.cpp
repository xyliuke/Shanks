//
// Created by 刘科 on 2022/11/14.
//

#include "main_window.h"
#include <gtkmm.h>
#include "resource.h"

namespace plan9
{
    class MainWindow::MainWindowImpl {
    public:
        MainWindowImpl() {
            auto builder = resource::getWindowBuilder();
            window = Glib::make_refptr_for_instance(builder->get_widget<Gtk::Window>("window"));
        }

        void show() {
            window->show();
        }

        Gtk::Window * get_window() {
            return window.get();
        }
    private:
        Glib::RefPtr<Gtk::Window> window;
    };

    MainWindow::MainWindow() {
        impl_ = std::make_shared<MainWindowImpl>();
    }

    Gtk::Window * MainWindow::get_window() {
        return impl_->get_window();
    }

    void MainWindow::show() {
        impl_->show();
    }
}