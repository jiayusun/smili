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
	milxQtImage::generateImage(quietly);
   //ui.view1->SetRenderWindow(GetRenderWindow());
  //riw[0]->SetupInteractor(
    //  ui.view1->GetRenderWindow()->GetInteractor());

   //ui.view2->SetRenderWindow(GetRenderWindow());
//  riw[1]->SetupInteractor(
  //    ui.view2->GetRenderWindow()->GetInteractor());

     //ui.view3->SetRenderWindow(GetRenderWindow());
  //riw[2]->SetupInteractor(
    //  ui.view3->GetRenderWindow()->GetInteractor());
}