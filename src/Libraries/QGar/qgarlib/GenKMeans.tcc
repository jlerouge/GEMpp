/*---------------------------------------------------------------------+
 | Library QgarLib, graphics analysis and recognition                  |
 | Copyright (C) 2002  Qgar Project, LORIA                             |
 |                                                                     |
 | This library is free software; you can redistribute it and/or       |
 | modify it under the terms of the GNU Lesser General Public          |
 | License version 2.1, as published by the Free Software Foundation.  |
 |                                                                     |
 | This library is distributed in the hope that it will be useful,     |
 | but WITHOUT ANY WARRANTY; without even the implied warranty of      |
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                |
 | See the GNU Lesser General Public License for more details.         |
 |                                                                     |
 | The GNU Lesser General Public License is included in the file       |
 | LICENSE.LGPL, in the root directory of the Qgar packaging. See      |
 | http://www.gnu.org/licenses/lgpl.html for the terms of the licence. |
 | To receive a paper copy, write to the Free Software Foundation,     |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       |
 |                                                                     |
 | Contact Project Qgar for any information:                           |
 |   LORIA - équipe Qgar                                               |
 |   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                |
 |   email: qgar-contact@loria.fr                                      |
 |   http://www.qgar.org/                                              |
 *---------------------------------------------------------------------*/


/**
 * @file   GenKMeans.tcc
 *
 * @brief  Implementation of function members of classes
 * qgar::GenCluster and qgar::GenKMeans.
 *
 *
 * @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Gérald Masini">Gérald Masini</a>
 * @date   January 27, 2005  21:21
 * @since  Qgar 2.2
 */



// STD
#include <algorithm>
#include <limits>
#include <list>
#include <sstream>
#include <vector>
// QGAR
#include "array.h"
#include "math.h"
#include "QgarErrorAlgorithm.h"



using namespace std;



namespace qgar
{


/*---------------------------------------------------------------------*
 |                                                                     |
 |          C  L  A  S  S      G  E  N  C  L  U  S  T  E  R            |
 |                                                                     |
 *---------------------------------------------------------------------*/


// ============
// CONSTRUCTORS
// ============

template <class T>
GenCluster<T>::GenCluster(const vector<value_type>& elements, 
			  const_reference center)

  : _center(center), 
    _elements(elements)

{
  /* EMPTY */
}


template <class T>
GenCluster<T>::GenCluster(const GenCluster<T>& other)

  : _center(other._center),
    _elements(other._elements)

{
  /* EMPTY */ 
}


// =========
// OPERATORS
// =========


template <class T>
GenCluster<T>& 
GenCluster<T>::operator=(const GenCluster<T>& rhs)
{
  if (this != &rhs) 
    {
      _center   = rhs._center;
      _elements = rhs._elements;
    }

  return *this;
}


// ======
// ACCESS
// ======


template <class T>
inline size_t
GenCluster<T>::size() const
{ 
  return _elements.size();
}


template <class T>
inline const T&
GenCluster<T>::center() const
{
  return _center;
}


template <class T>
inline const vector<T>&
GenCluster<T>::elements() const
{
  return _elements;
}


/*---------------------------------------------------------------------*
 |                                                                     |
 *---------------------------------------------------------------------*/





/*---------------------------------------------------------------------*
 |                                                                     |
 |            C  L  A  S  S      G  E  N  K  M  E  A  N  S             |
 |                                                                     |
 *---------------------------------------------------------------------*/


// ============
// CONSTRUCTORS
// ============


// CONSTRUCT A PARTITION OF A GIVEN NUMBER OF CLUSTERS,
// USING A GIVEN DISTANCE FUNCTION
// anObjVect       vector of objects to be partitioned
// aDistFunction   distance function
// aClusterCnt     number of resulting clusters

template<class T>
GenKMeans<T>::GenKMeans(const vector<T>& anObjVect,
  			DistanceFunction aDistFunction,
			int aClusterCnt)



  : _clusterCnt(aClusterCnt),
    _clusterElts(aClusterCnt),
    _distance(aDistFunction)

{
  _objVect.reserve(anObjVect.size());

  for (typename vector<T>::const_iterator it = anObjVect.begin();
       it != anObjVect.end();
       ++it)
    {
      _objVect.push_back(&(*it));
    }

  PRIVATEinitCenters();
  PRIVATEgetClusters();
}


// CONSTRUCT A PARTITION OF A GIVEN NUMBER OF CLUSTERS,
// USING A GIVEN DISTANCE FUNCTION AND GIVEN INITIAL CENTERS
// anObjVect       vector of objects to be partitioned
// aDistFunction   distance function
// aCenterVector   initial cluster centers
// aClusterCnt     number of clusters

template<class T>
GenKMeans<T>::GenKMeans(const vector<T>& anObjVect,
  			DistanceFunction aDistFunction,
			const vector<T>& aCenterVector,
			int aClusterCnt)


  : _clusterCnt(aClusterCnt),
    _clusterElts(aClusterCnt),
    _distance(aDistFunction)

{
  _objVect.reserve(anObjVect.size());

  for(unsigned int i=0; i < anObjVect.size(); ++i)
    {
      _objVect.push_back(&anObjVect[i]);
    }

  for (int idx = 0 ; idx < aClusterCnt ; ++idx)
    {
      _clusterSizes.push_back(0);                        // Cluster size
      _clusterCenters.push_back(&aCenterVector[idx]);    // Cluster center
    }
  
  PRIVATEgetClusters();
}


// ==========
// DESTRUCTOR
// ==========


template<class T>
GenKMeans<T>::~GenKMeans()
{
  // VOID
}


// ======
// ACCESS
// ======


// GET NUMBER OF RESULTING CLUSTERS

template<class T>
inline int
GenKMeans<T>::clusterCnt() const
{
  return _clusterCnt;
}


// GET VECTOR OF RESULTING CLUSTERS SIZES

template<class T>
inline const vector<int>&
GenKMeans<T>::clusterSizes() const
{
  return _clusterSizes;
}


// GET VECTOR OF RESULTING CLUSTER CENTERS

template<class T>
inline const vector<const T*>&
GenKMeans<T>::clusterCenters() const
{
  return _clusterCenters;
}


// GET THE VECTOR OF CLUSTER ELEMENTS

template<class T>
inline const vector< vector<const T*> >&
GenKMeans<T>::accessClusterElts() const
{
  return _clusterElts;
}


// GET A COPY OF THE VECTOR OF CLUSTER ELEMENTS

template<class T>
inline vector< vector<const T*> >
GenKMeans<T>::clusterElts() const
{
  return _clusterElts;
}


// GET THE VECTOR OF CLUSTERS

template<class T>
const vector< GenCluster<T> >&
GenKMeans<T>::accessClusters() const
{
  PRIVATEconsFinalClusters();
  return _clusters; 
}


// GET A COPY OF THE VECTOR OF CLUSTERS

template<class T>
vector< GenCluster<T> >
GenKMeans<T>::clusters() const
{
  PRIVATEconsFinalClusters();
  return _clusters; 
}


// ===========
// AUXILIARIES
// ===========


// INITIALIZE CLUSTER CENTERS, USING A GIVEN NUMBER
// OF THE FIRST OBJECTS FROM THE GIVEN LIST OF OBJECTS

template <class T>
void
GenKMeans<T>::PRIVATEinitCenters()



{
  typename vector<T const *>::iterator iterObjs
    = _objVect.begin();
  
  // While the expected number of clusters is not reached
  // ====================================================
  int  idx = 0;
  while (idx < _clusterCnt)
    {
      if (iterObjs == _objVect.end())
	{
	  // No more objects to get remaining centers
	  ostringstream os;
	  os << "Impossible to get given number of initial clusters: "
	     << _clusterCnt;
	  throw QgarErrorAlgorithm(__FILE__, __LINE__,
				   "template <class T> void qgar::GenKMeans<T>::PRIVATEinitCenters()",
				   os.str());
	}

      // Make sure that the current object is not very close
      // (in the sense of the distance function) to an existing center,
      // to avoid getting empty clusters after distribution of the objects
      bool sameCenter = false;
      for (int jdx = 0 ; jdx < idx ; ++jdx)
	{
	  if (qgEq0((*_distance)(*_clusterCenters[jdx], **iterObjs)))
	  {
	    sameCenter = true;
	    break;
	  }
	} // for jdx

      if (!sameCenter)
	{
	  // Record the center
	  _clusterCenters.push_back(*iterObjs);
	  // Initialize the size of the new cluster
	  _clusterSizes.push_back(0);
	  // One more cluster has been created
	  ++idx;
	}
      
      ++iterObjs;
    } // while ====================================================

} // function PRIVATEinitCenters



// DISTRIBUTE OBJECTS INTO CLUSTERS

template <class T>
void
GenKMeans<T>::PRIVATEdistributeIntoClusters()
{
  // index of the corresponding cluster
  int idxMin = 0;

  // For each object
  // ==============================================================
  for(typename vector<const T*>::const_iterator
	iterObjs = _objVect.begin();
      iterObjs != _objVect.end();
      ++iterObjs)
    {

      double distMin = numeric_limits<double>::max();
      
      // Computer the minimum distance 
      // between the current object and each center
      for(int idx = 0 ; idx < _clusterCnt ; ++idx)
	{
	  double dist = (*_distance)(**iterObjs, *_clusterCenters[idx]);
	  if (dist < distMin)
	    {
	      distMin = dist;
	      idxMin = idx;
	    }
	}
      
      // Put the current object in the right cluster
      _clusterElts[idxMin].push_back(*iterObjs);
      _clusterSizes[idxMin]++;
    } // for ======================================================

} // function PRIVATEdistributeIntoClusters



// COMPUTE CLUSTER CENTERS

template <class T>
void
GenKMeans<T>::PRIVATEgetCenters(vector<const T*>& aNewCenterVector)



{
  // For each cluster
  // ===============================================================
  for(int idxClu = 0 ; idxClu < _clusterCnt ; ++idxClu)
    {
      int sizeClu = _clusterSizes[idxClu]; // Size of the current cluster
      if (sizeClu == 0)
	{
	  throw QgarErrorAlgorithm(__FILE__, __LINE__,
				   "template <class T> void qgar::GenKMeans<T>::PRIVATEgetCenters(std::vector<const T*>&)",
				   "At least one cluster is empty");
	}
      else
	{
	  // Pointer to the current cluster
	  vector<const T*>& pClu = _clusterElts[idxClu];

	  // Table to cumulate the squared distances
	  // between the objects of the current cluster:
	  // distTab[i] = SUM distance(current object, j)
	  //              for each j in the current cluster

	  double* distTab = new double[sizeClu];
	  qgFill(distTab, sizeClu, 0.);

	  // For each object of the cluster, except the last one
	  // -------------------------------------------------------
	  for(int idxObj = 0 ; idxObj < (sizeClu - 1) ; ++idxObj)
	    {
	      // The current object
	      const T* currObj = (pClu)[idxObj];

	      // For each object of the current cluster, whose index
	      // is greater than the index of the current object

	      for(int jdxObj = idxObj + 1 ; jdxObj < sizeClu ; ++jdxObj)
		{
		  // Squared distance between current object and object `jdxObj'
		  double dist = (*_distance)(*currObj, *(pClu)[jdxObj]);
		  dist *= dist;
		  // Cumulate the distance for current object and object `jdxObj'
		  distTab[idxObj] += dist;
		  distTab[jdxObj] += dist;
		}  // for each object jdxObj

	    } // for -----------------------------------------------

	  // The new center of the cluster is the object whose index
          // corresponds to the minimum value in table `distTab'
	  aNewCenterVector[idxClu] = (pClu)[qgMinElement(distTab, sizeClu)];

	  delete [] distTab;
	}

    } // for each cluster ==========================================

} // function PRIVATEgetCenters



// LOOP ON CONSTRUCTING CLUSTERS UNTIL GETTING STABLE CENTERS

template <class T>
void
GenKMeans<T>::PRIVATEgetClusters()
{
  // New cluster centers
  vector<const T*> newCenterVector(_clusterCnt);
  
  // Loop until getting stable centers
  // ===============================================================
  while (true)
    {
      // Distribute objects into clusters
      PRIVATEdistributeIntoClusters();

      // Compute new cluster centers
      PRIVATEgetCenters(newCenterVector);

      // True when centers remain unchanged
      bool stable = true;

      // Terminate if new centers are the same as the old ones
      for(int idx = 0 ; idx < _clusterCnt ; ++idx)
	{
	  stable = stable && (_clusterCenters[idx] == newCenterVector[idx]);
	  if (!stable)
	    {
	      break;
	    }
	} // END for

      if (stable)
	{
	  break;
	}

      // For each cluster
      for(int idx = 0 ; idx < _clusterCnt ; ++idx)
	{
	  // Pointer on current cluster
	  vector<const T*>& pClu = _clusterElts[idx];

	  // Erase current cluster
	  pClu.erase(pClu.begin(), pClu.end());

	  // Re-create current cluster
	  _clusterSizes[idx] = 0;

	  // Store new center
	  _clusterCenters[idx] = newCenterVector[idx];
	}

    } // loop ======================================================

} // function PRIVATEgetClusters



// CONSTRUCT THE FINAL CLUSTERS

template <class T>
void
GenKMeans<T>::PRIVATEconsFinalClusters()
{
  // Lazy computation

  if (_clusters.empty())
    {

      for (int clusterIdx = 0; clusterIdx < _clusterCnt; ++clusterIdx) 
	{
	  vector<T> vect;
	  vect.reserve(_clusterSizes[clusterIdx]);

	  for(int eltIdx = 0; eltIdx < _clusterSizes[clusterIdx]; ++eltIdx) 
	    {
	      vect.push_back(*_clusterElts[clusterIdx][eltIdx]);
	    }

	  _clusters.push_back(GenCluster<T>(vect, *_clusterCenters[clusterIdx]));
	} // END for

    } // END if
}


/*---------------------------------------------------------------------*
 |                                                                     |
 *---------------------------------------------------------------------*/





/*---------------------------------------------------------------------*
 |                                                                     |
 |                         H  E  L  P  E  R  S                         |
 |                                                                     |
 *---------------------------------------------------------------------*/


// CONSTRUCT A PARTITION OF CLUSTERS USING A DISTANCE FUNCTION

template <class T>
vector< GenCluster<T> > 
qgKMeans(const vector<T>& anObjVect,
	 double (*aDistFunction)(const T&, const T&),
	 int aClusterCnt)

  throw (QgarErrorAlgorithm)

{
  return (GenKMeans<T>(anObjVect, aDistFunction, aClusterCnt)).clusters();
}


// CONSTRUCT A PARTITION OF CLUSTERS OF GIVEN CENTERS,
// USING A DISTANCE FUNCTION

template <class T>
vector< GenCluster<T> >
qgKMeans(const vector<T>& anObjVect,
	 double (*aDistFunction) (const T&, const T&),
	 vector<T*>& aCenterVector,
	 int aClusterCnt)

  throw (QgarErrorAlgorithm)

{
  return
    (GenKMeans<T>(anObjVect, aDistFunction, aCenterVector, aClusterCnt)).clusters();
}


/*---------------------------------------------------------------------*
 |                                                                     |
 *---------------------------------------------------------------------*/


} // namespace qgar
