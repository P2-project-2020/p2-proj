#pragma once

#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <iostream>
#include "imageWindow.h"

/* Non definisco neanche il distruttore perchè quello standard va mene, è solo un wrapper attorno a QLabel
   per avere il segnale di clicked su un'immagine*/

class ImageView : public QLabel{
	Q_OBJECT

	QString* path;

	int width, height;
public:
	ImageView(QWidget* = Q_NULLPTR);
	ImageView(const QString&, QWidget* = Q_NULLPTR);
	bool setPixmap(const QString&);
	void setSize(int,int);							  

protected:	
	void mousePressEvent(QMouseEvent*);

};
