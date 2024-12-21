#define MAX_SUB_CLUSTERS 10

class SubCluster {
	int disks_;
	int startIndex_;
	// Assumption: Each disk in a sub-cluster has the same weight
	// TODO: Support heterogeneous disks later
	// Weight ensures that replicas are distributed proportionally and consider sub-cluster
	// specific characteristics like capacity, performance, or cost
	int weight_;

	public:
		SubCluster( int _disks, int _startIndex, int _weight ) {
			disks_ = _disks;
			startIndex_ = _startIndex;
			weight_ = _weight;
		}

		int weight() { return weight_; }
		int disks() { return disks_; }
		int startIndex() { return startIndex_; }
}

class Cluster {
	int n = 0;
	int weight_ = 0; // Total weight of all the sub-clusters
	std::vector< SubCluster > subCluster_;

	public:
		std::vector< const SubCluster & > & subCluster() { return subCluster_; }
		void addSubCluster( const SubCluster & );
		int weight() { return weight_; }
};
