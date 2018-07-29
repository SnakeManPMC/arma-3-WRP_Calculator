#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle("WRP Calculator " + version + " (c) PMC");

	QFont f( "Verdana", 32, QFont::Bold);
	ui->label_Summary->resize(1000,50);
	ui->label_Summary->setFont(f);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_comboBox_Heightmap_currentIndexChanged(int index)
{
	updateTerrainSize();
}

void MainWindow::on_doubleSpinBox_CellSize_valueChanged(double arg1)
{
	updateTerrainSize();
}

void MainWindow::on_spinBox_SatRes_valueChanged(int arg1)
{
	updateTerrainSize();
}

void MainWindow::on_doubleSpinBox_MeterPerPixel_valueChanged(double arg1)
{
	updateTerrainSize();
}

void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::about(this, "WRP Calculator " + version, "<b>WRP Calculator " + version + "</b>.<br><br>Small tool to help quickly check various terrain sizes and combinations with all the grid, cell, satellite oh my sizes.");
}

void MainWindow::on_actionPMC_Editing_Wiki_triggered()
{
	QDesktopServices::openUrl(QUrl("https://pmc.editing.wiki/doku.php?id=arma3:terrain", QUrl::TolerantMode));
}

void MainWindow::updateTerrainSize()
{
	cellSize = ui->doubleSpinBox_CellSize->value();
	satelliteRes = ui->spinBox_SatRes->value();

	if (ui->comboBox_Heightmap->currentIndex() == 0)
		gridSize = 4;
	if (ui->comboBox_Heightmap->currentIndex() == 1)
		gridSize = 8;
	if (ui->comboBox_Heightmap->currentIndex() == 2)
		gridSize = 16;
	if (ui->comboBox_Heightmap->currentIndex() == 3)
		gridSize = 32;
	if (ui->comboBox_Heightmap->currentIndex() == 4)
		gridSize = 64;
	if (ui->comboBox_Heightmap->currentIndex() == 5)
		gridSize = 128;
	if (ui->comboBox_Heightmap->currentIndex() == 6)
		gridSize = 256;
	if (ui->comboBox_Heightmap->currentIndex() == 7)
		gridSize = 512;
	if (ui->comboBox_Heightmap->currentIndex() == 8)
		gridSize = 1024;
	if (ui->comboBox_Heightmap->currentIndex() == 9)
		gridSize = 2048;
	if (ui->comboBox_Heightmap->currentIndex() == 10)
		gridSize = 4096;
	if (ui->comboBox_Heightmap->currentIndex() == 11)
		gridSize = 8192;
	if (ui->comboBox_Heightmap->currentIndex() == 12)
		gridSize = 16384;
	if (ui->comboBox_Heightmap->currentIndex() == 13)
		gridSize = 32768;
	if (ui->comboBox_Heightmap->currentIndex() == 14)
		gridSize = 65536;

	// terrain size in meters
	meters = (gridSize * cellSize);

	// terrain size in square kilometers
	km2 = ( (meters/1000) * (meters/1000));

	// satellite map details - meters per pixel
	pixelfinal = (meters / satelliteRes);

	// if we want desired m/px
	if (ui->checkBox_UseMeterPerPixel->isChecked())
	{
		double mpx = ui->doubleSpinBox_MeterPerPixel->value();
		// sat = terrain / meter per pixel
		ui->spinBox_SatRes->setValue((meters / mpx));
	}

	// display them in text edits
	// first the size of the terrain
	ui->lineEdit_TerrainSizeMeters->setText( QString::number( (meters) ) + " x " + QString::number( (meters) ) + " meters (" + QString::number( (meters/1000) ) + " km), " + QString::number(km2) + " square km" );
	// then pixels per meter and also blue edge
	ui->lineEdit_MeterPerPixel->setText( QString::number( (pixelfinal) ) );
	ui->lineEdit_TextureLayer->setText(QString::number(cellSize * 4));
	ui->lineEdit_LandGrid->setText(QString::number(gridSize / cellSize));

	// clip this to highest we got in-game, ie iran jahrom 163,840 x 163,840 res
	if ((gridSize * cellSize) > 163840) ui->lineEdit_RecSatRes->setText("163840");
		else
		ui->lineEdit_RecSatRes->setText(QString::number(gridSize * cellSize));

	ui->label_Summary->setText(QString::number((meters/1000)) + "km x " + QString::number((meters/1000)) + "km");
}

// one liner terrain specifications
void MainWindow::on_pushButton_Clipboard_Short_clicked()
{
	QString buffader;
	buffader.append("Terrain size " + QString::number(meters / 1000));
	buffader.append("km, Satellite res " + QString::number(satelliteRes));
	buffader.append(", " + QString::number(pixelfinal) + " m/px");

	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(buffader);
}

// longer several lines terrain specifications
void MainWindow::on_pushButton_Clipboard_Long_clicked()
{
	QString buffader;
	buffader.append("Written by WRP Calculator " + version + " (c) PMC.\n\n");
	buffader.append("Terrain size: " + QString::number(meters / 1000) + " kilometers x " + QString::number(meters / 1000) + " kilometers\n");
	buffader.append("Heightmap grid size " + QString::number(gridSize) + "\n");
	buffader.append("Cell size " + QString::number(cellSize) + " meters\n");
	buffader.append("Satellite resolution " + QString::number(satelliteRes) + " pixels\n");
	buffader.append("Satellite meters per pixel scale " + QString::number(pixelfinal) + "\n");

	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(buffader);
}

void MainWindow::on_comboBox_PresetTerrainSizes_currentIndexChanged(int index)
{
	// 2km
	if (index == 0)
	{
		// 7 - 512
		ui->comboBox_Heightmap->setCurrentIndex(7);
		ui->doubleSpinBox_CellSize->setValue(4);
		ui->spinBox_SatRes->setValue(2048);
	}

	// 5km
	if (index == 1)
	{
		// 8 - 1024
		ui->comboBox_Heightmap->setCurrentIndex(8);
		ui->doubleSpinBox_CellSize->setValue(5);
		ui->spinBox_SatRes->setValue(5120);
	}

	// 10km
	if (index == 2)
	{
		// 9 - 2048
		ui->comboBox_Heightmap->setCurrentIndex(9);
		ui->doubleSpinBox_CellSize->setValue(5);
		ui->spinBox_SatRes->setValue(10240);
	}

	// 15km
	if (index == 3)
	{
		ui->comboBox_Heightmap->setCurrentIndex(9);
		ui->doubleSpinBox_CellSize->setValue(7.5);
		ui->spinBox_SatRes->setValue(15360);
	}

	// 20km
	if (index == 4)
	{
		ui->comboBox_Heightmap->setCurrentIndex(9);
		ui->doubleSpinBox_CellSize->setValue(10);
		ui->spinBox_SatRes->setValue(20480);
	}

	// 40km
	if (index == 5)
	{
		// 10 - 4096
		ui->comboBox_Heightmap->setCurrentIndex(10);
		ui->doubleSpinBox_CellSize->setValue(10);
		ui->spinBox_SatRes->setValue(40960);
	}

	// 81km
	if (index == 6)
	{
		ui->comboBox_Heightmap->setCurrentIndex(10);
		ui->doubleSpinBox_CellSize->setValue(20);
		ui->spinBox_SatRes->setValue(81920);
	}

	// 102km
	if (index == 7)
	{
		ui->comboBox_Heightmap->setCurrentIndex(10);
		ui->doubleSpinBox_CellSize->setValue(25);
		ui->spinBox_SatRes->setValue(102480);
	}

	// 143km
	if (index == 8)
	{
		ui->comboBox_Heightmap->setCurrentIndex(10);
		ui->doubleSpinBox_CellSize->setValue(35);
		ui->spinBox_SatRes->setValue(143360);
	}

	// 163km
	if (index == 9)
	{
		ui->comboBox_Heightmap->setCurrentIndex(10);
		ui->doubleSpinBox_CellSize->setValue(40);
		ui->spinBox_SatRes->setValue(163840);
	}

	// 204km
	if (index == 10)
	{
		ui->comboBox_Heightmap->setCurrentIndex(10);
		ui->doubleSpinBox_CellSize->setValue(50);
		ui->spinBox_SatRes->setValue(163840);
	}
}

void MainWindow::on_checkBox_UseMeterPerPixel_stateChanged(int arg1)
{
	updateTerrainSize();
}
