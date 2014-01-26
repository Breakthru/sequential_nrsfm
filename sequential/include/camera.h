#ifndef CAMERA_H
#define CAMERA_H

#include "cameraparameters.h"

// measurements per point
#define MNP 2
// parameters per point
#define PNP 3


template <class T>
class OrthographicCamera
{
public:
    int num_params() const {
        return 6; // quaternion and 2D translation
    }

    void project(const T* params, const T* pts, int num_points, T* projections_) {
        Eigen::Matrix<T,3,3> R;
        quaternion2rotation(params, &R);
        T tx = params[4];
        T ty = params[5];
        int idx=0;
        int pt_idx=0;
        for (int i=0; i < num_points; ++i) {
            projections_[idx++] = R(0,0)*pts[pt_idx] + R(0,1)*pts[pt_idx+1] + R(0,2)*pts[pt_idx+2] + tx;
            projections_[idx++] = R(1,0)*pts[pt_idx] + R(1,1)*pts[pt_idx+1] + R(1,2)*pts[pt_idx+2] + ty;
            pt_idx+=PNP;
        }
    }
};

template <class T>
class PerspectiveCamera
{
public:
    int num_params() const {
        return 11; // fx, fy, cx, cy, quaternion and tranlation
    }
};

#endif // CAMERA_H
