#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, Ui_MainWindow
{
Q_OBJECT
public:
	MainWindow();
private slots:
	void about();
	void computeThermalElement();
	void computeLambdaProbe();
};

#endif
