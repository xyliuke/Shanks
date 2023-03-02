//
// Created by 刘科 on 2022/11/28.
//

#include "yuv_widget.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include "qwidget_util.h"
#include "resource_manager.h"
#include "render_widget.h"
#include <QUiLoader>

namespace plan9
{
    class FileSelector : public QWidget {
    public:
        explicit FileSelector() {
            QWidgetUtil::set_background_color(this, Qt::blue);
            auto layout = new QHBoxLayout(this);
            layout->setContentsMargins(0, 0, 0, 0);
            button_ = new QPushButton("打开文件");
            auto policy(button_->sizePolicy());
            policy.setHorizontalPolicy(QSizePolicy::Fixed);
            button_->setSizePolicy(policy);
            button_->setFixedWidth(70);
            label_ = new QLabel("abcd");
            layout->addWidget(button_);
            layout->setSpacing(5);
            layout->addWidget(label_);

            connect(button_, &QPushButton::pressed, [this]() {
                file_ = QFileDialog::getOpenFileName(this, "选择YUV文件", "~", "*");
                label_->setText(file_);
            });
        }

    private:
        QLabel *label_;
        QPushButton *button_;
        QString file_;
    };

    class YUVWidget::YUVWidgetImpl {
    public:
        explicit YUVWidgetImpl(QWidget *widget) : parent_(widget) {
            QWidget *myWidget = ResourceManager::load_ui(":/ui/yuv/yuv_widget.ui");
            auto layout = new QVBoxLayout(widget);
            layout->setContentsMargins(1, 1, 1, 1);
            layout->addWidget(myWidget);

            auto renderWidget = myWidget->findChild<RenderWidget *>("center");
            auto image = std::make_shared<QImage>(":image/images/test.jpeg");
            renderWidget->updateImage(image);
        }

        ~YUVWidgetImpl() {

        }
    private:
        QWidget *parent_;
        QHBoxLayout *layout_;

        QWidget *createLeftWidget() {
            auto widget = new QWidget();
            auto layout = new QVBoxLayout(widget);
            layout->setContentsMargins(0, 0, 0, 0);
            auto groupBox = new QGroupBox(widget);
            layout->addWidget(groupBox);
            groupBox->setTitle("输入");

            auto groupBoxLayout = new QVBoxLayout(groupBox);
            groupBoxLayout->setContentsMargins(0, 0, 0, 0);
            auto fileSelector = new FileSelector();
            groupBoxLayout->addWidget(fileSelector);
            auto filePolicy = fileSelector->sizePolicy();
            filePolicy.setVerticalPolicy(QSizePolicy::Fixed);
            fileSelector->setSizePolicy(filePolicy);
            fileSelector->setFixedHeight(50);

            auto pushButton = new QPushButton(groupBox);
            pushButton->setText("分析YUV");
            groupBoxLayout->addWidget(pushButton);
            connect(pushButton, &QPushButton::pressed, [](){

            });

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
    }


}