#include <unordered_set>
#include <utility>
#include <vector>

#include "cluster.h"

class RushP {
	public:
		// Returns a disk ID
		std::unordered_set< int > rushp( int, int, const Cluster & );
		// TODO: Allow modifying the number of disks and weight in a sub-cluster
};

