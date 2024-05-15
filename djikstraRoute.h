#ifndef DJIKSTRAROUTE_H_INCLUDED
#define DJIKSTRAROUTE_H_INCLUDED

class DjikstraRoute{
public:
    static void dijkstra(const std::vector<std::vector<std::pair<int, float>>>& graph, int src, std::vector<float>& dist, std::vector<int>& prev);
    static void printPath(int target, const std::vector<int>& prev, const std::vector<garbageLocation>& locations, routeCost::RouteCost& cost, const std::vector<float>& dist);
    static void generateDijkstraRoute(const std::vector<garbageLocation>& locations, const std::vector<std::vector<std::pair<int, float>>>& graph);
};

#endif // DJIKSTRAROUTE_H_INCLUDED
