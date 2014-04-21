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

#endif // SHAPEMODEL_H
