//
// Created by 刘科 on 2022/12/14.
//

#include "resource_manager.h"
#include <QUiLoader>
#include <QWidget>
#include <QFile>

namespace plan9
{
    QWidget *ResourceManager::load_ui(QString source) {
        QUiLoader loader;
        QFile file(source);
        QWidget *widget = nullptr;
        if (file.open(QFile::ReadOnly)) {
            widget = loader.load(&file, nullptr);
        }
        file.close();
        return widget;
    }
}