//
// Created by 刘科 on 2022/12/14.
//

#ifndef SHANKS_RESOURCE_MANAGER_H
#define SHANKS_RESOURCE_MANAGER_H

#include <string>

class QWidget;
class QString;

namespace plan9
{
    class ResourceManager {
    public:
        static QWidget *load_ui(QString source);
    };
}


#endif //SHANKS_RESOURCE_MANAGER_H
