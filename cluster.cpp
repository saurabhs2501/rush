#include <cstdlib>

#include "cluster.h"

void
Cluster::addSubCluster( const SubCluster & subCluster ) {
	if ( n == MAX_SUB_CLUSTERS ) {
		std::cerr << "Reached sub-cluster limit!" << std::endl;
		exit( 1 );
	}
	subCluster[ i++ ] = std::move( subCluster );
	weight_ += ( subCluster.disks() * subCluster.weight() );
}
