//
// Created by 刘科 on 2022/11/4.
//

#include "window.h"
#include <gtk/gtk.h>
#include <fstream>
#include <memory>
#include "resource.h"

namespace plan9 {
    static void ok_button1_clicked() {
        g_print("click");
    }
    class window::window_impl {
    public:
        explicit window_impl() {
            app = gtk_application_new ("com.shanks", G_APPLICATION_FLAGS_NONE);
            g_signal_connect (app, "startup", G_CALLBACK (app_startup), this);
            g_signal_connect (app, "activate", G_CALLBACK (activate), this);
        }
        void show() const {
            g_application_run (G_APPLICATION (app), 0, nullptr);
        }
        ~window_impl() {
            g_object_unref (app);
        }
    private:
        static void activate (GtkApplication *app, gpointer user_data) {
            /* Construct a GtkBuilder instance and load our UI description */
            GtkBuilder *builder = resource::getWindowBuilder();
            GObject *window = gtk_builder_get_object (builder, "window");
            gtk_window_set_application (GTK_WINDOW (window), app);

            const GActionEntry win_entries[] = {
                    { "new", new_activated, NULL, NULL, NULL },
                    };
            GSimpleActionGroup *group;
            group = g_simple_action_group_new ();
            g_action_map_add_action_entries (G_ACTION_MAP (group), win_entries, G_N_ELEMENTS (win_entries), nullptr);
            g_object_unref(group);

            auto impl = reinterpret_cast<window_impl *>(user_data);
            impl->create_menu_bar();

            gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (window), true);
            gtk_widget_show (GTK_WIDGET (window));
            
            g_object_unref (builder);
        }

        static void app_startup (GApplication *app, gpointer user_data) {
//            auto impl = reinterpret_cast<window_impl *>(user_data);
//            impl->create_menu_bar();
        }

        void create_menu_bar() {
            GtkBuilder *builder = resource::getMenuBarBuilder();
            GMenuModel *menubar = G_MENU_MODEL (gtk_builder_get_object (builder, "menubar"));
            gtk_application_set_menubar (GTK_APPLICATION (app), menubar);
            g_object_unref (builder);
        }

        static void new_activated (GSimpleAction *action, GVariant *parameter, gpointer win) {
            g_print("hello");
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