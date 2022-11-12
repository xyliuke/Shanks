//
// Created by 刘科 on 2022/11/12.
//

#ifndef SHANKS_RESOURCE_H
#define SHANKS_RESOURCE_H
#include <gtk/gtk.h>

namespace plan9
{
    class resource {
    public:
        static GtkBuilder* getMenuBarBuilder();
        static GtkBuilder* getWindowBuilder();
    };
}


#endif //SHANKS_RESOURCE_H
