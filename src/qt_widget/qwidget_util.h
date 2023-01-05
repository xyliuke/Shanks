//
// Created by 刘科 on 2022/12/9.
//

#ifndef SHANKS_QWIDGETUTIL_H
#define SHANKS_QWIDGETUTIL_H

class QWidget;
class QColor;
class QRect;

namespace plan9
{
    class QWidgetUtil {
    public:
        static void set_background_color(QWidget *widget, QColor color);
        static QRect get_screen_available_rect();
    };
}



#endif //SHANKS_QWIDGETUTIL_H
