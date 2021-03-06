// Spheres.hpp
// Data representation for the big set of spheres (a.k.a. disks) generated by the algorithms

// Copyright 2016 Sandia Corporation. Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains certain rights in this software.
// SCR#:2084.0

#ifndef SPHERES
#define SPHERES

#include "Point_Tool.hpp"
#include <iostream>
#include "Domain.hpp"

class Ghost_Spheres;

class Spheres
{
public:

  Spheres(Domain &domain)
  : _max_num_spheres(0), _num_spheres(0), _pt(domain.num_dim()), _sphere_array(0), _domain(domain)
  {}
  Spheres(size_t max_num_spheres, Domain &domain)
  : _max_num_spheres(max_num_spheres), _num_spheres(0), _pt(domain.num_dim()), _sphere_array(0), _domain(domain)
  {
    new_sphere_array(max_num_spheres);
  }

  void new_sphere_array(size_t max_num_spheres)
  {
    _max_num_spheres = max_num_spheres;
    delete [] _sphere_array;
    if (_max_num_spheres)
      _sphere_array = new double*[_max_num_spheres];
    else
      _sphere_array = 0;
    _num_spheres = 0;
    std::cout << " creating space for spheres: " << max_num_spheres << std::endl;
  }


  virtual ~Spheres()
  {
    for (size_t i = 0; i < _num_spheres; ++i)
      _pt.delete_sphere( _sphere_array[i] );
    delete [] _sphere_array;
    _sphere_array = 0;
  }
  
  double radius( size_t i )
  {
    assert( is_valid_sphere(i) );
    return _pt.radius( _sphere_array[i] );
  }

  // return the index of the sphere with the passed in coordinates,
  // not virtual, but the called function is
  size_t add_sphere(const double *sphere)
  {
    size_t real_index;
    return add_sphere(sphere, real_index);
  }
  // also return the index of the "real" non-ghost copy of it, which might be the same.
  virtual size_t add_sphere(const double *sphere, size_t &real_index)
  {
    // for plain Spheres, there is no ghosting.
    real_index = add_real_sphere_to_array(sphere);
    return real_index;
  }
  
  virtual bool remove_sphere(size_t &i)
  {
//    assert(i < max_num_spheres());
    if (i == bad_sphere_index())
      return false;

    assert(i < _num_spheres);
    // move the last sphere into the current sphere
    // reduce the number of spheres by one
    // no need to do special checks if i == _num_spheres-1, etc
    double *removed_sphere = _sphere_array[i];
    _sphere_array[i] = _sphere_array[--_num_spheres];
    _pt.delete_sphere(removed_sphere);
    if ( i == _num_spheres )
      i = bad_sphere_index();
    // otherwise leave i alone, as it was replaced by a later sphere
    return true;
  }

  // spheres[i]
  //
  // rvalue access only through operator []
  // double *sphere = spheres[3];
  const double* operator[](size_t i) const
  {
    //assert(i<_num_spheres); only holds for non-ghosted nodes
    assert(i<max_num_spheres());
    return _sphere_array[i];
  };

  size_t max_num_spheres() const { return _max_num_spheres; }

  virtual size_t size() const { return _num_spheres; }
  size_t num_real_spheres() const { return _num_spheres; }

  // callers can use this, but shouldn't change the dimension
  Point_Tool _pt;

  size_t num_dim() const { return _pt.num_dim(); }

  const size_t last_disk() const { return _num_spheres-1; }
  static size_t bad_sphere_index() {return size_t(-1);}
  virtual bool is_valid_sphere( size_t i ) const { return i < size(); }
  virtual bool is_valid_index( size_t i ) const { return i < max_num_spheres(); }

  // currently there is no mechanism for deleting an individual sphere, or replacing it

  const Domain &domain() const {return _domain;}

  // For use by Ghost_Global_Container
  // is this a Spheres or a Ghost_Spheres?
  friend class Ghost_Global_Container;
  friend class Global_Container;
  virtual bool is_ghost() const {return false;}
  // is this particular spheres a ghost?
  virtual bool is_ghost(size_t i) const {return false;}
  // cast this to a Ghost_Spheres
  virtual Ghost_Spheres* cast_to_ghost() const {return 0;}
  virtual const Ghost_Spheres* cast_to_const_ghost() const {return 0;}

protected:
  
  Domain &_domain;

 
  // mechanics of adding the sphere to the end of the array
  size_t add_real_sphere_to_array(const double *sphere)
  {
    
    assert( _num_spheres < _max_num_spheres );
    if ( _num_spheres >= _max_num_spheres )
    {
      std::cout << "Error Spheres::_sphere_array exhausted." << std::endl;
      return bad_sphere_index();
    }
    
    // should be in the domain box, within roundoff
    assert( domain().in_bounds_tol( sphere ) );
    
    double *s = _pt.new_copy_sphere( sphere );
    _sphere_array[_num_spheres] = s;
    return _num_spheres++; // return old number of spheres as the index of the current sphere
  };


  // data
protected:
  double** _sphere_array;
  size_t _num_spheres;
  size_t _max_num_spheres; // array size

};

#endif