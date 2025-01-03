#include <cstdlib>
#include <iostream>

#include "cluster.h"

void
Cluster::addSubCluster( const SubCluster & subCluster ) {
	if ( n_ == MAX_SUB_CLUSTERS ) {
		std::cerr << "Reached sub-cluster limit!" << std::endl;
		exit( 1 );
	}
	subCluster_[ n_++ ] = std::move( subCluster );
	weight_ += ( subCluster.disks() * subCluster.weight() );
}
