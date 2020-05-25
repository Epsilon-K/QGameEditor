#ifndef HELPER_H
#define HELPER_H
#include <QtCore>
#include <QFileDialog>
#include <QMessageBox>
#include <stdlib.h>

// Contains Static functions only

class Helper
{
public:
    Helper();

    static QString getFileNameWithExtension(QString &path){
        return path.right(path.size() - path.lastIndexOf("/") - 1 );
    }

    static QString getNameWithOutExtension(QString &fileName){
        return fileName.left(fileName.lastIndexOf("."));
    }

    static QString getExtension(QString &fileName){
        return  fileName.right(fileName.size() - fileName.lastIndexOf(".") - 1);
    }

    static void debugMSG(QString title, QString text){
        qDebug() << title << " : ";
        qDebug() << text;
    }

    static QString getRandomString(int size){
        QString str;
        for(int i = 0; i < size; i++){
            str += rand()%26 + 65;
        }
        return str;
    }
};

#endif // HELPER_H
