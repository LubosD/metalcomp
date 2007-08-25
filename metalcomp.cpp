#include <QApplication>
#include "mainwindow.h"
#include "metalcomp.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	MainWindow wnd;
	
	wnd.show();
	return app.exec();
}

double computeThermalElement(TE_Type type, double voltage, double clampTemperature)
{
	const double data[][9] = {
		{ 0.00598, 1.9482941, 167.1759, -29.629164, 8.0396286, -1.3297225, 0.12650078, -0.0064036964, 0.00013361744 },
		{ 0.00596, 2.3399546, 166.96606, -31.01295, 7.8240305, -1.2091343, 0.10722102, -0.0050320074, 9.6812012e-5 },
		{ 0.0404, 1.2153716, 23.301166, 0.28795151, -0.02401098, 0.00080276845, -1.1843844e-5, 6.2962201e-8, 6.1032164e-11 },
		{ 0.0267931, 0.043683104, 38.679623, -1.1157723, 0.061590637, -0.0023135575, 5.4782579e-05, -7.1861926e-07, 3.9693632e-09 },
		{ 0.0517317, -0.59326364, 20.295133, -0.29971242, 0.017550324, -0.00045578504, 4.2653871e-06, 4.8523606e-09, -1.8964102e-10 }
	};
	
	double result = 0;
	
	voltage += clampTemperature * data[type][0];
	result = data[type][8];
	
	for(int i=7;i>=1;i--)
	{
		result *= voltage;
		result += data[type][i];
	}
	
	return (result < 2000) ? result : 2000;
}
