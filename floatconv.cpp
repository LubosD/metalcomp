#include <iostream>
#include <cassert>

using namespace std;

//typedef unsigned short[3] pascal_real;
// ax
// bx
// dx
struct pascal_real
{
	unsigned char ax[2];
	unsigned char bx[2];
	unsigned char dx[2];
};

static char ld[10];
static double out;

double real2float(pascal_real r);

int main(int argc,char** argv)
{
	char buf[20];
	
	while(true)
	{
		double num;
		pascal_real real;
		cerr << "0x0: ";
		cin >> buf;
		if(cin.eof())
			break;
		
		*((unsigned short*) real.ax) = strtol(buf, 0, 16);
		cerr << "0x2: ";
		cin >> buf;
		*((unsigned short*) real.bx) = strtol(buf, 0, 16);
		cerr << "0x4: ";
		cin >> buf;
		*((unsigned short*) real.dx) = strtol(buf, 0, 16);
		
		num = real2float(real);
		cerr.precision(8);
		cerr << "Number: " <<  num << endl;
		cout.precision(8);
		cout << num << ", ";
	}
	cout << endl;
	
	return 0;
}

double real2float(pascal_real r)
{
	char cx[2];
	if(r.ax[0] == 0)
		return 0;
	cx[0] = 0;
	cx[1] = r.ax[1];
	r.ax[1] = r.dx[1];
	r.ax[1] &= 0x80;
	*((unsigned short*) r.ax) += 0x3f7e;
	r.dx[1] |= 0x80;
	
	ld[0] = 0;
	ld[1] = 0;
	ld[2] = cx[0];
	ld[3] = cx[1];
	ld[4] = r.bx[0];
	ld[5] = r.bx[1];
	ld[6] = r.dx[0];
	ld[7] = r.dx[1];
	ld[8] = r.ax[0];
	ld[9] = r.ax[1];
	
	__asm (
	".intel_syntax noprefix\n"
	"fld tbyte ptr ld\n"
	"fstp qword ptr [out]\n"
	".att_syntax\n");
	
	return out;
}
