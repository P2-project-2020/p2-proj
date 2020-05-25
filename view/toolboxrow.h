#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QMessageBox>
#include <QGuiApplication>
#include <QMessageBox>

class toolboxRow : public QWidget{
	Q_OBJECT;

	QPushButton* load;
	QPushButton* remove;
	QPushButton* refresh;

	QHBoxLayout* layout;
	static void initFileDialog(QFileDialog&);
	
public:
	toolboxRow(QWidget* = Q_NULLPTR);

signals:
	void signal_load(const QString&);
	void signal_remove();
	void signal_refresh();					
					
public slots:
	void slot_load();
	void slot_remove();
	void slot_refresh();
};
