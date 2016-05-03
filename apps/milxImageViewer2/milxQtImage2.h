    #ifndef __DLG_H__
     #define __DLG_H__

     #include <QDialog.h>
     #include <milxImageViewer2.h>

     class milxQtImage2 : public QDialog
     {
     Q_OBJECT
     public:
         milxQtImage2(); 
     private:
         Ui::milxImageViewer2 ui;
     };

     #endif