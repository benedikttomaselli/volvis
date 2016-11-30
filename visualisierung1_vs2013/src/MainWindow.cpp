//Kolb Mathias, 0625588
//Tomaselli Benedikt, 0926048

#include "MainWindow.h"
#include <QFileDialog>
#include <QPainter>
#include <QtOpenGL>
#include <QColor>
#include "QLineEdit.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Volume(0), image(new QImage(500, 500, QImage::Format_RGB32))		//draw 500 pixel square
{
	invert = false;		//initialize inveft with boolean = false
	m_Ui = new Ui_MainWindow();
	m_Ui->setupUi(this);

	Shading* shading = new Shading;		//initialize shading class for gradient shading
	MIP = new VR_MIP(shading);		//initialize class for Maximum-Intensity-Projection
	FH = new VR_FirstHit(shading);		//initialize class for First Hit
	AC = new VR_AlphaCompositing(shading);		//initialize class for Alpha-Compositing
	renderer = MIP;		//renderer set to Maximum-Intensity-Projection as default

	vd = VR::TOP;



	QHBoxLayout *vlay = new QHBoxLayout(m_Ui->centralwidget);

	QVBoxLayout *imageLay = new QVBoxLayout();
	qlabel = new QLabel(m_Ui->centralwidget);

	qlabel->setPixmap(QPixmap::fromImage(*image));
	imageLay->addWidget(qlabel);
	QHBoxLayout *buttonsView = new QHBoxLayout();
	QPushButton *top = new QPushButton("top");		//button for top-view of object
	QPushButton *side = new QPushButton("side");		//button for side-view of object
	QPushButton *front = new QPushButton("front");		//button for frontal-view of object
	buttonsView->addWidget(top);
	buttonsView->addWidget(side);
	buttonsView->addWidget(front);
	imageLay->addLayout(buttonsView);
	vlay->addLayout(imageLay);
	QVBoxLayout *buttons = new QVBoxLayout();
	QHBoxLayout *stepLabel = new QHBoxLayout();
	stepInput = new QLineEdit();
	stepInput->setFixedWidth(50);
	stepInput->setValidator(new QIntValidator(0, 9));
	stepLabel->addWidget(stepInput);
	QLabel *stepL = new QLabel("sample distance");
	stepLabel->addWidget(stepL);

	buttons->addLayout(stepLabel);

	QPushButton *invertBtn = new QPushButton("invert");		//button to invert color
	invertBtn->setFixedWidth(200);
	buttons->addWidget(invertBtn);
	QPushButton *btnMIP = new QPushButton("Maximum-Intensity-Projection");		//button to selet Maximum-Intensity-Projection
	btnMIP->setFixedWidth(200);
	buttons->addWidget(btnMIP);
	QPushButton *btnAC = new QPushButton("Alpha Compositing");		//button to selet Alpha Compositing
	btnAC->setFixedWidth(200);
	buttons->addWidget(btnAC);
	QHBoxLayout * fh = new QHBoxLayout();
	QPushButton *btnFH = new QPushButton("First Hit");		//button to selet First Hit method
	btnFH->setFixedWidth(200);
	fh->addWidget(btnFH);
	threshInput = new QLineEdit();
	threshInput->setFixedWidth(50);
	threshInput->setValidator(new QDoubleValidator(0.0, 1.0, 4));
	fh->addWidget(threshInput);
	buttons->addLayout(fh);
	QPushButton *btnShading = new QPushButton("Gradient Shading (will not work with AlphaComp!)");
	buttons->addWidget(btnShading);

	QHBoxLayout *intensityLabel = new QHBoxLayout();
	intensityInput = new QLineEdit();
	intensityInput->setFixedWidth(50);
	intensityInput->setValidator(new QDoubleValidator(0.0, 1.0, 4));
	intensityLabel->addWidget(intensityInput);
	QLabel *intensityL = new QLabel("light intensity");		//button to selet the light intensity
	intensityLabel->addWidget(intensityL);
	buttons->addLayout(intensityLabel);

	QHBoxLayout *ambientLabel = new QHBoxLayout();
	ambientInput = new QLineEdit();
	ambientInput->setFixedWidth(50);
	ambientInput->setValidator(new QDoubleValidator(0.0, 1.0, 4));
	ambientLabel->addWidget(ambientInput);
	QLabel *ambientL = new QLabel("ambient light intensity");		//button to selet the ambient light intensity
	ambientLabel->addWidget(ambientL);
	buttons->addLayout(ambientLabel);

	buttons->setAlignment(Qt::AlignCenter);
	vlay->addLayout(buttons);
	m_Ui->centralwidget->setLayout(vlay);

	//Set image to draw
	//connecting the object on the canvas with the slots


	connect(invertBtn, SIGNAL(clicked()), this, SLOT(invertClicked()));
	connect(btnMIP, SIGNAL(clicked()), this, SLOT(MIPClicked()));
	connect(btnFH, SIGNAL(clicked()), this, SLOT(FHClicked()));
	connect(btnAC, SIGNAL(clicked()), this, SLOT(ACClicked()));
	connect(btnShading, SIGNAL(clicked()), this, SLOT(shadingClicked()));

	connect(top, SIGNAL(clicked()), this, SLOT(TOPClicked()));
	connect(side, SIGNAL(clicked()), this, SLOT(SIDEClicked()));
	connect(front, SIGNAL(clicked()), this, SLOT(FRONTClicked()));

	connect(stepInput, SIGNAL(textChanged(const QString &)), this, SLOT(stepChanged()));
	connect(threshInput, SIGNAL(textChanged(const QString &)), this, SLOT(threshChanged()));
	connect(intensityInput, SIGNAL(textChanged(const QString &)), this, SLOT(intensityChanged()));
	connect(ambientInput, SIGNAL(textChanged(const QString &)), this, SLOT(ambientChanged()));


	connect(m_Ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileAction()));
	connect(m_Ui->actionClose, SIGNAL(triggered()), this, SLOT(closeAction()));
	step = 1;
	alt = false;
}

MainWindow::~MainWindow()
{
	delete m_Volume;
	delete m_VectorField;
	delete m_MultiSet;
	delete FH;
	delete MIP;
	delete AC;
	delete image;
	delete qlabel;
}


//-------------------------------------------------------------------------------------------------
// Slots
//-------------------------------------------------------------------------------------------------

void MainWindow::invertClicked(){
	invert = !invert;
	if (m_Volume){
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::shadingClicked(){
	alt = !alt;
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::MIPClicked(){
	renderer = MIP;
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::FHClicked(){
	renderer = FH;
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::ACClicked(){
	renderer = AC;
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::stepChanged(){
	QString s = stepInput->text();
	step = s.toInt();
	if (m_Volume && 1 <= step){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::threshChanged(){
	QString s = threshInput->text();
	FH->setThreshold(s.toFloat());
	if (m_Volume && renderer == FH){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::intensityChanged(){
	QString s = intensityInput->text();

	renderer->setLightIntensity(s.toFloat());
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::ambientChanged(){
	QString s = ambientInput->text();

	renderer->setAmbientIntensity(s.toFloat());
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::TOPClicked(){
	vd = VR::TOP;
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}
void MainWindow::SIDEClicked(){
	vd = VR::SIDE;
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}
void MainWindow::FRONTClicked(){
	vd = VR::FRONT;
	if (m_Volume){
		renderer->setVolume(*m_Volume);
		renderer->drawVolume(image, qlabel, invert, alt, step, vd);
	}
}

void MainWindow::openFileAction()
{
	QString filename = QFileDialog::getOpenFileName(this, "Data File", 0, tr("Data Files (*.dat *.gri *.csv)"));

	if (!filename.isEmpty())
	{
		// store filename
		m_FileType.filename = filename;
		std::string fn = filename.toStdString();
		bool success = false;

		// progress bar and top label
		m_Ui->progressBar->setEnabled(true);
		m_Ui->labelTop->setText("Loading data ...");

		// load data according to file extension
		if (fn.substr(fn.find_last_of(".") + 1) == "dat")		// LOAD VOLUME
		{
			// create VOLUME
			m_FileType.type = VOLUME;
			m_Volume = new Volume();

			// load file
			success = m_Volume->loadFromFile(filename, m_Ui->progressBar);

			renderer->setVolume(*m_Volume);
			renderer->drawVolume(image, qlabel, invert, alt, step, vd);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "gri")		// LOAD VECTORFIELD
		{
			// create VECTORFIELD
			m_FileType.type = VECTORFIELD;
			m_VectorField = new VectorField();

			// load file
			success = m_VectorField->loadFromFile(filename, m_Ui->progressBar);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "csv")		// LOAD MULTIVARIATE DATA
		{
			// create MULTIVARIATE
			m_FileType.type = MULTIVARIATE;
			m_MultiSet = new MultiSet();

			// load file
			success = m_MultiSet->loadFromFile(filename, m_Ui->progressBar);
		}

		m_Ui->progressBar->setEnabled(false);

		// status message
		if (success)
		{
			QString type;
			if (m_FileType.type == VOLUME) type = "VOLUME";
			else if (m_FileType.type == VECTORFIELD) type = "VECTORFIELD";
			else if (m_FileType.type == MULTIVARIATE) type = "MULTIVARIATE";
			m_Ui->labelTop->setText("File LOADED [" + filename + "] - Type [" + type + "]");
		}
		else
		{
			m_Ui->labelTop->setText("ERROR loading file " + filename + "!");
			m_Ui->progressBar->setValue(0);
		}
	}
}

void MainWindow::closeAction()
{
	close();
}
