// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_UGGRIDLEVELITERATOR_HH
#define DUNE_UGGRIDLEVELITERATOR_HH

/** \file
 * \brief The UGGridLevelIterator class and its specializations
 */

namespace Dune {

  // Forward declaration
  template <int codim, PartitionIteratorType PiType, class GridImp>
  class UGGridLevelIteratorFactory;

  //**********************************************************************
  //
  // --UGGridLevelIterator
  // --LevelIterator
  /** \brief Iterator over all entities of a given codimension and level of a grid.
   * \ingroup UGGrid
   */
  template<int codim, PartitionIteratorType pitype, class GridImp>
  class UGGridLevelIterator :
    public LevelIteratorDefault <codim,pitype,GridImp,UGGridLevelIterator>
  {
    friend class UGGridEntity<codim,GridImp::dimension,GridImp>;
    friend class UGGridEntity<0,    GridImp::dimension,GridImp>;

    template <int codim_, PartitionIteratorType PiType_, class GridImp_>
    friend class UGGridLevelIteratorFactory;

  public:

    typedef typename GridImp::template codim<codim>::Entity Entity;

    //! Constructor
    explicit UGGridLevelIterator(int travLevel);

    //! prefix increment
    void increment();

    //! equality
    bool equals(const UGGridLevelIterator<codim,pitype,GridImp>& i) const;

    //! dereferencing
    Entity& dereference() const;

    //! ask for level of entity
    int level ();

  private:

    void makeIterator();

    void setToTarget(typename TargetType<codim,GridImp::dimension>::T* target) {
      target_ = target;
      virtualEntity_.setToTarget(target);
    }

    void setToTarget(typename TargetType<codim,GridImp::dimension>::T* target, int level) {
      target_ = target;
      level_  = level;
      virtualEntity_.setToTarget(target, level);
    }

    // private Members
    mutable UGMakeableEntity<codim,GridImp::dimension,GridImp> virtualEntity_;

    //! element number
    int elNum_;

    //! level
    int level_;

    typename TargetType<codim,GridImp::dimension>::T* target_;

  };

  // Include method definitions
#include "uggridleveliterator.cc"

}  // namespace Dune

#endif
