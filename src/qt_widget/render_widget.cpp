//
// Created by 刘科 on 2023/1/6.
//

#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "render_widget.h"

namespace plan9
{
    class RenderWidget::RenderWidgetImpl : protected QOpenGLFunctions {
    public:
        explicit RenderWidgetImpl(QOpenGLWidget *openGlWidget) {
            this->openGlWidget_ = openGlWidget;
        }

        ~RenderWidgetImpl() {
            delete vao;
            delete vbo;
            delete ebo;
            delete program_;
        }

        void initializeGL() {
            initializeOpenGLFunctions();
            glClearColor(0.0, 0.0, 0.0,1.0);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_DEPTH_TEST);

            auto vertShader = new QOpenGLShader(QOpenGLShader::Vertex, this->openGlWidget_);
            if (!(vertShader->compileSourceFile(":shader/shader/vertex_shader.glsl"))) {
                qDebug() << "vertex shader error";
            }
            fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, this->openGlWidget_);
            if (!(fragmentShader->compileSourceFile(":shader/shader/fragment_shader.glsl"))) {
                qDebug() << "fragment shader error";
            }

            program_ = new QOpenGLShaderProgram;
            program_->addShader(vertShader);
            program_->addShader(fragmentShader);
            program_->link();
            program_->bind();

            float vertices[] = {
                0.5f, 0.5f, 0.0f, 1.0f, 1.f,  // 右上角
                0.5f, -0.5f, 0.0f, 1.f, 0.f,  // 右下角
                -0.5f, -0.5f, 0.0f, 0.f, 0.f,// 左下角
                -0.5f, 0.5f, 0.0f, 0.f, 1.f,   // 左上角
            };

            unsigned int indices[] = {
                    0, 1, 3, // first triangle
                    1, 2, 3  // second triangle
            };

            vao = new QOpenGLVertexArrayObject();
            vao->create();
            vao->bind();

            vbo = new QOpenGLBuffer();
            vbo->create();
            vbo->bind();
            vbo->allocate(vertices, sizeof(vertices));

            ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
            ebo->create();

            program_->setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
            program_->enableAttributeArray("aPos");

            ebo->bind();
            ebo->setUsagePattern(QOpenGLBuffer::StaticDraw);
            ebo->allocate(indices, sizeof(indices));

//            initTexture();
            //向顶点着色器传递其中定义为"aColor"的变量所需的数据
//            m_color=program->attributeLocation("aColor");
//            program->setAttributeBuffer(m_color,GL_FLOAT,3*sizeof(GLfloat),3,6*sizeof(GLfloat));
//            program->enableAttributeArray(m_color);

            program_->release();//解绑程序
        }
        void paintGL() {
            program_->bind();//绑定绘制所要使用的openGL程序
            vao->bind();//绑定包含openGL程序所需信息的VAO
            ebo->bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);//绘制
            vao->release();//解绑VAO
            ebo->release();
            program_->release();//解绑程序
        }
        void resizeGL(int w, int h) {

        }

    private:
//        void initTexture() {
//            QOpenGLTexture texture(QOpenGLTexture::Target2D);
//            texture.create();
//            texture.setSize(100, 100);
//            texture.allocateStorage();
//            QImage image(":image/images/test.jpeg");
//            texture.setData(image);
//            texture.bind(0);
//            program_->setUniformValue("ourTexture", 0);
//
//
//
//            unsigned int indices[] = {
//                    // 注意索引从0开始!
//                    // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
//                    // 这样可以由下标代表顶点组合成矩形
//                    0, 1, 3, // 第一个三角形
//                    1, 2, 3  // 第二个三角形
//            };
//        }
    private:
        QOpenGLWidget *openGlWidget_;
        QOpenGLShaderProgram *program_;
        QOpenGLShader *fragmentShader;
        QOpenGLVertexArrayObject *vao;
        QOpenGLBuffer *vbo;
        QOpenGLBuffer *ebo;
    };

    RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent){
        impl_ = std::make_shared<RenderWidgetImpl>(this);
    }

    void RenderWidget::initializeGL() {
        impl_->initializeGL();
    }

    void RenderWidget::paintGL() {
        impl_->paintGL();
    }

    void RenderWidget::resizeGL(int w, int h) {
        impl_->resizeGL(w, h);
    }
}