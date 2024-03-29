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
    static unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    class RenderWidget::RenderWidgetImpl : protected QOpenGLFunctions {
    public:
        explicit RenderWidgetImpl() : vertices(new float[20]()) {
            initVertices(mode_);
        }

        ~RenderWidgetImpl() {
            delete[] vertices;
        }

        void initializeGL() {
            initializeOpenGLFunctions();
            initShader();
            initOpenGL();
            isInitOpenGL_ = true;
            updateImage(image_);
        }
        void paintGL() {
            paintOpenGL();
        }
        void resizeGL(int w, int h) {
            if (window_width_ != w || window_height_ != h) {
                isRefreshVertices = true;
            }
            window_width_ = w;
            window_height_ = h;
            if (isRefreshVertices) {
                updateVerticesIfNeed();
                isRefreshVertices = false;
            }
        }

        void updateImage(std::shared_ptr<QImage> image) {
            if (isInitOpenGL_) {
                if (image_width_ != image->width() || image_height_ != image->height()) {
                    isRefreshVertices = true;
                }
                image_width_ = image->width();
                image_height_ = image->height();
                if (isRefreshVertices) {
                    updateVerticesIfNeed();
                    isRefreshVertices = false;
                }
                QImage horFlipImage = image->mirrored(false, true);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width(), (GLsizei)image->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, horFlipImage.bits());
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                this->image_ = image;
            }
        }
        void setFillMode(RenderFillMode mode) {
            if (this->mode_ != mode) {
                isRefreshVertices = true;
            }
            this->mode_ = mode;
        }

    private:

        void initShader() {
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
        }

        void initDefaultFillVertices(float x, float y) {
            // top right
            vertices[0] = x;
            vertices[1] = y;
            vertices[2] = 0.f;
            // top right texture
            vertices[3] = 1.f;
            vertices[4] = 1.f;

            // bottom right
            vertices[5] = x;
            vertices[6] = -y;
            vertices[7] = 0.f;
            // bottom right texture
            vertices[8] = 1.f;
            vertices[9] = 0.f;

            // bottom left
            vertices[10] = -x;
            vertices[11] = -y;
            vertices[12] = 0.f;
            // bottom left texture
            vertices[13] = 0.f;
            vertices[14] = 0.f;

            // top left
            vertices[15] = -x;
            vertices[16] = y;
            vertices[17] = 0.f;
            // top left texture
            vertices[18] = 0.f;
            vertices[19] = 1.f;
        }

        void initVertices(RenderFillMode mode) {
            if (mode == Fill) {
                initDefaultFillVertices(1.f, 1.f);
            } else if (mode == Fit){
                if (window_width_ == 0 || window_height_ == 0 || image_height_ == 0 || image_width_ == 0) {
                    initDefaultFillVertices(1.f, 1.f);
                    return;
                }
                float y =  (image_height_ * 1.f / image_width_) / (window_height_ * 1.f / window_width_);
                initDefaultFillVertices(1.f, y);
            } else if (mode == AspectFill) {
                if (window_width_ == 0 || window_height_ == 0 || image_height_ == 0 || image_width_ == 0) {
                    initDefaultFillVertices(1.f, 1.f);
                    return;
                }
                float x =  (image_width_ * 1.f / image_height_) / (window_width_ * 1.f / window_height_);
                initDefaultFillVertices(x, 1.f);
            }
        }

        void updateVerticesIfNeed() {
            initVertices(mode_);
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 20, vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

        void initOpenGL() {
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);

            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 20, vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // texture coord attribute
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glUniform1i(glGetUniformLocation(frag_shader, "ourTexture"), 0);
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

    private:
        bool isInitOpenGL_{false};
        GLuint shader_program{0};
        GLuint vertex_shader;
        GLuint frag_shader;
        GLuint vao{0};
        GLuint vbo{0};
        GLuint ebo{0};
        GLuint texture;
        float *vertices;
        RenderFillMode mode_{Fit};
        int image_width_{0};
        int image_height_{0};
        int window_width_{0};
        int window_height_{0};
        std::shared_ptr<QImage> image_;
        bool isRefreshVertices{false};
    };

    RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent){
        impl_ = std::make_shared<RenderWidgetImpl>();
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

    void RenderWidget::setFillMode(RenderFillMode mode) {
        impl_->setFillMode(mode);
    }

    void RenderWidget::updateImage(std::shared_ptr<QImage> image) {
        impl_->updateImage(image);
    }
}