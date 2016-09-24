/*=========================================================================
  The Software is copyright (c) Commonwealth Scientific and Industrial Research Organisation (CSIRO)
  ABN 41 687 119 230.
  All rights reserved.

  Licensed under the CSIRO BSD 3-Clause License
  You may not use this file except in compliance with the License.
  You may obtain a copy of the License in the file LICENSE.md or at

  https://stash.csiro.au/projects/SMILI/repos/smili/browse/license.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
=========================================================================*/
//Qt
#include <QApplication>
#include <QMainWindow>
#include "milxQtFile.h"
#include "milxQtImage2.h"


int main(int argc, char *argv[])
{
	QApplication *app = new QApplication(argc, argv);
	QMainWindow *mainWindow = new QMainWindow;
	
    QPixmap icon(":resources/smilx_icon.png");
    app->setWindowIcon(QIcon(icon));

    if (argc < 2)
    {
        cerr << "milxImageViewer2 Application:" << endl;
        cerr << "For quick and fast display of image files." << endl;
        cerr << "View configuration always matches sMILX settings wherever possible." << endl;
        cerr << "Usage:" << endl;
        cerr << "<Image Filename> " << endl;
        return EXIT_FAILURE;
    }

    std::string inputSurfaceFilename = argv[1];

    //Load the vertex table from CSV file
    milxQtImage2 *image = new milxQtImage2(mainWindow); //app takes ownership so need to be on stack, not heap
    milxQtFile *reader = new milxQtFile(mainWindow);
    bool success = reader->openImage(inputSurfaceFilename.c_str(), image);

    if(!success)
    {
      cerr << "Error opening image file." << endl;
      return EXIT_FAILURE;
    }

    image->generateImage();
    
    //Setup size
    QSize desktopSize = qApp->desktop()->availableGeometry().size();
    int newWidth = 567;
    int newHeight = 633;
    int xOffset = (desktopSize.width()-newWidth)/2.0;
    int yOffset = (desktopSize.height()-newHeight)/2.0;
    mainWindow->resize( QSize(newWidth, newHeight) );
    mainWindow->move( QPoint(xOffset, yOffset) );
	/*
    //Setup view to match sMILX
    QSettings settings("Shekhar Chandra", "milxQt");
    int defaultViewMode = 2; //axial
    int defaultOrientationTypeMode = 0; //radiological
    image->setView(settings.value("defaultView", defaultViewMode).toInt());
    image->setDefaultOrientation(settings.value("defaultOrientationType", defaultOrientationTypeMode).toInt());

    //Setup menu
    QMenuBar *menuBar = new QMenuBar(&mainWindow);
    //File
    QMenu *menuFile = menuBar->addMenu("File");
    image->createMenu(menuFile);
    QAction *actionExit = menuFile->addAction("Exit");
    QObject::connect(actionExit, SIGNAL(activated()), &mainWindow, SLOT(close()));
    mainWindow.setMenuBar(menuBar);
    */
    mainWindow->setWindowTitle("milxImageViewer2");
    mainWindow->show();
	QObject::connect(app, SIGNAL(aboutToQuit()), image, SLOT(writeSettings()));
    return app->exec();
}
