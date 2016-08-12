#ifndef MILXQTIMAGE2_H
#define MILXQTIMAGE2_H
#include <QWidget> 
#include <QApplication>
#include <QMainWindow>
#include "milxQtImage.h"
#include "milxQtMain.h"
#include "ui_milxQtImage2.h" 
#include <QPointer>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>

class MILXQT_EXPORT milxQtImage2 : public milxQtImage
{
	Q_OBJECT

public:
	milxQtImage2(QMainWindow *parent = 0, bool contextSystem = true);
	~milxQtImage2();
	void generateImage(const bool quietly = false);

public slots:
	void updateWindowsWithAutoLevel();
	void updateWindowsWithRefresh();
	void updateWindowsWithCursors();
	void saveScreen1(QString filename = "");
	void saveScreen2(QString filename = "");
	void saveScreen3(QString filename = "");
	void saveScreen(QString filename = "");


protected:
	Ui_milxQtImage2 ui;
	vtkSmartPointer<vtkImageViewer3> riw[3];
	int magnifyFactor = 2;
};
#endif