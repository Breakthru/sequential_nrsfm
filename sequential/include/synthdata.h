#ifndef SYNTHDATA_H
#define SYNTHDATA_H

#include "camera.h"
#include "shapemodel.h"
#include <boost/shared_ptr.hpp>

void make_synth_data(double *params, boost::shared_ptr<RigidShape<double> > *shape )
{
    const int num_points=10;
    double pts[num_points*PNP];
    for (int i=0; i<num_points*PNP; i++)
        pts[i]=i;

    shape->reset(new RigidShape<double>(pts, num_points));

    params[0]=1;
    for (int i=1;i<6; i++)
        params[i]=0;

}

#endif // SYNTHDATA_H
