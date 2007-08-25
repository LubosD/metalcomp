#include <QApplication>
#include <cmath>
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

double computeLambdaProbe(double temperature, double voltage, double CO, double K1, double K2)
{
	const double const1 = 0.043082;
	const double const2 = 9.19884;
	const double const3 = 0.434294;
	
	double var1,var2,var3;
	double result = 1.0f;
	
	var1 = (K1 - voltage) / (temperature * const1) + const2 - log(CO);
	var2 = K2 / const3;
	
	var3 = 1.0;
	
	for(int i=0;i<12;i++)
	{
		var3 /= 2.0;
				
		if((var2 * result - log(result)) < var1)
			result -= var3;
		else
			result += var3;
	}
	
	return result;
}
