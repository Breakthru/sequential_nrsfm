#ifndef SYNTHDATA_H
#define SYNTHDATA_H

#include "camera.h"
#include "shapemodel.h"
#include <boost/shared_ptr.hpp>
#include <cstdlib>

void make_synth_data(double *params, boost::shared_ptr<RigidShape<double> > *shape )
{
    const int num_points=10;
    double pts[num_points*PNP];
    for (int i=0; i<num_points*PNP; i++)
        pts[i]=double(rand())/RAND_MAX;
    // increase Z values
    for (int i=2; i<num_points*PNP; i+=3)
        pts[i]+=1.0;

    shape->reset(new RigidShape<double>(pts, num_points));

    params[0]=1;
    for (int i=1;i<6; i++)
        params[i]=0;

}

void make_nr_synth_data(double *params, boost::shared_ptr<RigidShape<double> > *shape)
{

}

#endif // SYNTHDATA_H
