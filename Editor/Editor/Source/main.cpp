//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Meshwork 3D Engine Editor Copyright (C) 2014  Ivan Donev
//
//	This program is released under the MIT License. You are free to use, distribute and modify this code as you see fit. For more info, please read the MIT License
//
//	For help and documentation on the editor and the engine, visit <http://morroworks.com>
//	You're very welcome to post your questions and get support at the community page!
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Needed to save window, docking and toolbars states
    QCoreApplication::setOrganizationDomain("Morroworks.com");
    QCoreApplication::setOrganizationName("Morroworks");
    QCoreApplication::setApplicationName("Meshwork Editor");
    QCoreApplication::setApplicationVersion("0.8.9");

    MainWindow w;
    w.show();

    return a.exec();
}
