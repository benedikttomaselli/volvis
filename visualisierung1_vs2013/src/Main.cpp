//Kolb Mathias, 0625588
//Tomaselli Benedikt, 0926048

#include "MainWindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();

}
