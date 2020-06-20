#include "imageControlBox.h"
#include <QDebug>
#include <iostream>

ImageControlBox::ImageControlBox(const QString& path, QWidget* parent):
	QWidget(parent),
	image(new ImageView(this)),
	toolbox(new toolboxRow(this)),
	layout(new QVBoxLayout(this)),
	imageIsSet(false)
{
	if(path != "")
		setImage(path);
	layout->addWidget(image);
	layout->addWidget(toolbox);

	setLayout(layout);

	QObject::connect(toolbox, SIGNAL(signal_load(const QString&)), this, SLOT(slot_setImage(const QString&)));
	QObject::connect(toolbox, SIGNAL(signal_remove()), this, SLOT(slot_removeImage()));
}
 
ImageControlBox::~ImageControlBox(){
	delete image;
	delete toolbox;
	delete layout;
}

bool ImageControlBox::setImage(const QString& file){
	// Se non c'è un'immagine corrispondente non la setta e torna falso
	// Se l'immagine è null rimuove quella di prima e torna true B)
	
	imageIsSet = image->setPixmap(file);
	return imageIsSet;
}

void ImageControlBox::slot_setImage(const QString& newImage){
	/* Dovrebbe ricevere una immagine selezionata dal toolboxRow da impostare come immagine dell'oggetto e
	   mostrare. */
	setImage(newImage);
	emit signal_setImage(newImage);
}

void ImageControlBox::slot_removeImage(){
	if(imageIsSet){
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this,
									  "Rimozione immagine",
									  "Rimuovere l'immagine dello strumento?",
									  QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes) {
			setImage("");
			emit signal_removeImage();
		}
	}
}

bool ImageControlBox::setPreviewSize(int width,int height) {
     image->setSize(width, height);
     return true;
}
