//
// Created by 刘科 on 2022/11/12.
//

#include "resource.h"
#include "resources.h"
/**
 * 在widget目录下执行
 * glib-compile-resources ./widget.assets/widget.gresource.xml --target=resources.h --generate-source
 * 生成资源的源文件，包含了xml配置的ui文件，这样不需要再把ui文件copy到可执行文件目录。
 */

namespace plan9
{
    Glib::RefPtr<Gtk::Builder> resource::getMenuBarBuilder() {
        return Gtk::Builder::create_from_resource("/shanks/widget/menu_bar");
    }

    Glib::RefPtr<Gtk::Builder> resource::getWindowBuilder() {
        return Gtk::Builder::create_from_resource("/shanks/widget/window");
    }
}