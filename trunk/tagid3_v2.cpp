#include "tagid3_v2.h"

TagID3_V2::TagID3_V2(const QString& name, QObject *parent) :
    QObject(parent)
{
    this->file = new QFile(name);
    if(file->exists() && file->open(QIODevice::ReadOnly)) {
        this->len = 0;
        this->cpos = 0;
        this->readId3();
    } else {
        delete file;
    }
}

TagID3_V2::~TagID3_V2() {
    if(this->file != NULL) {
        this->file->close();
        delete this->file;
    }
    if(this->id3 != NULL)
        delete[] this->id3;
}

bool TagID3_V2::readId3() {
    if(this->file != NULL) {
        file->seek(0);
        char * sig = new char[3];
        if(this->file->read(sig, 3)) {
            if(sig[0] == 0x49 && sig[1] == 0x44 && sig[2] == 0x33) {
                if(file->read(this->flags, 2)) {
                    char * len = new char[4];
                    if(file->read(len, 4)) {
                        this->len = ((len[0] << 24) & 0xff) | ((len[1] << 16) & 0xff) | ((len[2] << 8) & 0xff) | (len[3] & 0xff);
                        this->id3 = new char[this->len];
                        if(this->file->read(this->id3, this->len) == this->len) {
                            return true;
                        } else {
                            delete[] this->id3;
                        }
                    }
                }
            }
        }
    }
    return false;
}

V2_TAG * TagID3_V2::nextTag() {
    V2_TAG * tag = new V2_TAG;
    char *tagname = new char[4];
    char *flags;
    tagname[0] = *this->id3;
    this->id3++;
    tagname[1] = *this->id3;
    this->id3++;
    tagname[2] = *this->id3;
    this->id3++;
    tagname[3] = *this->id3;
    this->id3++;
    flags[0] = *this->id3;
    this->id3++;
    flags[1] = *this->id3;
    this->id3++;
}
