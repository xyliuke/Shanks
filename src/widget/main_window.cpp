//
// Created by 刘科 on 2022/11/14.
//

#include "main_window.h"
#include <gtkmm.h>

namespace plan9
{
    class MainWindow::MainWindowImpl : public Gtk::ApplicationWindow {
    public:
        MainWindowImpl() {
            set_title("Shanks");
            set_default_size(800, 600);
            set_show_menubar(true);
        }
    };

    MainWindow::MainWindow() {
        impl_ = std::make_shared<MainWindowImpl>();
    }

    Gtk::Window * MainWindow::get_window() {
        return static_cast<Gtk::Window *>(impl_.get());
    }

    void MainWindow::show() {
        impl_->show();
    }
}