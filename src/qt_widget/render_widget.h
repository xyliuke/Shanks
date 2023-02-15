//
// Created by 刘科 on 2023/1/6.
//

#ifndef SHANKS_RENDER_WIDGET_H
#define SHANKS_RENDER_WIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace plan9
{
    class RenderWidget : public QOpenGLWidget {
    public:
        explicit RenderWidget(QWidget *parent);
    protected:
        void initializeGL() override;
        void paintGL() override;
        void resizeGL(int w, int h) override;
    private:
        class RenderWidgetImpl;
        std::shared_ptr<RenderWidgetImpl> impl_;
    };

}


#endif //SHANKS_RENDER_WIDGET_H
