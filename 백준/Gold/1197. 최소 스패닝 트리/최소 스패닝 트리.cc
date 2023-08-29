    #include <iostream>
    #include <vector>
    #include <algorithm>
    using namespace std;

    //  /*undirected, connected, weight can be negative
    //   Kruskal : greedy, select least cost edge but no cycle
    //  Prim : vertex -> select least cost edge*/

    typedef struct EDGE{
        int u, v, weight;
    } Edge;

    int N, M;
    int sum = 0;

    bool compare(const Edge& a, const Edge& b){
        return a.weight < b.weight;
    }

    int FindSet(int v, vector<int>& set){
        if(set[v] == -1){
            return v;
        }
        return set[v] = FindSet(set[v], set);
    }

    void UnionSet(int u, int v, vector<int>& set){
        int setU = FindSet(u, set);
        int setV = FindSet(v, set);
        if(setU != setV){
            set[setU] = setV;
        }
    }

    void kruskalMST(vector<Edge>& edge, int n){
        vector<int> set(n + 1, -1);

        sort(edge.begin(), edge.end(), compare);

        for(Edge i : edge){
            if(FindSet(i.u, set) != FindSet(i.v, set)){
                UnionSet(i.u, i.v, set);
                sum += i.weight;
            } 
        }
    }

    int main(){
        ios_base::sync_with_stdio(false);
        cin.tie(0), cout.tie(0);

        cin >> N >> M;
        vector<Edge> edge(M);

        for(int i = 0; i < M; i++){
            cin >> edge[i].u >> edge[i].v >> edge[i].weight;
        }

        kruskalMST(edge, N);

        cout << sum << "\n";
    }