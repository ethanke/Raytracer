#include "triangle.h"

Triangle::Triangle()
{
    this->point[0].x = 0;
    this->point[0].y = 0;
    this->point[0].z = 0;

    this->point[1].x = 0;
    this->point[1].y = 0;
    this->point[1].z = 0;

    this->point[1].x = 0;
    this->point[2].y = 0;
    this->point[2].z = 0;

    this->material = new Material();
}

Triangle::Triangle(const Vector3f<float> point1, const Vector3f<float> point2, const Vector3f<float> point3, Material *mat)
{
    this->point[0].x = point1.x;
    this->point[0].y = point1.y;
    this->point[0].z = point1.z;

    this->point[1].x = point2.x;
    this->point[1].y = point2.y;
    this->point[1].z = point2.z;

    this->point[1].x = point3.x;
    this->point[2].y = point3.y;
    this->point[2].z = point3.z;

    this->material = mat;
}

bool Triangle::hit(const Camera ray, float &old_dist)
{
    Vector3f<float> e1, e2;  //Edge1, Edge2
    Vector3f<float> P, Q, T;
    float det, inv_det, u, v;
    float t;

    //Find vectors for two edges sharing this->point[0]
    e1 = this->point[1] + this->point[0];
    e2 = this->point[2] + this->point[0];
    //Begin calculating determinant - also used to calculate u parameter
    P = Vector3f<float>::cross(ray.direction, e2);
    //if determinant is near zero, ray lies in plane of triangle
    det = e1.dot(P);
    //NOT CULLING
    if(det > - 0.01 && det < 0.01)
        return 0;
    inv_det = 1.f / det;

    //calculate distance from this->point[0] to ray origin
    T = ray.start + this->point[0];

    //Calculate u parameter and test bound
    u = T.dot(P) * inv_det;
    //The intersection lies outside of the triangle
    if(u < 0.f || u > 1.f)
        return 0;

    //Prepare to test v parameter
    Q = Vector3f<float>::cross(T, e1);

    //Calculate V parameter and test bound
    v = ray.direction.dot(Q) * inv_det;
    //The intersection lies outside of the triangle
    if(v < 0.f || u + v  > 1.f)
        return 0;

    t = e2.dot(Q) * inv_det;

    if(t > 0.01 && t < old_dist)
    { //ray intersection
      old_dist = t;
      return 1;
    }

    // No hit, no win
    return 0;
}

Vector3f<float> Triangle::getNormale(const Camera ray, const Vector3f<float> hitPoint)
{
    Vector3f<float> S1S2(this->point[1].x-this->point[0].x,this->point[1].y-this->point[0].y,this->point[1].z-this->point[0].z);
    Vector3f<float> S1S3(this->point[2].x-this->point[0].x,this->point[2].y-this->point[0].y,this->point[2].z-this->point[0].z);
    Vector3f<float> N;
    N.x = (this->point[1].y-this->point[0].y)*(this->point[2].z-this->point[0].z) - (this->point[1].z-this->point[0].z)*(this->point[2].y-this->point[0].y);
    N.y = (this->point[1].z-this->point[0].z)*(this->point[2].x-this->point[0].x) - (this->point[1].x-this->point[0].x)*(this->point[2].z-this->point[0].z);
    N.z = (this->point[1].x-this->point[0].x)*(this->point[2].y-this->point[0].y) - (this->point[1].y-this->point[0].y)*(this->point[2].x-this->point[0].x);
    if (N.x >= 0 || N.y >= 0 || N.z >= 0)
        return (-N.normalize());
    return (N.normalize());
}

Vector3f<float> Triangle::getObjectColor(const Vector3f<float> hitPoint)
{
    return (Vector3f<float>(this->material->color->r, this->material->color->g, this->material->color->b) / 255.0);
}

QString Triangle::getObjectType()
{
    return (QString("Triangle"));
}
