//
// Created by 刘科 on 2022/12/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_yuv_left.h" resolved

#include "yuv_left_widget.h"
#include "resource_manager.h"
#include <QHBoxLayout>
#include "qwidget_util.h"

namespace plan9
{
    YUVLeftWidget::YUVLeftWidget(QWidget *parent) :
            QWidget(parent) {
        auto widget = plan9::ResourceManager::load_ui(":ui/yuv/yuv_left_widget.ui", this);
        auto layout = new QHBoxLayout(this);
        layout->addWidget(widget);
        QWidgetUtil::set_background_color(this, Qt::red);
    }

    YUVLeftWidget::~YUVLeftWidget() {

    }
}