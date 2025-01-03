#include <cstdlib>
#include <iostream>

#include "cluster.h"

void
Cluster::addSubCluster( const SubCluster & subCluster ) {
	if ( n_ == MAX_SUB_CLUSTERS ) {
		std::cerr << "Reached sub-cluster limit!" << std::endl;
		exit( 1 );
	}
	subCluster_.push_back( std::move( subCluster ) );
	n_++;
	weight_ += ( subCluster.disks() * subCluster.weight() );
}
