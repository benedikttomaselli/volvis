
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Volume.h"
#include "VectorField.h"
#include "MultiSet.h"
#include "VR.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QVariant>
#include "Shading.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		MainWindow(QWidget *parent = 0);
		~MainWindow();
		void drawTest(QImage* image);

	
	protected slots :

		void								 openFileAction();
		void								 closeAction();
		void invertClicked();
		void MIPClicked();
		void ACClicked();
		void FHClicked();
		void stepChanged();
		void TOPClicked();
		void SIDEClicked();
		void FRONTClicked();
		void threshChanged();
		void shadingClicked();
		void intensityChanged();
		void ambientChanged();
		

	private:

		// USER INTERFACE ELEMENTS

		Ui_MainWindow						*m_Ui;
		QLineEdit *stepInput;
		QLineEdit *intensityInput;
		QLineEdit *ambientInput;
		QLineEdit *threshInput;


		// DATA 

		enum DataType
		{
			VOLUME					= 0,
			VECTORFIELD				= 1,
			MULTIVARIATE			= 2
		};

		struct FileType
		{
			QString			filename;
			DataType		type;
		}									 m_FileType;

		Volume								*m_Volume;						// for Volume-Rendering
		VectorField							*m_VectorField;					// for Flow-Visualisation
		MultiSet							*m_MultiSet;					// for Multivariate Data
		QImage *image;
		QLabel *qlabel;
		VR *renderer;
		VR_MIP *MIP;
		VR_FirstHit *FH;
		VR_AlphaCompositing *AC;
		bool invert;
		bool alt;
		int step;
		VR::ViewDirection vd;

};

#endif
