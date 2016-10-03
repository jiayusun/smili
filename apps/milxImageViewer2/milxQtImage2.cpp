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
	timestamping = true;
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
	//riw[0]->SetInputData(GetOutput());
	//riw[1]->SetInputData(GetOutput());
	//ui.view1->SetRenderWindow(GetRenderWindow());
	//SetupInteractor(ui.view1->GetRenderWindow()->GetInteractor());
	QMenu *menu = new QMenu();
	createMenu(menu);
	QToolButton* toolButton = new QToolButton();
	toolButton->setIcon(QIcon(":/resources/toolbar/help.png"));
	toolButton->setMenu(menu);
	toolButton->setPopupMode(QToolButton::InstantPopup);
	ui.toolBar->addWidget(toolButton);

	view1XY = new QAction(this);
	view1XY->setText(QApplication::translate("Render", "Axial (xy-plane)", 0, QApplication::UnicodeUTF8));
	view1XY->setShortcut(tr("Alt+a"));
	view1XY->setCheckable(true);
	view1ZX = new QAction(this);
	view1ZX->setText(QApplication::translate("Render", "Coronal (zx-plane)", 0, QApplication::UnicodeUTF8));
	view1ZX->setShortcut(tr("Alt+c"));
	view1ZX->setCheckable(true);
	view1ZY = new QAction(this);
	view1ZY->setText(QApplication::translate("Render", "Sagittal (zy-plane)", 0, QApplication::UnicodeUTF8));
	view1ZY->setShortcut(tr("Alt+s"));
	view1ZY->setCheckable(true);
	view1Group = new QActionGroup(this);
	view1Group->addAction(view1XY);
	view1Group->addAction(view1ZX);
	view1Group->addAction(view1ZY);

	view1Menu = new QMenu(this);
	view1Menu->addAction(view1XY);
	view1Menu->addAction(view1ZX);
	view1Menu->addAction(view1ZY);
	ui.viewButton1->setMenu(view1Menu);

	connect(view1XY, SIGNAL(triggered()), this, SLOT(view1ToXYPlane()));
	connect(view1ZX, SIGNAL(triggered()), this, SLOT(view1ToZXPlane()));
	connect(view1ZY, SIGNAL(triggered()), this, SLOT(view1ToZYPlane()));

	view2XY = new QAction(this);
	view2XY->setText(QApplication::translate("Render", "Axial (xy-plane)", 0, QApplication::UnicodeUTF8));
	view2XY->setShortcut(tr("Alt+a"));
	view2XY->setCheckable(true);
	view2ZX = new QAction(this);
	view2ZX->setText(QApplication::translate("Render", "Coronal (zx-plane)", 0, QApplication::UnicodeUTF8));
	view2ZX->setShortcut(tr("Alt+c"));
	view2ZX->setCheckable(true);
	view2ZY = new QAction(this);
	view2ZY->setText(QApplication::translate("Render", "Sagittal (zy-plane)", 0, QApplication::UnicodeUTF8));
	view2ZY->setShortcut(tr("Alt+s"));
	view2ZY->setCheckable(true);
	view2Group = new QActionGroup(this);
	view2Group->addAction(view2XY);
	view2Group->addAction(view2ZX);
	view2Group->addAction(view2ZY);

	view2Menu = new QMenu(this);
	view2Menu->addAction(view2XY);
	view2Menu->addAction(view2ZX);
	view2Menu->addAction(view2ZY);
	ui.viewButton2->setMenu(view2Menu);

	connect(view2XY, SIGNAL(triggered()), this, SLOT(view2ToXYPlane()));
	connect(view2ZX, SIGNAL(triggered()), this, SLOT(view2ToZXPlane()));
	connect(view2ZY, SIGNAL(triggered()), this, SLOT(view2ToZYPlane()));

	view3XY = new QAction(this);
	view3XY->setText(QApplication::translate("Render", "Axial (xy-plane)", 0, QApplication::UnicodeUTF8));
	view3XY->setShortcut(tr("Alt+a"));
	view3XY->setCheckable(true);
	view3ZX = new QAction(this);
	view3ZX->setText(QApplication::translate("Render", "Coronal (zx-plane)", 0, QApplication::UnicodeUTF8));
	view3ZX->setShortcut(tr("Alt+c"));
	view3ZX->setCheckable(true);
	view3ZY = new QAction(this);
	view3ZY->setText(QApplication::translate("Render", "Sagittal (zy-plane)", 0, QApplication::UnicodeUTF8));
	view3ZY->setShortcut(tr("Alt+s"));
	view3ZY->setCheckable(true);
	view3Group = new QActionGroup(this);
	view3Group->addAction(view3XY);
	view3Group->addAction(view3ZX);
	view3Group->addAction(view3ZY);

	view3Menu = new QMenu(this);
	view3Menu->addAction(view3XY);
	view3Menu->addAction(view3ZX);
	view3Menu->addAction(view3ZY);
	ui.viewButton3->setMenu(view3Menu);

	connect(view3XY, SIGNAL(triggered()), this, SLOT(view3ToXYPlane()));
	connect(view3ZX, SIGNAL(triggered()), this, SLOT(view3ToZXPlane()));
	connect(view3ZY, SIGNAL(triggered()), this, SLOT(view3ToZYPlane()));

	if (index[0] == 0)
	{
		view1ToXYPlane();
		view1XY->setChecked(true);
	}
	else if (index[0] == 1)
	{
		view1ToZXPlane();
		view1ZX->setChecked(true);
	}
	else if (index[0] == 2)
	{
		view1ToZYPlane();
		view1ZY->setChecked(true);
	}
	if (index[1] == 0)
	{
		view2ToXYPlane();
		view2XY->setChecked(true);
	}
	else if (index[1] == 1)
	{
		view2ToZXPlane();
		view2ZX->setChecked(true);
	}
	else if (index[1] == 2)
	{
		view2ToZYPlane();
		view2ZX->setChecked(true);
	}
	if (index[2] == 0)
	{
		view3ToXYPlane();
		view3XY->setChecked(true);
	}
	else if (index[2] == 1)
	{
		view3ToZXPlane();
		view3ZX->setChecked(true);
	}
	else if (index[2] == 2)
	{
		view3ToZYPlane();
		view3ZY->setChecked(true);
	}

	ui.actionIntensity->setIcon(QIcon(":/resources/toolbar/intensity.png"));
	QObject::connect(ui.actionIntensity, SIGNAL(triggered()), this, SLOT(updateWindowsWithAutoLevel()));

	ui.actionRefresh->setIcon(QIcon(":/resources/toolbar/refresh.png"));
	QObject::connect(ui.actionRefresh, SIGNAL(triggered()), this, SLOT(updateWindowsWithRefresh()));

	ui.actionCrosshair->setIcon(QIcon(":/resources/toolbar/crosshairs_2D.png"));
	QObject::connect(ui.actionCrosshair, SIGNAL(triggered()), this, SLOT(updateWindowsWithCursors()));
	
	ui.actionSaveScreen4->setIcon(QIcon(":/resources/toolbar/screenshot.png")); 
	QObject::connect(ui.actionSaveScreen4, SIGNAL(triggered()), this, SLOT(saveScreen()));

	ui.actionControls->setIcon(QIcon(":/resources/toolbar/controls.png"));
	QObject::connect(ui.actionControls, SIGNAL(triggered()), this, SLOT(controls()));

	ui.actionAbout->setIcon(QIcon(":/resources/smilx_icon.png"));
	QObject::connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));

	ui.saveScreen_1->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	QObject::connect(ui.saveScreen_1, SIGNAL(clicked()), this, SLOT(saveScreen1()));

	ui.saveScreen_2->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	QObject::connect(ui.saveScreen_2, SIGNAL(clicked()), this, SLOT(saveScreen2()));

	ui.saveScreen_3->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	QObject::connect(ui.saveScreen_3, SIGNAL(clicked()), this, SLOT(saveScreen3()));

	QPointer<milxQtRenderWindow> slicesView = new milxQtRenderWindow;  //list deletion
	slicesView->setConsole(console);
	slicesView->addImageActor(riw[0]->GetImageActor(), getTransformMatrix());
	slicesView->addImageActor(riw[1]->GetImageActor(), getTransformMatrix());
	slicesView->addImageActor(riw[2]->GetImageActor(), getTransformMatrix());
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



void milxQtImage2::saveScreen1(QString filename)
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
	riw[0]->GetRenderWindow()->Render();
	windowToImage->SetInput(riw[0]->GetRenderWindow());
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
	riw[0]->GetRenderWindow()->Render(); //Restore rendering

	if (!success)
	{
		printError("Unable to save screenshot. Ignoring.");
		return;
	}

	printInfo("Write Complete.");
}


void milxQtImage2::saveScreen2(QString filename)
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
	riw[1]->GetRenderWindow()->Render();
	windowToImage->SetInput(riw[1]->GetRenderWindow());
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
	riw[1]->GetRenderWindow()->Render(); //Restore rendering

	if (!success)
	{
		printError("Unable to save screenshot. Ignoring.");
		return;
	}

	printInfo("Write Complete.");
}


void milxQtImage2::saveScreen3(QString filename)
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
	riw[2]->GetRenderWindow()->Render();
	windowToImage->SetInput(riw[2]->GetRenderWindow());
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
	riw[2]->GetRenderWindow()->Render(); //Restore rendering

	if (!success)
	{
		printError("Unable to save screenshot. Ignoring.");
		return;
	}

	printInfo("Write Complete.");
}


void milxQtImage2::saveScreen(QString filename)
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

void milxQtImage2::view1ToXYPlane()
{
	if (viewerSetup)
	{
		riw[0]->SetSliceOrientationToXY();
		currentView[0] = AXIAL;
	}
}

void milxQtImage2::view1ToZXPlane()
{
	if (viewerSetup)
	{
		riw[0]->SetSliceOrientationToXZ();
		currentView[0] = CORONAL;
	}

}

void milxQtImage2::view1ToZYPlane()
{
	if (viewerSetup)
	{
		riw[0]->SetSliceOrientationToYZ();
		currentView[0] = SAGITTAL;
	}
}

void milxQtImage2::view2ToXYPlane()
{
	if (viewerSetup)
	{
		riw[1]->SetSliceOrientationToXY();
		currentView[1] = AXIAL;
	}
}

void milxQtImage2::view2ToZXPlane()
{
	if (viewerSetup)
	{
		riw[1]->SetSliceOrientationToXZ();
		currentView[1] = CORONAL;
	}
}

void milxQtImage2::view2ToZYPlane()
{
	if (viewerSetup)
	{
		riw[1]->SetSliceOrientationToYZ();
		currentView[1] = SAGITTAL;
	}
}

void milxQtImage2::view3ToXYPlane()
{
	if (viewerSetup)
	{
		riw[2]->SetSliceOrientationToXY();
		currentView[2] = AXIAL;
	}
}

void milxQtImage2::view3ToZXPlane()
{
	if (viewerSetup)
	{
		riw[2]->SetSliceOrientationToXZ();
		currentView[2] = CORONAL;
	}
}

void milxQtImage2::view3ToZYPlane()
{
	if (viewerSetup)
	{
		riw[2]->SetSliceOrientationToYZ();
		currentView[2] = SAGITTAL;
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

	settings.setValue("timestamping", timestamping);
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

	timestamping = settings.value("timestamping", timestamping).toBool();
	///Handle saving dock positions/areas etc.
	console->setTimestamps(timestamping);
	settings.endGroup();
	parent->restoreDockWidget(console->dockWidget());
	printDebug("ReadSettings");
	//use value in view to set view in viewer
}

