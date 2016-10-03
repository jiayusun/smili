#include "milxQtImage2.h"
#include "ui_milxQtImage2.h"
#include <QtGui> 
#include <QMessageBox> 
#include <QSystemTrayIcon> 
#include <QStringList> 
#include <vtkWindowToImageFilter.h>
#include "milxQtFile.h"
#include "milxQtAboutForm.h"



milxQtImage2::milxQtImage2(QMainWindow *parent, bool contextSystem) 
{
	ui.setupUi(parent);
	maxProcessors = milx::NumberOfProcessors();
	if (maxProcessors > 1)
		maxProcessors = milx::NumberOfProcessors() / 2;
	///Setup Console
	console = new milxQtConsole;
	actionConsole = console->dockWidget()->toggleViewAction();
	actionConsole->setIcon(QIcon(":/resources/toolbar/console.png"));
	ui.toolBar->addAction(actionConsole);
	dockActions.append(actionConsole);
	QObject::connect(console->dockWidget(), SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), console, SLOT(setDockDefaultArea(Qt::DockWidgetArea)));
	parent->addDockWidget(console->dockDefaultArea(), console->dockWidget());
	console->show();
	readSettings(parent);
	///viewers
	for (int i = 0; i < 3; i++)
	{
		riw[i] = vtkSmartPointer<vtkImageViewer3>::New();
	}

	setConsole(console);
	///Program Info
	printInfo("--------------------------------------------------------");
	printInfo("sMILX Visualisation Tool for Medical Imaging");
	printInfo("Open Source Release (BSD License)");
	printInfo("(c) Copyright CSIRO, 2015.");
	printInfo("University of Queensland, Australia.");
	printInfo("Australian e-Health Research Centre, CSIRO.");
	printInfo("SMILI Version: " + QString::number(milx::Version));
	printInfo("Application Version: " + QString::number(milxQtVersion));
	printInfo("Processors to be used: " + QString::number(maxProcessors));
	printInfo("--------------------------------------------------------\n");

	///Style

	update();
}
	
milxQtImage2::~milxQtImage2()
{

}

void milxQtImage2::generateImage(const bool quietly)
{
	setConsole(console);
	if (loaded)
	{
		printDebug("Generating Image");
		int bounds[6];

		emit working(-1);
		updateData(orientAct->isChecked());

		imageData->GetExtent(bounds);

		imageInformation();


		if (bounds[5] > 1)
			volume = true;

#if VTK_MAJOR_VERSION <= 5
		riw[0]->SetInput(imageData);
#else
		for (int i = 0; i < 3; i++)
		{
			riw[i]->SetInputData(imageData);
		}
#endif
		if (!viewerSetup)
		{
			printDebug("Setting up viewer");
			for (int i = 0; i < 3; i++)
			{
				linkProgressEventOf(riw[i]);
				milxQtRenderWindow::SetRenderer(riw[i]->GetRenderer());
			}
			printDebug("Size of Image window: " + QString::number(milxQtRenderWindow::GetRenderWindow()->GetSize()[0]) + "x" + QString::number(milxQtRenderWindow::GetRenderWindow()->GetSize()[1]));
			ui.view1->SetRenderWindow(riw[0]->GetRenderWindow());
			ui.view2->SetRenderWindow(riw[1]->GetRenderWindow());
			ui.view3->SetRenderWindow(riw[2]->GetRenderWindow());
			riw[0]->SetupInteractor(ui.view1->GetRenderWindow()->GetInteractor());
			riw[1]->SetupInteractor(ui.view2->GetRenderWindow()->GetInteractor());
			riw[2]->SetupInteractor(ui.view3->GetRenderWindow()->GetInteractor());

			if (volume)
				for (int i = 0; i < 3; i++)
				{
					riw[i]->SetSlice(bounds[5] / 2); //show middle of volume
				}
			//Remove VTK events for the right mouse button for Qt context menu
			QVTKWidget::GetInteractor()->RemoveObservers(vtkCommand::RightButtonPressEvent);
			QVTKWidget::GetInteractor()->RemoveObservers(vtkCommand::RightButtonReleaseEvent);
			Connector->Connect(QVTKWidget::GetInteractor(),
				vtkCommand::EndWindowLevelEvent,
				this,
				SLOT(userEvent()));
			Connector->Connect(QVTKWidget::GetInteractor(),
				vtkCommand::MouseWheelForwardEvent,
				this,
				SLOT(userEvent()));
			Connector->Connect(QVTKWidget::GetInteractor(),
				vtkCommand::MouseWheelBackwardEvent,
				this,
				SLOT(userEvent()));
			Connector->Connect(QVTKWidget::GetInteractor(),
				vtkCommand::KeyPressEvent,
				this,
				SLOT(userEvent()));
			for (int i = 0; i < 3; i++)
			{
				riw[i]->GetRenderer()->ResetCamera();
			}

			//Human Glyph setup

			for (int i = 0; i < 3; i++){
				view[i] = new milxQtRenderWindow;  //list deletion
				view[i]->getHumanGlyph()->SetDefaultRenderer(riw[i]->GetRenderer());
				view[i]->getHumanGlyph()->SetInteractor(riw[i]->GetRenderWindow()->GetInteractor());
				if (actualNumberOfDimensions > 2)
				{
					milxQtRenderWindow::humanAct->setEnabled(true);
					view[i]->getHumanGlyph()->On();
				}
				else
				{
					milxQtRenderWindow::humanAct->setEnabled(false);
					view[i]->getHumanGlyph()->Off();
				}
			}

			//            humanGlyph->InteractiveOn();

			//Sphere annotate
			for (int i = 0; i < 3; i++)
			{
				sphereWidget->SetDefaultRenderer(riw[i]->GetRenderer());
				sphereWidget->SetInteractor(riw[i]->GetRenderWindow()->GetInteractor());
			}

			printDebug("Viewer Setup Complete");
		}
		for (int i = 0; i < 3; i++)
		{
			riw[i]->GetInteractorStyle()->InvokeEvent(vtkCommand::ResetWindowLevelEvent); //Reset window level as if pressing 'r'
			riw[i]->GetRenderer()->ResetCamera(); //Reset window view as if pressing 'Shift+r'
			riw[i]->UpdateCursor();
			riw[i]->Render();
		}

		///Check for magnification
		if (!viewerSetup)
		{
			setupEvents();
			viewerSetup = true;
		}


		if (milxQtRenderWindow::useDefaultView)
			setView(milxQtRenderWindow::defaultView); //Default view

		emit milxQtRenderWindow::modified(GetImageActor());
		if (!quietly)
			emit modified(this);
		emit done(-1);
	}
	printDebug("Completed Generating Image");

	for (int i = 0; i < 3; i++)
	{
		viewXY[i] = new QAction(this);
		viewXY[i]->setText(QApplication::translate("Render", "Axial (xy-plane)", 0, QApplication::UnicodeUTF8));
		viewXY[i]->setShortcut(tr("Alt+a"));
		viewXY[i]->setCheckable(true);
		viewZX[i] = new QAction(this);
		viewZX[i]->setText(QApplication::translate("Render", "Coronal (zx-plane)", 0, QApplication::UnicodeUTF8));
		viewZX[i]->setShortcut(tr("Alt+c"));
		viewZX[i]->setCheckable(true);
		viewZY[i] = new QAction(this);
		viewZY[i]->setText(QApplication::translate("Render", "Sagittal (zy-plane)", 0, QApplication::UnicodeUTF8));
		viewZY[i]->setShortcut(tr("Alt+s"));
		viewZY[i]->setCheckable(true);
		viewGroup[i] = new QActionGroup(this);
		viewGroup[i]->addAction(viewXY[i]);
		viewGroup[i]->addAction(viewZX[i]);
		viewGroup[i]->addAction(viewZY[i]);
		viewMenu[i] = new QMenu(this);
		viewMenu[i]->addAction(viewXY[i]);
		viewMenu[i]->addAction(viewZX[i]);
		viewMenu[i]->addAction(viewZY[i]);

	}
	ui.viewButton1->setMenu(viewMenu[0]);
	ui.viewButton2->setMenu(viewMenu[1]);
	ui.viewButton3->setMenu(viewMenu[2]);

	QSignalMapper* mapperXY = new QSignalMapper;
	for (int i = 0; i < 3; i++)
	{
		
		mapperXY->setMapping(viewXY[i], i);
		QObject::connect(viewXY[i], SIGNAL(triggered()), mapperXY, SLOT(map()));
	}
	QObject::connect(mapperXY, SIGNAL(mapped(int)), this, SLOT(viewToXYPlane(int)));

	QSignalMapper* mapperZX = new QSignalMapper;
	for (int i = 0; i < 3; i++)
	{
		mapperZX->setMapping(viewZX[i], i);
		QObject::connect(viewZX[i], SIGNAL(triggered()), mapperZX, SLOT(map()));
	}
	QObject::connect(mapperZX, SIGNAL(mapped(int)), this, SLOT(viewToZXPlane(int)));

	QSignalMapper* mapperZY = new QSignalMapper;
	for (int i = 0; i < 3; i++)
	{
		mapperZY->setMapping(viewZY[i], i);
		QObject::connect(viewZY[i], SIGNAL(triggered()), mapperZY, SLOT(map()));
	}
	QObject::connect(mapperZY, SIGNAL(mapped(int)), this, SLOT(viewToZYPlane(int)));

	if (index[0] == 0)
	{
		viewToXYPlane(0);
		viewXY[0]->setChecked(true);
	}
	else if (index[0] == 1)
	{
		viewToZXPlane(0);
		viewZX[0]->setChecked(true);
	}
	else if (index[0] == 2)
	{
		viewToZYPlane(0);
		viewZY[0]->setChecked(true);
	}
	if (index[1] == 0)
	{
		viewToXYPlane(1);
		viewXY[1]->setChecked(true);
	}
	else if (index[1] == 1)
	{
		viewToZXPlane(1);
		viewZX[1]->setChecked(true);
	}
	else if (index[1] == 2)
	{
		viewToZYPlane(1);
		viewZY[1]->setChecked(true);
	}
	if (index[2] == 0)
	{
		viewToXYPlane(2);
		viewXY[2]->setChecked(true);
	}
	else if (index[2] == 1)
	{
		viewToZXPlane(2);
		viewZX[2]->setChecked(true);
	}
	else if (index[2] == 2)
	{
		viewToZYPlane(2);
		viewZY[2]->setChecked(true);
	}

	ui.actionIntensity->setIcon(QIcon(":/resources/toolbar/intensity.png"));
	QObject::connect(ui.actionIntensity, SIGNAL(triggered()), this, SLOT(updateWindowsWithAutoLevel()));

	ui.actionRefresh->setIcon(QIcon(":/resources/toolbar/refresh.png"));
	QObject::connect(ui.actionRefresh, SIGNAL(triggered()), this, SLOT(updateWindowsWithRefresh()));

	ui.actionCrosshair->setIcon(QIcon(":/resources/toolbar/crosshairs_2D.png"));
	QObject::connect(ui.actionCrosshair, SIGNAL(triggered()), this, SLOT(updateWindowsWithCursors()));

	ui.actionSaveScreen4->setIcon(QIcon(":/resources/toolbar/screenshot.png")); 
	QObject::connect(ui.actionSaveScreen4, SIGNAL(triggered()), this, SLOT(saveFullScreen()));

	ui.actionControls->setIcon(QIcon(":/resources/toolbar/controls.png"));
	QObject::connect(ui.actionControls, SIGNAL(triggered()), this, SLOT(controls()));

	ui.actionAbout->setIcon(QIcon(":/resources/smilx_icon.png"));
	QObject::connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));

	QSignalMapper* screen = new QSignalMapper;
	screen->setMapping(ui.saveScreen_1, 0);
	screen->setMapping(ui.saveScreen_2, 1);
	screen->setMapping(ui.saveScreen_3, 2);
	QObject::connect(ui.saveScreen_1, SIGNAL(clicked()), screen, SLOT(map()));
	QObject::connect(ui.saveScreen_2, SIGNAL(clicked()), screen, SLOT(map()));
	QObject::connect(ui.saveScreen_3, SIGNAL(clicked()), screen, SLOT(map()));
	ui.saveScreen_1->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	ui.saveScreen_2->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	ui.saveScreen_3->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	QObject::connect(screen, SIGNAL(mapped(int)), this, SLOT(saveScreen(int)));

	QPointer<milxQtRenderWindow> slicesView = new milxQtRenderWindow;  //list deletion
	slicesView->setConsole(console);
	for (int i = 0; i < 3; i++)
	{
		slicesView->addImageActor(riw[i]->GetImageActor(), getTransformMatrix());
	}
	//slicesView->addActor(newImage->GetCursorActor(), newImage->getTransformMatrix());
	slicesView->generateRender();
	ui.view4->SetRenderWindow(slicesView->GetRenderWindow());
}

void milxQtImage2::updateWindowsWithAutoLevel()
{
	autoLevel();
	//updateData();
	for (int i = 0; i < 3; i++)
	{
		riw[i]->SetColorWindow(viewer->GetColorWindow());
		riw[i]->SetColorLevel(viewer->GetColorLevel());
		riw[i]->Render();
	}
	//generateImage();
}


void milxQtImage2::updateWindowsWithRefresh()
{


	for (int i = 0; i < 3; i++)
	{
		riw[i]->UpdateCursor();
		riw[i]->GetInteractorStyle()->InvokeEvent(vtkCommand::ResetWindowLevelEvent); //Reset window level as if pressing 'r'
		riw[i]->Render();
		milxQtRenderWindow::refresh();
	}
}

void milxQtImage2::updateWindowsWithCursors()
{

	for (int i = 0; i < 3; i++)
	{
		riw[i]->EnableCursor();
		cursorAct->setChecked(true);
	}
}

void milxQtImage2::saveScreen(int i, QString filename)
{
	QFileDialog *fileSaver = new QFileDialog(this);

	QSettings settings("Shekhar Chandra", "milxQt");
	QString path = settings.value("recentPath").toString();
	if (filename.isEmpty())
	{
		filename = fileSaver->getSaveFileName(this,
			tr("Select File Name to Save"),
			path,
			tr(saveExtsForScreens.c_str()));
	}

	QPointer<milxQtFile> writer = new milxQtFile; //Smart deletion
	vtkSmartPointer<vtkWindowToImageFilter> windowToImage = vtkSmartPointer<vtkWindowToImageFilter>::New();
	riw[i]->GetRenderWindow()->Render();
	windowToImage->SetInput(riw[i]->GetRenderWindow());
	windowToImage->SetMagnification(magnifyFactor);
	//        windowToImage->SetInputBufferTypeToRGBA(); //also record the alpha (transparency) channel
	windowToImage->ReadFrontBufferOff();
	windowToImage->Update();
	//Save screenshot
	int extent[6];
	windowToImage->GetOutput()->GetExtent(extent);
	printDebug("Screenshot Size: " + QString::number(extent[1] - extent[0]) + ", " + QString::number(extent[3] - extent[2]) + ", " + QString::number(extent[5] - extent[4]));
	bool success = writer->saveImage(filename, windowToImage->GetOutput());

	//        windowVTK->GetRenderWindow()->OffScreenRenderingOff();
	riw[i]->GetRenderWindow()->Render(); //Restore rendering

	if (!success)
	{
		printError("Unable to save screenshot. Ignoring.");
		return;
	}

	printInfo("Write Complete.");
}


void milxQtImage2::saveFullScreen(QString filename)
{
	QFileDialog *fileSaver = new QFileDialog(this);

	QSettings settings("Shekhar Chandra", "milxQt");
	QString path = settings.value("recentPath").toString();
	if (filename.isEmpty())
	{
		filename = fileSaver->getSaveFileName(this,
			tr("Select File Name to Save"),
			path,
			tr(saveExtsForScreens.c_str()));
	}
	QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(), pos().x(), pos().y(), frameGeometry().width(), frameGeometry().height());
	pixmap.save( filename , "png");
}

void milxQtImage2::controls()
{
	printDebug("Showing controls available...");
	QPixmap pixmap(":resources/controls_splash.png");
	QSplashScreen *controlsSplash = new QSplashScreen(this);
	controlsSplash->setPixmap(pixmap);
	controlsSplash->setMask(pixmap.mask());
	controlsSplash->show();

	qApp->processEvents();
}

void milxQtImage2::about()
{
	milxQtAboutForm aboutForm(this);

	aboutForm.exec();
}

void milxQtImage2::viewToXYPlane(int i)
{
	if (viewerSetup)
	{
		riw[i]->SetSliceOrientationToXY();
		currentView[i] = AXIAL;
	}
}

void milxQtImage2::viewToZXPlane(int i)
{
	if (viewerSetup)
	{
		riw[i]->SetSliceOrientationToXZ();
		currentView[i] = CORONAL;
	}

}

void milxQtImage2::viewToZYPlane(int i)
{
	if (viewerSetup)
	{
		riw[i]->SetSliceOrientationToYZ();
		currentView[i] = SAGITTAL;
	}
}


void milxQtImage2::writeSettings(QWidget *parent)
{
	QSettings settings("Shekhar Chandra", "milxQt");
	settings.beginGroup("milxQtImage2");
	settings.setValue("geometry", saveGeometry());
	QMainWindow *mainWindow = qobject_cast<QMainWindow *>(parent);
	settings.setValue("windowState", mainWindow->saveState());
	for (int i = 0; i < 3; i++)
	{
		if (currentView[i] == AXIAL)
		{
			settings.setValue("defaultView" + QString::number(i), 0);
		}
		else if (currentView[i] == CORONAL)
		{
			settings.setValue("defaultView" + QString::number(i), 1);
		}
		else if (currentView[i] == SAGITTAL)
		{
			settings.setValue("defaultView" + QString::number(i), 2);
		}
	}

	settings.endGroup();
	printDebug("saveSetting");
}

void milxQtImage2::readSettings(QMainWindow *parent)
{
	QSettings settings("Shekhar Chandra", "milxQt");

	settings.beginGroup("milxQtImage2");
	restoreGeometry(settings.value("geometry").toByteArray());
	parent->restoreState(settings.value("windowState").toByteArray());
	for (int i = 0; i < 3; i++)
	{
		defaultViewMode[i] = i;
	}

	for (int i = 0; i < 3; i++)
	{
		index[i] = settings.value("defaultView" + QString::number(i), defaultViewMode[i]).toInt();
	}

	///Handle saving dock positions/areas etc.
	settings.endGroup();
	parent->restoreDockWidget(console->dockWidget());
	printDebug("ReadSettings");
	//use value in view to set view in viewer
}

