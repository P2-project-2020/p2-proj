#include "imageView.h"
#include <iostream>

ImageView::ImageView(QWidget* parent):
	QLabel(parent), path(nullptr), width(300), height(300){}

ImageView::ImageView(const QString& _path, QWidget* parent):
	QLabel(parent), path(new QString(_path)), width(300), height(300){}

void ImageView::mousePressEvent(QMouseEvent* event){
	/* evento di mousePress overridato da quello di QLabel così che 
	   apra l'immagine col visualizzatore immagini del proprio sistema */
	if(path)
		QDesktopServices::openUrl(QUrl(*path, QUrl::TolerantMode));
}

bool ImageView::setPixmap(const QString& _path){
	QPixmap img(_path);
	bool to_return = !img.isNull();
	if(to_return){
		img = img.scaled(width,height,Qt::KeepAspectRatioByExpanding);
		int hStart = img.height() > height ? (img.height()-height)/2 : 0;
		int wStart = img.width() > width ? (img.width()-width)/2 : 0;
		img = img.copy(wStart,hStart,width,height);
	}
	/* Sto ambaradan per scalare l'immagine a una dimensione fissa. 
	   così che si comporti come una sorta di minatura*/
	QLabel::setPixmap(img);
	delete path;
	path = new QString(_path);
	return to_return;
}

void ImageView::setSize(int w, int h){
	width = w>0 ? w : 0;
	height = h>0 ? h : 0;
}
