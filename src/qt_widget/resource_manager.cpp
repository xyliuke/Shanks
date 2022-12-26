//
// Created by 刘科 on 2022/12/14.
//

#include "resource_manager.h"
#include <QUiLoader>
#include <QWidget>
#include <QFile>
#include <QDirIterator>
#include "yuv_left_widget.h"

namespace plan9
{
    class UILoader : public QUiLoader {
        QWidget * createWidget(const QString &className, QWidget *parent = nullptr, const QString &name = QString()) override {
            if (className == "YUVLeftWidget") {
                QWidget *widget = new YUVLeftWidget(parent);
                widget->setObjectName(name);
                return widget;
            }
            return QUiLoader::createWidget(className, parent, name);
        }
    };

    QWidget *ResourceManager::load_ui(const QString &source) {
        return load_ui(source, nullptr);
    }

    QWidget *ResourceManager::load_ui(const QString &source, QWidget *parent) {
        UILoader loader;
        QFile file(source);
        QWidget *widget = nullptr;
        if (file.open(QFile::ReadOnly)) {
            widget = loader.load(&file, parent);
        }
        file.close();
//        auto itt = loader.pluginPaths().begin();
//        while (itt != loader.pluginPaths().end()) {
//            qDebug() << *itt << "\n";
//            itt ++;
//        }
//
//        auto it = loader.availableWidgets().begin();
//        while (it != loader.availableWidgets().end()) {
//            qDebug() << *it << "\n";
//            it ++;
//        }
        return widget;
    }

    void ResourceManager::print_resources() {
        QDirIterator iterator(":", QDirIterator::Subdirectories);
        while (iterator.hasNext()) {
            qDebug() << iterator.next();
        }
    }
}