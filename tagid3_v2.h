#ifndef TAGID3_V2_H
#define TAGID3_V2_H

#include <QObject>
#include <QFile>
#include "global.h"

struct V2_TAG {
    QString tag;
    int len;
    char flags[2];
    char * content;
};

class TagID3_V2 : public QObject
{
Q_OBJECT
public:
    explicit TagID3_V2(const QString& name, QObject *parent = 0);
    ~TagID3_V2();
    V2_TAG * nextTag();

private:
    QFile *file;
    int version;
    int len;
    int cpos;
    char flags[2];
    char * id3;
    bool readId3();
signals:

public slots:

};

#endif // TAGID3_V2_H
