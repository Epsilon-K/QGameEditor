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
            QImage sheet = QImage(dataFilePath);
            int framesCount = horizontalFrames * verticalFrames;
            int imgWidth = sheet.width() / horizontalFrames;
            int imgHeight = sheet.height() / verticalFrames;

            for(int i = 0; i < framesCount; i++){
                Frame *frame = new Frame;
                int xp = i%hf * imgWidth;
                int yp = i/hf * imgHeight;
                frame->pixmap = new QPixmap(QPixmap::fromImage(sheet.copy(xp,yp, imgWidth, imgHeight)));
                frames.append(frame);
            }
        }
    break;
    }
    case MultipleFiles:{

    break;
    }
    }
}
