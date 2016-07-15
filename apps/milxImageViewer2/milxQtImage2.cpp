#include "milxQtImage2.h"
#include "ui_milxQtImage2.h"
#include <QtGui> 
#include <QMessageBox> 
#include <QSystemTrayIcon> 
#include <QStringList> 





milxQtImage2::milxQtImage2(QMainWindow *parent, bool contextSystem)
{
	ui.setupUi(parent);
	//ui.view1 = qobject_cast<QVTKWidget*>(this);
	//ui.view2 = qobject_cast<QVTKWidget*>(this);
	//ui.view3 = qobject_cast<QVTKWidget*>(this);
	//ui.view4 = qobject_cast<QVTKWidget*>(this);
}
	
milxQtImage2::~milxQtImage2()
{

}

void milxQtImage2::generateImage(const bool quietly)
{
	for (int i = 0; i < 3; i++)
	{
		riw[i] = vtkSmartPointer<vtkImageViewer3>::New();
	}

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
}
