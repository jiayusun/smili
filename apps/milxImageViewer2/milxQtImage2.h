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

	//Print Members
	/*!
	\fn milxQtMain::printError(QString msg)
	\brief Error message wrapper for console.
	*/
	inline void printError(QString msg)
	{
		console->printError(msg);
	}
	//    {   cerr << msg.toStdString() << endl;   }
	/*!
	\fn milxQtMain::printWarning(QString msg)
	\brief Warning message wrapper for console.
	*/
	inline void printWarning(QString msg)
	{
		console->printWarning(msg);
	}
	//    {   cerr << msg.toStdString() << endl;   }
	/*!
	\fn milxQtMain::printDebug(QString msg)
	\brief Debug message wrapper for console.
	*/
	inline void printDebug(QString msg)
	{
		console->printDebug(msg);
	}
	//    {   cerr << msg.toStdString() << endl;   }
	/*!
	\fn milxQtMain::printInfo(QString msg)
	\brief Info message wrapper for console.
	*/
	inline void printInfo(QString msg)
	{
		console->printInfo(msg);
	}

protected:
	Ui_milxQtImage2 ui;
	vtkSmartPointer<vtkImageViewer3> riw[3];
	int maxProcessors; //!< Max processors to use
	int magnifyFactor = 2;
	QAction* actionConsole;
	QList< QAction* > dockActions; //!< List of dock actions of dock widgets loaded succesfully.
	QPointer<milxQtConsole> console; //!< console docked window
};
#endif