#include <unordered_set>

#include "cluster.h"
#include "rushp.h"

// TODO: Use namespaces in every file
int main() {
	int key = 42;
	int replicas = 5;
	int replicationFactor = 5;

	SubCluster subCluster1( 5, 0, 1 );
	SubCluster subCluster2( 10, 5, 2 );
	SubCluster subCluster3( 20, 15, 3 );

	Cluster cluster;
	cluster.addSubCluster( subCluster1 );
	cluster.addSubCluster( subCluster2 );
	cluster.addSubCluster( subCluster3 );

	RushP rushp;

	std::unordered_set< int > placements;
	placements = rushp.rushp( key, replicas, cluster, replicationFactor );

	for ( const auto & placement : placements ) {
		std::cout << placement << std::endl;
	}

	return 0;
}
