# Optimal meeting point (OMP) search

The mathematical formulation of the problem: 
Let us assume we have a weighted non-Euclidean connected graph G=(V, E) and V' is a subset of V.
We need to find a node(OMP) n so that for each v element of V', the distance between n and v is minimal.

Possible usages:
 - find the best location for the international conference so that the farthest participant is as close as possible,
 - find the best location for a hospital so that distance from the farthest patient is minimal,
 - find a cafe so that the last participant comes as fast as possible.

The first solution uses a nature-inspired algorithm, the Bees algorithm. It uses local and global search so it doesn't end up in local optimum.
This algorithm queries how good a node is and converges to a better solution.
Dijkstra's algorithm was used as the quality function.

Another solution was named Halfway of the farthest algorithm. 
The idea was to find some vertices of V' that are as far from each other as possible. 
The final goal was to find a point in the middle that should be the OMP.
Dijkstra was used for distance calculation and Hill climbing was used for the halfway search.
