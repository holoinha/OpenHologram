#include "hologramdepthmap.h"
#include <QtCore/QTime>

HologramDepthmap::HologramDepthmap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.pbGen, SIGNAL(clicked()), this, SLOT(GenHologram()));
	QObject::connect(ui.pbRecon, SIGNAL(clicked()), this, SLOT(ReconImage()));
	
	hologram_ = 0;

}

HologramDepthmap::~HologramDepthmap()
{

}

void HologramDepthmap::GenHologram()
{
	LOG("Generate Hologram\n");

	if (!hologram_)
		hologram_ = new HologramGenerator();

	if (!hologram_->readConfig())
	{
		QMessageBox::warning(this,"Warning", "Error: Wrong Format\n", QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	QTime t;
	t.start();

	hologram_->initialize();
	hologram_->GenerateHologram();

	LOG("Time : %d \n", t.elapsed());

}
void HologramDepthmap::ReconImage()
{
	if (!hologram_)
	{
		hologram_ = new HologramGenerator();
		if (!hologram_->readConfig())
		{
			QMessageBox::warning(this, "Warning", "Error: Wrong Format\n", QMessageBox::Ok, QMessageBox::Ok);
			return;
		}
	}

	LOG("Reconstruct Image\n");

	hologram_->ReconstructImage();
	
}
