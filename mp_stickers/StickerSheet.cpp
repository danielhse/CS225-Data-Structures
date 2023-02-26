#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>
#include "Image.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    size_ = max;
    background = new Image(picture);
    ptr = new Image*[size_];
    x_ = new unsigned[max];
    y_ = new unsigned[max];
    num = 0;
}

StickerSheet::~StickerSheet() {
    for (unsigned i = 0; i < num; i++) {
        delete ptr[i];
    }
    delete[] x_;
    delete[] y_;
    delete background;
    delete[] ptr;

}

StickerSheet::StickerSheet(const StickerSheet &other) {
    background = NULL;
    ptr = NULL;
    x_ = NULL;
    y_ = NULL;
    copy_(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {
        delete[] x_;
        delete[] y_;
        delete background;
        delete[] ptr;
        copy_(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    unsigned *newx_ = new unsigned[num];
    unsigned *newy_ = new unsigned[num];
    Image **newptr = new Image*[num];
    for (unsigned i = 0; i < num; i++) {
        newx_[i] = x_[i];
        newy_[i] = y_[i];
        newptr[i] = ptr[i];
    }
    delete[] x_;
    delete[] y_;
    delete[] ptr;
    
    if (max < num) {
        for (unsigned i = max; i < num; i++) {
            delete newptr[i];
            newptr[i] = NULL;
        }
        size_ = max;
        num = max;
        ptr = new Image*[max];
        x_ = new unsigned[max];
        y_ = new unsigned[max];
        for (unsigned i = 0; i < max; i++) {
            x_[i] = newx_[i];
            y_[i] = newy_[i];
            ptr[i] = newptr[i];
        }
    } 
    else {
        ptr = new Image*[max];
        x_ = new unsigned[max];
        y_ = new unsigned[max];
        for (unsigned i = 0; i < num; i++) {
            x_[i] = newx_[i];
            y_[i] = newy_[i];
            ptr[i] = newptr[i];
        }
        size_ = max;
    }
    delete[] newx_;
    delete[] newy_;
    delete[] newptr;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (num >= size_) 
        return -1;
    else {
        ptr[num] = new Image(sticker);
        x_[num] = x;
        y_[num] = y;
        num++;
        return num;
        delete ptr[num];
    }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < 0 || index > num - 1) 
        return 0;
    else {
        x_[index] = x;
        y_[index] = y;
        return 1;
    }
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= 0 && index <= size_ - 1) {
        delete ptr[index];
        for (unsigned i = index; i < size_ - 1; i++) {
        ptr[i] = ptr[i + 1];
        x_[i] = x_[i + 1];
        y_[i] = y_[i + 1];
        }
        ptr[size_ - 1] = NULL;
        x_[size_ - 1] = 0; 
        y_[size_ - 1] = 0;
        num--;
  }
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index < 0 || index >= num) 
        return NULL;
    else 
        return ptr[index];
}

Image StickerSheet::render() const {
    Image done(*background);
    for (unsigned i = 0; i < num; i++){
        if (ptr[i]->width() + x_[i] > done.width()) 
            done.resize(ptr[i]->width() + x_[i], done.height());
        if (ptr[i]->height() + y_[i] > done.height()) 
            done.resize(done.width(), ptr[i]->height() + y_[i]);
        for (unsigned xx = 0; xx < ptr[i]->width(); xx++) {
            for (unsigned yy = 0; yy < ptr[i]->height(); yy++) {
                HSLAPixel &pixel = done.getPixel(x_[i] + xx, y_[i] + yy);
                if (ptr[i]->getPixel(xx, yy).a != false) 
                    pixel = ptr[i]->getPixel(xx, yy);
            }
        }
    }
    return done;
}

void StickerSheet::copy_(StickerSheet const & other) {
    background = new Image(*other.background);
    size_ = other.size_;
    num = other.num;
    x_ = new unsigned[size_];
    for (unsigned i = 0; i < num; i++) {
        x_[i] = other.x_[i];
    }
    y_ = new unsigned[size_];
    for (unsigned i = 0; i < num; i++) {
        y_[i] = other.y_[i];
    }
        ptr = new Image*[size_];
        for (unsigned i = 0; i < num; i++) {
            ptr[i] = new Image();
            *ptr[i] = *(other.ptr[i]);
        }
}