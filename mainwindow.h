#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_comboBox_Heightmap_currentIndexChanged(int index);

	void on_doubleSpinBox_CellSize_valueChanged(double arg1);

	void on_spinBox_SatRes_valueChanged(int arg1);

	void on_doubleSpinBox_MeterPerPixel_valueChanged(double arg1);

	void on_actionAbout_triggered();

	void on_actionPMC_Editing_Wiki_triggered();

	void on_pushButton_Clipboard_Short_clicked();

	void on_pushButton_Clipboard_Long_clicked();

	void on_comboBox_PresetTerrainSizes_currentIndexChanged(int index);

	void on_checkBox_UseMeterPerPixel_stateChanged(int arg1);

private:
	Ui::MainWindow *ui;
	QString version = "v0.0.1";
	void updateTerrainSize();
	double cellSize;
	int satelliteRes;
	double meters;
	double km2;
	double pixelfinal;
	int gridSize;
};

#endif // MAINWINDOW_H
