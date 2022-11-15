//
// Created by 刘科 on 2022/11/12.
//

#ifndef SHANKS_RESOURCE_H
#define SHANKS_RESOURCE_H
#include <gtkmm.h>
#include <glibmm/refptr.h>

namespace plan9
{
    class resource {
    public:
        static Glib::RefPtr<Gtk::Builder> getMenuBarBuilder();
        static Glib::RefPtr<Gtk::Builder> getWindowBuilder();
    };
}


#endif //SHANKS_RESOURCE_H
