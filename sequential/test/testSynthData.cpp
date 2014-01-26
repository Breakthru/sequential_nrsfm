#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "costframe.h"
#include "synthdata.h"

BOOST_AUTO_TEST_CASE( camera ) {
    double *params;
    RigidShape<double> *shape;
    make_synth_data(params,shape);
    OrthographicCamera<double> camera;
    double measurements[shape->num_points()];
    camera.project(params,shape->pts_,shape->num_points(),measurements);


    delete []params;
}
