#ifndef MILXQTIMAGE2_H
#define MILXQTIMAGE2_H
#include <QApplication>
#include <QMainWindow>
#include "milxQtImage.h"
#include "milxQtMain.h"
#include "ui_milxQtImage2.h" 
#include <QPointer>
#include <QDesktopWidget>

class MILXQT_EXPORT milxQtImage2 : public milxQtImage
{
	Q_OBJECT

public:
	milxQtImage2(QMainWindow *parent = 0, bool contextSystem = true);
	~milxQtImage2();
	void generateImage(const bool quietly = false);
	void readSettings(QMainWindow *parent = 0);
public slots:
	void updateWindowsWithAutoLevel();
	void updateWindowsWithRefresh();
	void updateWindowsWithCursors();
	void saveScreen(int i, QString filename = "");
	void saveFullScreen(QString filename = "");
	void controls();
	void about();
	void viewToXYPlane(int i);
	void viewToZXPlane(int i);
	void viewToZYPlane(int i);
	void writeSettings(QWidget *parent = 0);
protected:
	Ui_milxQtImage2 ui;
	vtkSmartPointer<vtkImageViewer3> riw[3];
	int currentView[3];
	int index[3];
	int defaultViewMode[3];
	int maxProcessors; //!< Max processors to use
	int magnifyFactor = 2;
	int currentView1;
	int currentView2;
	int currentView3;
	bool timestamping; //!< Prefer showing timestamp?
	QAction* actionConsole;
	QList< QAction* > dockActions; //!< List of dock actions of dock widgets loaded succesfully.
	QPointer<milxQtConsole> console; //!< console docked window
	QPointer<milxQtRenderWindow> view[3];  //list deletion
	QMenu* viewMenu[3]; //!< Context Menu
	QActionGroup* viewGroup[3]; //!< Grouping for check boxes
	QAction* viewXY[3]; //!< Change view to xy-plane (Axial)
	QAction* viewZY[3]; //!< Change view to zy-plane (Coronal)
	QAction* viewZX[3]; //!< Change view to zx-plane (Sagittal)
	
};
#endif