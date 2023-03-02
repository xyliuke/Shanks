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
        enum RenderFillMode {
            Fill,//可能会变形填充
            Fit,//宽度对齐，高度自适应，按比例缩放，可能会有黑边
            AspectFill//按照最小边对齐，按比例缩放，会裁剪
        };
        explicit RenderWidget(QWidget *parent);
        void updateImage(std::shared_ptr<QImage> image);
        void setFillMode(RenderFillMode mode);

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
