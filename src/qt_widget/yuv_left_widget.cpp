//
// Created by 刘科 on 2022/12/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_yuv_left.h" resolved

#include "yuv_left_widget.h"
#include "resource_manager.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include "qwidget_util.h"

namespace plan9
{
    class YUVLeftWidget::YUVLeftWidgetImpl {
    public:
        explicit YUVLeftWidgetImpl(QWidget *widget) {
            auto yuvWidget = plan9::ResourceManager::load_ui(":ui/yuv/yuv_left_widget.ui", widget);
            auto layout = new QHBoxLayout(widget);
            layout->addWidget(yuvWidget);
            QWidgetUtil::set_background_color(widget, Qt::red);

            auto button = yuvWidget->findChild<QPushButton *>("open_file_button");
            auto label = yuvWidget->findChild<QLabel *>("open_file_label");
            connect(button, &QPushButton::pressed, [widget, label, this](){
                file_ = QFileDialog::getOpenFileName(widget, "选择YUV文件", "~", "*");
                label->setText(file_);
                label->setToolTip(file_);
            });
        }

    private:
        QString file_;
    };

    YUVLeftWidget::YUVLeftWidget(QWidget *parent) :
            QWidget(parent) {
        impl_ = std::make_shared<YUVLeftWidgetImpl>(this);
    }

    YUVLeftWidget::~YUVLeftWidget() {

    }
}