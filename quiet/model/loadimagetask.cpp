#include "loadimagetask.h"

LoadImageTask::LoadImageTask(QString& path): _path(path)
{

}

void LoadImageTask::run()
{
    std::shared_ptr<Image> img = nullptr;
    img.reset(new Image(_path));

    emit loadDone(img, _path);
}
