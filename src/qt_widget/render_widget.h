//
// Created by 刘科 on 2023/1/6.
//

#ifndef SHANKS_RENDER_WIDGET_H
#define SHANKS_RENDER_WIDGET_H
#include <QOpenGLWidget>
namespace plan9
{
    class RenderWidget : public QOpenGLWidget {
    public:
        RenderWidget(QWidget *parent);
    };

}


#endif //SHANKS_RENDER_WIDGET_H
