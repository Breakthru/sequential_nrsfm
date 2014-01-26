#ifndef CAMERAPARAMETERS_H
#define CAMERAPARAMETERS_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

/**
 * @brief The CameraParameters class encapsulates all
 * parameters that vary per-frame, such as:
 * camera intrinsics
 * camera extrinsics
 * deformation coefficients
 * This class is used to convert a vector of parameters
 * into camera specific matrices
 */
template<class T> class CameraParameters
{
    T* p_;
public:
    /**
     * @brief CameraParameters encapsulates the parameter vector
     * @param parameters
     * camera translation (tx,ty,tz)
     * camera rotation as a quaternion (q1,q2,q3,q4)
     * deformation coefficients (d_1,...,d_r)
     */
    CameraParameters(T* parameters)
    {
        p_ = parameters;
    }       

};

/// 4-vector q, 9-vector row-major 3x3 R
template<class T>
void quaternion2rotation(const T* q, Eigen::Matrix<T,3,3> *R) {
    Eigen::Quaternion<T> quat(q[0],q[1],q[2],q[3]);
    quat.normalize();
    *R = quat.toRotationMatrix();
}

#endif // CAMERAPARAMETERS_H
