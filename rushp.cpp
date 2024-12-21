#include "hash.h"
#include "rushp.h"

// Returns a disk ID
// replicas: Total number of replicas needed for an object across the system
// replicationFactor: Maximum number of replicas per sub-cluster
std::unordered_set< int >
RushP::rushp( int key, int replicas, const Cluster & cluster, int replicationFactor ) {
	// A list of disk IDs where replicas are placed
	std::unordered_set< int > diskIds;
	int totalWeight = cluster.weight();
	int remainingReplicas = replicas;

	// Try to place replicas in different sub-clusters
	for ( int i = 0; i < cluster.subCluster().size(); i++ ) {
		if ( remainingReplicas == 0 ) {
			// All the replicas have been placed
			break;
		}
		const SubCluster & subCluster = cluster.subCluster()[ i ];
		int numDisks = subCluster.disks();
		int startIndex = subCluster.startIndex();
		int weight = subCluster.weight();

		// Proportion of replicas for this sub-cluster
		double proportion = ( weight * 1.0 ) / totalWeight;
		int replicasToPlace = std::min( remainingReplicas, int( proportion * replicas ) );

		// Select prime p >= mj based on hash(key, current sub-cluster, 1)
		int p = selectPrime( numDisks, key, i );

		// Auxiliary variable used in the placement logic
		int auxV = key + replicasToPlace + remainingReplicas * p;

		// Case 1 : Sub-cluster has enough disks to hold all the replicas without collision
		if ( numDisks >= replicationFactor && replicasToPlace < numDisks ) {
			std::unordered_set< int > uniquePlacements;
			for ( int j = 0; j < replicasToPlace; ++j ) {
				int localIndex = ( auxV + hash( key, i, j ) ) % numDisks;
				int globalIndex = startIndex + localIndex;
				if ( uniquePlacements.find( globalIndex ) == uniquePlacements.end() ) {
					uniquePlacements.put( globalIndex );
					diskIds.put( globalIndex );
				}
			}
		// Case 2 : Sub-cluster has fewer disks than the replication factor.  Additional condition ensures
		// valid placements only
		} else if ( numDisks < replicationFactor &&
			    replicasToPlace < replicationFactor * weight &&
			    ( auxV % replicationFactor ) < numDisks ) {
			for ( int j = 0; j < replicasToPlace; ++j ) {
				int localIndex = ( auxV + hash( key, i, j ) ) % replicationFactor;
				int globalIndex = startIndex + localIndex;
				if ( diskIds.find( globalIndex ) == globalIndex.end() ) {
					diskIds.put( globalIndex );
				}
			}
		} else {
			for ( int j = 0; j < replicasToPlace; ++j ) {
				int localIndex = ( auxV + hash( key, i, j ) ) % numDisks;
				int globalIndex = startIndex + localIndex;
				if ( diskIds.find( globalIndex ) == globalIndex.end() ) {
					diskIds.put( globalIndex );
				}
			}
		}
		remainingReplicas -= replicasToPlace;
		totalWeight -= weight;
	}
	return diskIds;
}
