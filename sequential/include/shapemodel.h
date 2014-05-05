#ifndef SHAPEMODEL_H
#define SHAPEMODEL_H

#include <stdexcept>

// parameters per point
#define PNP 3


template<class T>
class RigidShape {
public:
    T *pts_;
    int num_points_;

    RigidShape(const T *pts, int num_points):
        num_points_(num_points)
    {
        if (num_points_<=0)
            throw std::invalid_argument("a rigid shape must have at least one point");

        pts_ = new T[num_points_*PNP];
        for (int i=0; i < num_points*PNP; ++i) {
            pts_[i]=pts[i];
        }
    }
    ~RigidShape() {
        if (num_points_>0)
            delete [] pts_;
    }

    int num_points() const { return num_points_; }
    void compute(const T* , T* pts) {
        for (int i=0; i < num_points_*PNP; ++i) {
            pts[i] = pts_[i];
        }
    }
};

template<class T>
class NonRigidShape {
public:
    T *pts_;
    int num_points_;
    int K_;
    T *bases_;

    NonRigidShape(const T *bases, int num_points, int K):
        num_points_(num_points),
        K_(K)
    {
        bases_=new T[PNP*K*num_points];
        for (int k=0; k<K; k++)
        {
            for (int i=0; i < num_points*PNP; ++i)
            {
                bases_[k*num_points*PNP+i]=bases[k*num_points*PNP+i];
            }
        }
    }

    int num_points() const { return num_points_; }
    int num_bases() const { return K_; }
    /// params are the coefficients, vector of K elements
    void compute(const T* params, T* pts) {
        // init points to zero
        for (int i=0; i < num_points_*PNP; ++i) {
            pts[i] = 0;
        }
        // sum coeff. times base
        for (int k=0; k<K_; k++)
        {
            for (int i=0; i < num_points*PNP; ++i)
            {
                pts[i]=params[k]*bases_[k*num_points*PNP+i];
            }
        }
    }
};

#endif // SHAPEMODEL_H
