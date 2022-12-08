//
// Created by 刘科 on 2022/12/9.
//

#include "qwidget_util.h"
#include <QWidget>

namespace plan9
{
    void QWidgetUtil::set_background_color(QWidget *widget, QColor color) {
        auto p= widget->palette();
        p.setColor(QPalette::Window, color);
        widget->setAutoFillBackground(true);
        widget->setPalette(p);
    }
}