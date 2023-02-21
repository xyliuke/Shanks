//
// Created by 刘科 on 2023/1/6.
//

#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "render_widget.h"
#include <QFile>

namespace plan9
{
    class RenderWidget::RenderWidgetImpl : protected QOpenGLFunctions {
    public:
        explicit RenderWidgetImpl(QOpenGLWidget *openGlWidget) {
            this->openGlWidget_ = openGlWidget;
        }

        ~RenderWidgetImpl() {
        }

        void initializeGL() {
            initOpenGL();
        }
        void paintGL() {
            paintOpenGL();
        }
        void resizeGL(int w, int h) {

        }

    private:
        void initOpenGL() {
            initializeOpenGLFunctions();

            vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            QFile vertFile(":shader/shader/vertex_shader.glsl");
            if (vertFile.open(QFile::ReadOnly)) {
                qint64 size = vertFile.size();
                auto buf = new char[size + 1]();
                vertFile.read(buf, size + 1);
                buf[size] = '\0';
                glShaderSource(vertex_shader, 1, (const char **)&buf, NULL);
                delete []buf;
                glCompileShader(vertex_shader);
                int success;
                char infoLog[512];
                glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
                }
            }
            frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
            QFile fragFile(":shader/shader/fragment_shader.glsl");
            if (fragFile.open(QFile::ReadOnly)) {
                qint64 size = fragFile.size();
                auto buf = new char[size + 1]();
                fragFile.read(buf, size + 1);
                buf[size] = '\0';
                glShaderSource(frag_shader, 1, (const char **)&buf, NULL);
                delete []buf;
                glCompileShader(frag_shader);
                int success;
                char infoLog[512];
                glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
                }
            }

            shader_program = glCreateProgram();
            glAttachShader(shader_program, vertex_shader);
            glAttachShader(shader_program, frag_shader);
            glLinkProgram(shader_program);
            // check for linking errors
            int success;
            glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
            if (!success) {
                char infoLog[512];
                glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);
            }
            glDeleteShader(vertex_shader);
            glDeleteShader(frag_shader);

            float vertices[] = {
                // positions          // colors           // texture coords
                0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left
            };
            unsigned int indices[] = {
                0, 1, 3, // first triangle
                1, 2, 3  // second triangle
            };
            GLuint VBO, EBO;
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//            glEnableVertexAttribArray(1);
            // texture coord attribute

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            QImage image(":image/images/test.jpeg");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), (GLsizei)image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
            glGenerateMipmap(GL_TEXTURE_2D);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glUniform1i(glGetUniformLocation(frag_shader, "ourTexture"), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void paintOpenGL() {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUseProgram(shader_program);
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

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
//        QOpenGLShaderProgram *program_;
//        QOpenGLShader *fragmentShader;
//        QOpenGLVertexArrayObject *vao;
//        QOpenGLBuffer *vbo;
//        QOpenGLBuffer *ebo;

        GLuint shader_program;
        GLuint vertex_shader;
        GLuint frag_shader;
        GLuint vao;
        GLuint texture;
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