//
// Created by 刘科 on 2022/11/23.
//

#include "main_window_manager.h"
#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QLabel>

namespace plan9
{
    class MainIndexView : public QWidget {

    };

    class MainWindowManager::MainWindowManagerImpl {
    public:
        explicit MainWindowManagerImpl(std::shared_ptr<MainWindow> window) : window_(std::move(window)) {
            auto listView = createListView();
            window_->set_index_view(listView);

            QLabel *right = new QLabel();
            right->setText("right");
            window_->update_content_view(right);
        }

        void show() {
            window_->show();
        }
    private:
        std::shared_ptr<MainWindow> window_;

        QListView* createListView() {
            QListView *listView = new QListView();
            listView->setStyleSheet("{background-color: white; background-attachment: scroll;}");
            QStringList list = QStringList();
            list.append("YUV数据");
            list.append("音频");
            auto model = new QStringListModel(list);
            listView->setModel(model);
            return listView;
        }
    };

    MainWindowManager::MainWindowManager(std::shared_ptr<MainWindow> window) {
        impl_ = std::make_shared<MainWindowManagerImpl>(window);
    }

    void MainWindowManager::show() {
        impl_->show();
    }
}