#include "animation.h"

Animation::Animation(QString filePath, QString projectPath, AnimationFileType fType, int hf, int vf, int fps)
{
    name = filePath.right(filePath.length() - filePath.lastIndexOf("/") - 1);
    name = name.left(name.indexOf("."));
    fileType = fType;
    horizontalFrames = hf;
    verticalFrames = vf;
    frameRate = fps;

    switch (fileType) {
    case SingleFile:{
        QString dataFilePath = projectPath + "/data/" + filePath.right(filePath.length() - filePath.lastIndexOf("/") - 1);
        QFile::copy(filePath, dataFilePath);
        filesPaths.append(dataFilePath);

        if(horizontalFrames == 1 && verticalFrames == 1){
            Frame *frame = new Frame;
            frame->pixmap = new QPixmap(dataFilePath);
            frames.append(frame);
        }
        else{
            // divide by hf and vf

        }
    break;
    }
    case MultipleFiles:{

    break;
    }
    }
}
