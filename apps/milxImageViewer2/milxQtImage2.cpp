#include "milxQtImage2.h"
#include "ui_milxQtImage2.h"
#include <QtGui> 
#include <QMessageBox> 
#include <QSystemTrayIcon> 
#include <QStringList> 
#include <vtkWindowToImageFilter.h>
#include "milxQtFile.h"
#include <QPixmap>



milxQtImage2::milxQtImage2(QMainWindow *parent, bool contextSystem)
{
	ui.setupUi(parent);
	//ui.view1 = qobject_cast<QVTKWidget*>(this);
	//ui.view2 = qobject_cast<QVTKWidget*>(this);
	//ui.view3 = qobject_cast<QVTKWidget*>(this);
	//ui.view4 = qobject_cast<QVTKWidget*>(this);

	for (int i = 0; i < 3; i++)
	{
		riw[i] = vtkSmartPointer<vtkImageViewer3>::New();
	}
}
	
milxQtImage2::~milxQtImage2()
{

}

void milxQtImage2::generateImage(const bool quietly)
{

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
	setupHumanGlyph(transformMatrix);
	for (int i = 0; i < 3; i++)
	{
		humanGlyph->SetDefaultRenderer(riw[i]->GetRenderer());
		humanGlyph->SetInteractor(riw[i]->GetRenderWindow()->GetInteractor());
	}
	if (actualNumberOfDimensions > 2)
	{
		milxQtRenderWindow::humanAct->setEnabled(true);
		humanGlyph->On();
	}
	else
	{
		milxQtRenderWindow::humanAct->setEnabled(false);
		humanGlyph->Off();
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
	riw[0]->SetSliceOrientationToXY();
	riw[1]->SetSliceOrientationToXZ();
	riw[2]->SetSliceOrientationToYZ();
	
	ui.actionIntensity->setIcon(QIcon(":/resources/toolbar/intensity.png"));
	QObject::connect(ui.actionIntensity, SIGNAL(triggered()), this, SLOT(updateWindowsWithAutoLevel()));

	ui.actionRefresh->setIcon(QIcon(":/resources/toolbar/refresh.png"));
	QObject::connect(ui.actionRefresh, SIGNAL(triggered()), this, SLOT(updateWindowsWithRefresh()));

	ui.actionCrosshair->setIcon(QIcon(":/resources/toolbar/crosshairs_2D.png"));
	QObject::connect(ui.actionCrosshair, SIGNAL(triggered()), this, SLOT(updateWindowsWithCursors()));
	
	ui.actionSaveScreen4->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	QObject::connect(ui.actionSaveScreen4, SIGNAL(triggered()), this, SLOT(saveScreen()));

	ui.saveScreen_1->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	QObject::connect(ui.saveScreen_1, SIGNAL(clicked()), this, SLOT(saveScreen1()));

	ui.saveScreen_2->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	QObject::connect(ui.saveScreen_2, SIGNAL(clicked()), this, SLOT(saveScreen2()));

	ui.saveScreen_3->setIcon(QIcon(":/resources/toolbar/screenshot.png"));
	QObject::connect(ui.saveScreen_3, SIGNAL(clicked()), this, SLOT(saveScreen3()));


	QPointer<milxQtRenderWindow> slicesView = new milxQtRenderWindow;  //list deletion
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