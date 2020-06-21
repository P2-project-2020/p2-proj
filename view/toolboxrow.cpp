#include "toolboxrow.h"
#include <QDebug>
#include <iostream>

toolboxRow::toolboxRow(QWidget* parent):
     QWidget(parent),
     load(new QPushButton(QIcon::fromTheme("folder"),"Apri",this)),
     remove(new QPushButton(QIcon::fromTheme("process-stop"),"Elimina",this)),
     refresh(new QPushButton(QIcon::fromTheme("view-refresh"),"Refresh",this)),
     layout(new QHBoxLayout(this))
{
     layout->addStretch();
     layout->addWidget(load);
     layout->addWidget(remove);
     layout->addWidget(refresh);
     // layout->addStretch(); // Se si vuole avere i pulsanti al centro o a sinistra

     setLayout(layout);
	
     QObject::connect(load, SIGNAL(clicked()), this, SLOT(slot_load()));
     QObject::connect(remove, SIGNAL(clicked()), this, SLOT(slot_remove()));
     QObject::connect(refresh, SIGNAL(clicked()), this, SLOT(slot_refresh()));
}

void toolboxRow::initFileDialog(QFileDialog &dialog)
{
     // Chiede al sistema la path delle immaigni, se non la trova apre quella in cui è l'eseguibile
     const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
     dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());

     QStringList mimeTypeFilters;
     const QByteArrayList supportedMimeTypes = QImageReader::supportedMimeTypes();

     for (const QByteArray &mimeTypeName : supportedMimeTypes)
	  mimeTypeFilters.append(mimeTypeName);

     mimeTypeFilters.sort();
	
     dialog.setMimeTypeFilters(mimeTypeFilters);
     dialog.selectMimeTypeFilter("image/jpg");
     /* In pratica setta il file explorer in modo che apra /solo/ le immagini */
}

void toolboxRow::slot_load(){

     QString filter= "JPG (*.jpg);; PNG(*.png)";
    
     QFileDialog fileDialog;

     bool imgAccepted = false;
     QString filename = "";
     while(!imgAccepted && fileDialog.acceptMode() == QFileDialog::AcceptOpen)
     {
	  filename = fileDialog.getOpenFileName(
	       this,
	       tr("Scegli Il file da caricare"),
	       QDir::currentPath(),
	       filter,
	       &filter,
	       QFileDialog::DontUseNativeDialog);
	     
	  QImage imgReader(QString("file:///").append(filename));
	  imgAccepted = imgReader.isNull();
	  if(!imgAccepted){
	       QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
					tr("Impossibile caricare %1")
					.arg(QDir::toNativeSeparators(filename)));
	  }
     }
     if(imgAccepted)
	  emit signal_load(filename);
}

void toolboxRow::slot_remove(){
     emit signal_remove();
}

void toolboxRow::slot_refresh(){
     emit signal_refresh();
}
