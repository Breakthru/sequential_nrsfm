#ifndef SYNTHDATA_H
#define SYNTHDATA_H

#include "camera.h"
#include "shapemodel.h"

void make_synth_data(double *params, RigidShape<double> *shape )
{
    const int num_points=10;
    double *pts = new double[num_points*PNP];
    for (int i=0; i<num_points*PNP; i++)
        pts[i]=i;

    shape = new RigidShape<double>(pts, num_points);

    params[0]=1;
    for (int i=1;i<6; i++)
        params[i]=0;

    delete[] pts;
}

#endif // SYNTHDATA_H
