//
// Created by 刘科 on 2022/11/23.
//

#include "main_window_manager.h"
#include "yuv_widget.h"
#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QLabel>

namespace plan9
{

    class MainWindowModel {
    public:
        QString text;
        QWidget *widget;
    };

    class MainWindowManager::MainWindowManagerImpl {
    public:
        explicit MainWindowManagerImpl(std::shared_ptr<MainWindow> window) : window_(std::move(window)) {
            init_list_model();

            auto listView = createListView();
            window_->set_index_view(listView.get());

            QLabel *right = new QLabel();
            right->setText("right");
            window_->update_content_view(right);


        }

        void show() {
            window_->show();
        }

    private:
        std::shared_ptr<MainWindow> window_;
        std::shared_ptr<QListView> list_view_;
        std::shared_ptr<YUVWidget> yuv_widget_;
        std::vector<MainWindowModel> list_model_;

        std::shared_ptr<QListView> createListView() {
            if (!list_view_) {
                list_view_ = std::make_shared<QListView>();
                QStringList list = QStringList();
                std::vector<MainWindowModel>::iterator  it = list_model_.begin();
                while (it != list_model_.end()) {
                    list.append(it->text);
                    it ++;
                }
//                list.append("YUV数据");
//                list.append("音频");
                auto model = new QStringListModel(list);
                list_view_->setModel(model);
                QObject::connect(list_view_.get(), &QListView::pressed, [this](QModelIndex index){
                    this->update_content_view(index);
                });
            }
            return list_view_;
        }

        void update_content_view(QModelIndex index) {
            int row = index.row();
            auto model = list_model_[row];
            window_->update_content_view(model.widget);
        }

        void init_list_model() {
            MainWindowModel model;
            model.text = "YUV数据";
            model.widget = new YUVWidget();
            list_model_.push_back(model);

            MainWindowModel model1;
            model1.text = "音频";
            QLabel *right = new QLabel();
            right->setText("right2");
            model1.widget = right;
//            model1.widget = new QWidget();
            list_model_.push_back(model1);
        }

    };

    MainWindowManager::MainWindowManager(std::shared_ptr<MainWindow> window) {
        impl_ = std::make_shared<MainWindowManagerImpl>(window);
    }

    void MainWindowManager::show() {
        impl_->show();
    }
}