#include <bits/stdc++.h>
const int MAX_N = 100000;
using namespace std;

struct Graph{
	vector<int> weight_node;
	vector< vector< pair<int, int> > > adj_list;
	vector< pair<int, int> > merged_pairs;
};

vector<Graph> all_grphs;

void maximal(int ind){
	int n = all_grphs[ind].weight_node.size();
	int vis[n];
	for(int i=0;i<n;i++)
	{
		vis[i] = 0;
	}
	int merge[n];
	vector< pair<int, int> > merged_pairs;
	int counter = 0;
	for(int i=0;i<n;i++){
		if(vis[i]==0){
			int max = -1;
			int maxind = -1;
			int adj_num = all_grphs[ind].adj_list[i].size();
			for(int j=0;j<adj_num;j++){
				if(vis[j]==0){
					if(all_grphs[ind].adj_list[i][j].second>max){
						max = all_grphs[ind].adj_list[i][j].second;
						maxind = all_grphs[ind].adj_list[i][j].first;
					}
				}
			}
			if(maxind!=-1){
				vis[i] = 1;
				vis[maxind] = 1;
				merge[i] = counter;
				merge[maxind] = counter;
				merged_pairs.push_back(make_pair(i, maxind));
				counter++;
			}
			else{
				vis[i] = 1;
				merge[i] = counter;
				merged_pairs.push_back(make_pair(i, -1));
				counter++;
			}
		}
	}

	Graph ans_gp;
	for(int i=0;i<merged_pairs.size();i++){
		if(merged_pairs[i].second!=-1)
			ans_gp.weight_node.push_back(all_grphs[ind].weight_node[merged_pairs[i].first] + weight_node[all_grphs[ind].merged_pairs[i].second]);
		else
			ans_gp.weight_node.push_back(all_grphs[ind].weight_node[merged_pairs[i].first]);
	}
	for(int i=0;i<merged_pairs.size();i++){
		int first_p = merged_pairs[i].first;
		int second_p = merged_pairs[i].second;
		if(second_p==-1){
			vector< pair<int, int> > temp;
			for(int j=0;j<all_grphs[ind].adj_list[first_p].size();j++){
				temp.push_back(make_pair(merge[all_grphs[ind].adj_list[first_p][j].first], all_grphs[ind].adj_list[first_p][j].second));
			}
			ans_gp.adj_list.push_back(temp);
		}
		else{
			int cost[merged_pairs.size()];
			for(int j=0;j<merged_pairs.size();j++){
				cost[j] = 0;
			}
			for(int j=0;j<all_grphs[ind].adj_list[first_p].size();j++){
				cost[merge[all_grphs[ind].adj_list[first_p][j].first]] += all_grphs[ind].adj_list[first_p][j].second;
			}
			for(int j=0;j<all_grphs[ind].adj_list[second_p].size();j++){
				cost[merge[all_grphs[ind].adj_list[second_p][j].first]] += all_grphs[ind].adj_list[second_p][j].second;
			}
			vector< pair<int, int> > temp;
			for(int j=0;j<merged_pairs.size();j++){
				if(cost[j]!=0 && j!=i){
					temp.push_back(make_pair(j, cost[j]));
				}
			}
			ans_gp.adj_list.push_back(temp);
		}
	}
	all_grphs.push_back(ans_gp);
}

int main(int argc,char ** argv)
{
	int n,e;
	cin >> n >>e;
	Graph full_graph;
	vector< pair<int, int> > empty;
	for(int i=0;i<n;i++)
	{
		int temp;
		cin >> temp;
		full_graph.weight_node.push_back(temp);
		full_graph.merged_pairs.push_back(make_pair(i, -1));
		full_graph.adj_list.push_back(empty);
	}
	for(int i=0;i<e;i++)
	{
		int u,v,c;
		cin >>u >>v>>c;
		u--;v--;
		full_graph.adj_list[u].push_back(make_pair(v,c));
		full_graph.adj_list[v].push_back(make_pair(u,c));
	}
	// maximal(0);
}