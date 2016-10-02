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
	void saveScreen1(QString filename = "");
	void saveScreen2(QString filename = "");
	void saveScreen3(QString filename = "");
	void saveScreen(QString filename = "");
	void controls();
	void about();
	void view1ToXYPlane();
	void view1ToZXPlane();
	void view1ToZYPlane();
	void view2ToXYPlane();
	void view2ToZXPlane();
	void view2ToZYPlane();
	void view3ToXYPlane();
	void view3ToZXPlane();
	void view3ToZYPlane();
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
	QMenu* view1Menu; //!< Context Menu
	QActionGroup* view1Group; //!< Grouping for check boxes
	QAction* view1XY; //!< Change view to xy-plane (Axial)
	QAction* view1ZY; //!< Change view to zy-plane (Coronal)
	QAction* view1ZX; //!< Change view to zx-plane (Sagittal)
	QMenu* view2Menu; //!< Context Menu
	QActionGroup* view2Group; //!< Grouping for check boxes
	QAction* view2XY; //!< Change view to xy-plane (Axial)
	QAction* view2ZY; //!< Change view to zy-plane (Coronal)
	QAction* view2ZX; //!< Change view to zx-plane (Sagittal)
	QMenu* view3Menu; //!< Context Menu
	QActionGroup* view3Group; //!< Grouping for check boxes
	QAction* view3XY; //!< Change view to xy-plane (Axial)
	QAction* view3ZY; //!< Change view to zy-plane (Coronal)
	QAction* view3ZX; //!< Change view to zx-plane (Sagittal)
	
	
};
#endif