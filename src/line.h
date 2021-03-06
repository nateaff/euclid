#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"
#include "distance.h"

class line2 : public geometry_vector<Line_2, 2> {
public:
  using geometry_vector::geometry_vector;
  ~line2() = default;

  Primitive geometry_type() const { return LINE; }

  cpp11::writable::strings def_names() const {
    return {"a", "b", "c"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].a();
    case 1: return _storage[i].b();
    case 2: return _storage[i].c();
    }
    return _storage[i].a();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].a().exact()),
      CGAL::to_double(_storage[i].b().exact()),
      CGAL::to_double(_storage[i].c().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISORECT: return intersection_impl(get_vector_of_geo<Iso_rectangle>(other), _storage);
    case LINE: return intersection_impl(_storage, get_vector_of_geo<Line_2>(other));
    case POINT: return intersection_impl(_storage, get_vector_of_geo<Point_2>(other));
    case RAY: return intersection_impl(_storage, get_vector_of_geo<Ray_2>(other));
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case CIRCLE: return do_intersect_impl(get_vector_of_geo<Circle_2>(other), _storage);
    case ISORECT: return do_intersect_impl(get_vector_of_geo<Iso_rectangle>(other), _storage);
    case LINE: return do_intersect_impl(_storage, get_vector_of_geo<Line_2>(other));
    case POINT: return do_intersect_impl(_storage, get_vector_of_geo<Point_2>(other));
    case RAY: return do_intersect_impl(_storage, get_vector_of_geo<Ray_2>(other));
    case SEGMENT: return do_intersect_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return do_intersect_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: return unknown_intersect_impl(std::max(size(), other.size()));
    }
  }

  std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return squared_distance_impl(_storage, get_vector_of_geo<Line_2>(other));
    case POINT: return squared_distance_impl(_storage, get_vector_of_geo<Point_2>(other));
    case RAY: return squared_distance_impl(_storage, get_vector_of_geo<Ray_2>(other));
    case SEGMENT: return squared_distance_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return squared_distance_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: return unknown_squared_distance_impl(std::max(size(), other.size()));
    }
  }

  cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return distance_matrix_impl(_storage, get_vector_of_geo<Line_2>(other));
    case POINT: return distance_matrix_impl(_storage, get_vector_of_geo<Point_2>(other));
    case RAY: return distance_matrix_impl(_storage, get_vector_of_geo<Ray_2>(other));
    case SEGMENT: return distance_matrix_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return distance_matrix_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: return unknown_distance_matrix_impl(size(), other.size());
    }
  }
};

typedef cpp11::external_pointer<line2> line2_p;

class line3 : public geometry_vector<Line_3, 3, Line_2> {
public:
  using geometry_vector::geometry_vector;
  ~line3() = default;

  Primitive geometry_type() const { return LINE; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z", "dx", "dy", "dz"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].point(0.0).x();
    case 1: return _storage[i].point(0.0).y();
    case 2: return _storage[i].point(0.0).z();
    case 3: return _storage[i].direction().dx();
    case 4: return _storage[i].direction().dy();
    case 5: return _storage[i].direction().dz();
    }
    return _storage[i].point(0.0).x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].point(0.0).x().exact()),
      CGAL::to_double(_storage[i].point(0.0).y().exact()),
      CGAL::to_double(_storage[i].point(0.0).z().exact()),
      CGAL::to_double(_storage[i].direction().dx().exact()),
      CGAL::to_double(_storage[i].direction().dy().exact()),
      CGAL::to_double(_storage[i].direction().dz().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISOCUBE: return intersection_impl(get_vector_of_geo<Iso_cuboid>(other), _storage);
    case LINE: return intersection_impl(_storage, get_vector_of_geo<Line_3>(other));
    case PLANE: return intersection_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return intersection_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return intersection_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_3>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_3>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISOCUBE: return do_intersect_impl(get_vector_of_geo<Iso_cuboid>(other), _storage);
    case LINE: return do_intersect_impl(_storage, get_vector_of_geo<Line_3>(other));
    case PLANE: return do_intersect_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return do_intersect_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return do_intersect_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return do_intersect_impl(_storage, get_vector_of_geo<Segment_3>(other));
    case SPHERE: return do_intersect_impl(_storage, get_vector_of_geo<Sphere>(other));
    case TETRAHEDRON: return do_intersect_impl(_storage, get_vector_of_geo<Tetrahedron>(other));
    case TRIANGLE: return do_intersect_impl(_storage, get_vector_of_geo<Triangle_3>(other));
    default: return unknown_intersect_impl(std::max(size(), other.size()));
    }
  }

  std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return squared_distance_impl(_storage, get_vector_of_geo<Line_3>(other));
    case PLANE: return squared_distance_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return squared_distance_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return squared_distance_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return squared_distance_impl(_storage, get_vector_of_geo<Segment_3>(other));
    default: return unknown_squared_distance_impl(std::max(size(), other.size()));
    }
  }

  cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return distance_matrix_impl(_storage, get_vector_of_geo<Line_3>(other));
    case PLANE: return distance_matrix_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return distance_matrix_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return distance_matrix_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return distance_matrix_impl(_storage, get_vector_of_geo<Segment_3>(other));
    default: return unknown_distance_matrix_impl(size(), other.size());
    }
  }
};

typedef cpp11::external_pointer<line3> line3_p;
