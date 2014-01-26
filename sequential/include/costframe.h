#ifndef COSTFRAME_H
#define COSTFRAME_H

#include "camera.h"


/**
 * @brief  cost function for time-varying parameters
 * compute the projections given camera matrices and
 * deformation coefficients
 * from an array of parameters for one frame, compute measurements for that frame
 */
template <class T, class CameraModel, class ShapeModel>
class CostFrame
{
public:
    // 3d shape at one frame
    T *pts_;
    // measurements at one frame
    T *measurements_;
    int shape_param_idx_;
    int num_points_;
    const CameraModel *camera_;
    const ShapeModel *shape_;
    T *projections_;

    CostFrame(const T* measurements, const CameraModel *camera, const ShapeModel *shape):
        pts_(NULL),
        measurements_(NULL),
        shape_param_idx_(0),
        num_points_(0),
        camera_(camera),
        shape_(shape)
    {
        shape_param_idx_ = camera_->num_params();
        num_points_ = shape_->num_points();
        if (num_points_<1)
            return;

        pts_ = new T[num_points_*PNP];
        measurements_ = new T[num_points_*MNP];
        projections_ = new T[num_points_*MNP];
        const int t=num_points_*MNP;
        for (int i=0; i<t ; ++i) {
            measurements_[i]=measurements[i];
        }
    }

    ~CostFrame() {
        if (pts_)
            delete []pts_;
        if (measurements_)
            delete []measurements_;
    }



    /// parameters are [camera parameters... shape parameters]
    /// [u v] = projection( pt, camera )
    T compute(const T * params)
    {

        T residual=0;
        shape_->compute(params[shape_param_idx_],pts_);
        camera_->project(params, pts_, num_points_, projections_);
        const int t=num_points_*MNP;
        for (int j=0; j<t; j++) {
            T r = measurements_[j]-projections_[j];
            residual += r*r;
        }

        residual /= 0.5*num_points_;

        return residual;
    }

};

#endif // COSTFRAME_H
