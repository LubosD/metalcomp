#include "mainwindow.h"
#include "metalcomp.h"
#include <QMessageBox>

MainWindow::MainWindow()
{
	setupUi(this);
	
	connect(pushAbout, SIGNAL(clicked()), this, SLOT(about()));
	connect(pushThermalElementCompute, SIGNAL(clicked()), this, SLOT(computeThermalElement()));
	
	computeThermalElement();
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About MetalComp"),
			QString::fromUtf8("<b>MetalComp</b><p>"
			"Copyright © 2007 Luboš Doležel &lt;lubos@dolezel.info&gt;<p>"
			"Web: <a href=\"http://www.dolezel.info\">http://www.dolezel.info</a><p>"
			"Licensed under terms of the GNU GPL v2 license.")
			);
}

void MainWindow::computeThermalElement()
{
	double voltage, clampTemperature, result;
	TE_Type type;
	
	if(radioTE_Type1->isChecked())
		type = Pt_Rh10;
	if(radioTE_Type2->isChecked())
		type = Pt_Rh13;
	if(radioTE_Type3->isChecked())
		type = Ni_CrNi;
	if(radioTE_Type4->isChecked())
		type = Ni_CrSi;
	if(radioTE_Type5->isChecked())
		type = Fe_Co;
	
	voltage = doubleThermalVoltage->value();
	clampTemperature = doubleClampTemperature->value();
	
	result = ::computeThermalElement(type, voltage, clampTemperature);
	
	lineThermalElementResult->setText(QString::number(result));
}

