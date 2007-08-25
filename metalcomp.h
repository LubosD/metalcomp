#ifndef METALCOMP_H
#define METALCOMP_H

enum TE_Type { Pt_Rh10 = 0, Pt_Rh13, Ni_CrNi, Ni_CrSi, Fe_Co };

double computeThermalElement(TE_Type type, double voltage, double clampTemperature);

#endif
