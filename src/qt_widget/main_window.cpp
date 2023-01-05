//
// Created by 刘科 on 2022/11/20.
//

#include "main_window.h"
#include <QWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QLabel>
#include "qwidget_util.h"

namespace plan9
{

    class MainWindow::MainWindowImpl {
    public:
        explicit MainWindowImpl() : widget_(std::make_shared<QWidget>()) {
            widget_->setWindowTitle("Shanks");
            QRect rect = QWidgetUtil::get_screen_available_rect();
            widget_->resize(rect.width(), rect.height());
            auto layout = new QHBoxLayout(widget_.get());
            layout->setContentsMargins(1 ,1 ,1 ,1);
            splitter_ = std::make_shared<QSplitter>(Qt::Orientation::Horizontal, widget_.get());
            splitter_->setMouseTracking(true);

            left_widget_ = std::make_shared<QWidget>();
            QSizePolicy policy = left_widget_->sizePolicy();
            policy.setHorizontalStretch(1);
            left_widget_->setSizePolicy(policy);

            right_widget_ = std::make_shared<QWidget>();
            QSizePolicy policy2 = left_widget_->sizePolicy();
            policy2.setHorizontalStretch(4);
            left_widget_->setSizePolicy(policy2);

            splitter_->addWidget(left_widget_.get());
            splitter_->addWidget(right_widget_.get());
            layout->addWidget(splitter_.get());
            splitter_->setCollapsible(0, true);
        }
        void show() {
            widget_->show();
        }

        void set_index_view(QWidget *widget) {
            QSizePolicy policy = widget->sizePolicy();
            policy.setHorizontalStretch(1);
            widget->setSizePolicy(policy);
            splitter_->replaceWidget(0, widget);
        }

        void update_content_view(QWidget *widget) {
            QSizePolicy policy = widget->sizePolicy();
            policy.setHorizontalStretch(4);
            widget->setSizePolicy(policy);
            splitter_->replaceWidget(1, widget);
        }

    private:
        std::shared_ptr<QWidget> widget_;
        std::shared_ptr<QSplitter> splitter_;
        std::shared_ptr<QWidget> left_widget_;
        std::shared_ptr<QWidget> right_widget_;
    };

    MainWindow::MainWindow() {
        impl_ = std::make_shared<MainWindowImpl>();
    }

    void MainWindow::show() {
        impl_->show();
    }

    void MainWindow::set_index_view(QWidget *widget) {
        impl_->set_index_view(widget);
    }

    void MainWindow::update_content_view(QWidget *widget) {
        impl_->update_content_view(widget);
    }
}