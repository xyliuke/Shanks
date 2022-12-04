//
// Created by 刘科 on 2022/11/28.
//

#ifndef SHANKS_YUV_WIDGET_H
#define SHANKS_YUV_WIDGET_H

#include <QWidget>
#include <memory>

namespace plan9
{
    class YUVWidget : public QWidget {
    public:
        explicit YUVWidget();


    private:
        class YUVWidgetImpl;
        std::shared_ptr<YUVWidgetImpl> impl_;
    };
}


#endif //SHANKS_YUV_WIDGET_H
