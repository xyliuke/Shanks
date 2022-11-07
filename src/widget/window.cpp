//
// Created by 刘科 on 2022/11/4.
//

#include "window.h"
#include <gtk/gtk.h>

namespace plan9 {
    class window::window_impl {
    public:
        explicit window_impl() {
            app = gtk_application_new ("com.shanks", G_APPLICATION_FLAGS_NONE);
            g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
        }
        void show() const {
            g_application_run (G_APPLICATION (app), 0, nullptr);
        }
        ~window_impl() {
            g_object_unref (app);
        }
    private:
        static void activate (GtkApplication *app, gpointer user_data) {
            GtkWidget *window;
            GtkWidget *button;

            window = gtk_application_window_new (app);
            gtk_window_set_title (GTK_WINDOW (window), "Window");
            gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

            button = gtk_button_new_with_label ("Hello World");
//            g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
            gtk_window_set_child (GTK_WINDOW (window), button);

            gtk_window_present (GTK_WINDOW (window));
        }
    private:
        GtkApplication *app;
    };


    window::window() {
        impl_ = std::make_shared<window_impl>();
    }

    void window::show() const {
        impl_->show();
    }
} // plan9