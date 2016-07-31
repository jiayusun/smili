#ifndef MILXQTIMAGE2_H
#define MILXQTIMAGE2_H
#include <QWidget> 
#include <QApplication>
#include <QMainWindow>
#include "milxQtImage.h"
#include "milxQtMain.h"
#include "ui_milxQtImage2.h" 
#include <QPointer>

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

protected:
	Ui_milxQtImage2 ui;
	vtkSmartPointer<vtkImageViewer3> riw[3];
};
#endif