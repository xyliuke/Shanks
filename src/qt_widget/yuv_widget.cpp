//
// Created by 刘科 on 2022/11/28.
//

#include "yuv_widget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

namespace plan9
{
    class YUVWidget::YUVWidgetImpl {
    public:
        explicit YUVWidgetImpl(QWidget *widget) : parent_(widget) {
            layout_ = new QHBoxLayout(widget);
            auto left = createLeftWidget();
            layout_->addWidget(left, 2);

            auto content = createContentWidget();
            layout_->addWidget(content, 6);

            auto right = createRightWidget();
            layout_->addWidget(right, 2);
//            layout_ = new QVBoxLayout(widget);
//            auto groupBox = new QGroupBox(widget);
//            groupBox->setTitle("输入");
//            layout_->addWidget(groupBox);
//

        }

        ~YUVWidgetImpl() {

        }
    private:
        QWidget *parent_;
        QHBoxLayout *layout_;

        QWidget *createLeftWidget() {
            auto widget = new QWidget();
            auto layout = new QVBoxLayout(widget);

            auto groupBox = new QGroupBox(widget);
            layout->addWidget(groupBox);
            groupBox->setTitle("输入");

            auto groupBoxLayout = new QVBoxLayout(groupBox);
            auto pushButton = new QPushButton(groupBox);
            pushButton->setText("测试");
            groupBoxLayout->addWidget(pushButton);

            return widget;
        }

        QWidget *createContentWidget() {
            auto widget = new QWidget();
            return widget;
        }

        QWidget *createRightWidget() {
            auto widget = new QWidget();
            return widget;
        }
    };

    YUVWidget::YUVWidget() {
        impl_ = std::make_shared<YUVWidgetImpl>(this);
//        this->setAutoFillBackground(true);
//        this->setStyleSheet("{background-color:red}");
        QPalette p(this->palette());
        p.setColor( QPalette::Window, Qt::red );
        this->setPalette( p );
    }


}