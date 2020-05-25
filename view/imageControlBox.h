#pragma once

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <iostream>
#include "toolboxrow.h"
#include "imageView.h"

class ImageControlBox : public QWidget{
	Q_OBJECT;

	ImageView* image;
	toolboxRow* toolbox;
	QVBoxLayout* layout;
	bool imageIsSet;
	
public:
	ImageControlBox(const QString& = "", QWidget* = Q_NULLPTR);
	~ImageControlBox();
	bool setImage(const QString&);
	bool setPreviewSize(int,int);

signals:
	void signal_removeImage();
	void signal_setImage(const QString&);
								 
public slots:
	void slot_setImage(const QString&);
	void slot_removeImage();
};
