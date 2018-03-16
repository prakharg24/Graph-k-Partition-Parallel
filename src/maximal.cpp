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
	Graph ans_gp;
	int n = all_grphs[ind].weight_node.size();
	int vis[n];
	for(int i=0;i<n;i++)
	{
		vis[i] = 0;
	}
	int merge[n];
	int counter = 0;
	for(int i=0;i<n;i++){
		if(vis[i]==0){
			int max = -1;
			int maxind = -1;
			int adj_num = all_grphs[ind].adj_list[i].size();
			for(int j=0;j<adj_num;j++){
				if(vis[all_grphs[ind].adj_list[i][j].first]==0){
					cout<<"ss : "<<i<<"  "<<j<<endl;
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
				ans_gp.merged_pairs.push_back(make_pair(i, maxind));
				counter++;
			}
			else{
				vis[i] = 1;
				merge[i] = counter;
				ans_gp.merged_pairs.push_back(make_pair(i, -1));
				counter++;
			}
		}
	}
	for(int i=0;i<ans_gp.merged_pairs.size();i++){
		if(ans_gp.merged_pairs[i].second!=-1)
			ans_gp.weight_node.push_back(all_grphs[ind].weight_node[ans_gp.merged_pairs[i].first] + all_grphs[ind].weight_node[ans_gp.merged_pairs[i].second]);
		else
			ans_gp.weight_node.push_back(all_grphs[ind].weight_node[ans_gp.merged_pairs[i].first]);
	}
	for(int i=0;i<ans_gp.merged_pairs.size();i++){
		int first_p = ans_gp.merged_pairs[i].first;
		int second_p = ans_gp.merged_pairs[i].second;
		int cost[ans_gp.merged_pairs.size()];
		for(int j=0;j<ans_gp.merged_pairs.size();j++){
			cost[j] = 0;
		}
		for(int j=0;j<all_grphs[ind].adj_list[first_p].size();j++){
			cost[merge[all_grphs[ind].adj_list[first_p][j].first]] += all_grphs[ind].adj_list[first_p][j].second;
		}
		if(second_p!=-1){
			for(int j=0;j<all_grphs[ind].adj_list[second_p].size();j++){
				cost[merge[all_grphs[ind].adj_list[second_p][j].first]] += all_grphs[ind].adj_list[second_p][j].second;
			}
		}
		vector< pair<int, int> > temp;
		for(int j=0;j<ans_gp.merged_pairs.size();j++){
			if(cost[j]!=0 && j!=i){
				temp.push_back(make_pair(j, cost[j]));
			}
		}
		ans_gp.adj_list.push_back(temp);
	}
	all_grphs.push_back(ans_gp);
}

void print_graph(Graph a){
	cout<<endl<<endl;
	for(int i=0;i<a.weight_node.size();i++){
		cout<<i<<"  :"<<"Weight :"<<a.weight_node[i]<<endl;
		cout<<"Edge list :"<<endl;
		for(int j=0;j<a.adj_list[i].size();j++){
			cout<<a.adj_list[i][j].first<<"  ";
		}
		cout<<endl;
		for(int j=0;j<a.adj_list[i].size();j++){
			cout<<a.adj_list[i][j].second<<"  ";
		}
		cout<<endl;
	}
	cout<<endl<<"Merging"<<endl;
	for(int i=0;i<a.merged_pairs.size();i++){
		cout<<a.merged_pairs[i].first<<"  "<<a.merged_pairs[i].second<<endl;
	}
	cout<<endl<<endl;
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
	all_grphs.push_back(full_graph);
	maximal(0);
	print_graph(all_grphs[0]);
	print_graph(all_grphs[1]);
}
