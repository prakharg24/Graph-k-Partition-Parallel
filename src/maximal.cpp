#include <bits/stdc++.h>
const int MAX_N = 10000000;
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
		// int cost[ans_gp.merged_pairs.size()];
		map <int, int > cost;
		for(int j=0;j<all_grphs[ind].adj_list[first_p].size();j++){
			int node = merge[all_grphs[ind].adj_list[first_p][j].first];
			int cost_val = all_grphs[ind].adj_list[first_p][j].second;
			if(cost.find(node)==cost.end()){
				cost.insert(pair <int, int> (node,cost_val));
			}
			else{
				cost.find(node)->second += cost_val;
			}
		}

		if(second_p!=-1){
			for(int j=0;j<all_grphs[ind].adj_list[second_p].size();j++){
				int node = merge[all_grphs[ind].adj_list[second_p][j].first];
				int cost_val = all_grphs[ind].adj_list[second_p][j].second;
				if(cost.find(node)==cost.end()){
					cost.insert(pair <int, int> (node,cost_val));
				}
				else{
					cost.find(node)->second += cost_val;
				}
			}
		}
		
		vector< pair<int, int> > temp;
		map<int,int>::iterator it;
		for(it = cost.begin();it!=cost.end();++it){
			int node = it->first;
			int cost_val = it->second;
			if(node!=i){
				temp.push_back(make_pair(node,cost_val));
			}
		}
		ans_gp.adj_list.push_back(temp);
	}
	cout<<ans_gp.merged_pairs.size()<<endl;
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
		full_graph.weight_node.push_back(1);
		full_graph.merged_pairs.push_back(make_pair(i, -1));
		full_graph.adj_list.push_back(empty);
	}
	string temp;
	getline(cin, temp);
	for(int i=0;i<n;i++)
	{
		string line;
		getline( cin, line );
		istringstream is(line);
		int temp;
		while( is >> temp ) {
			full_graph.adj_list[i].push_back(make_pair(temp-1, 1));
		}
	}
	all_grphs.push_back(full_graph);
	for(int i=0;i<300;i++){
		maximal(i);
	}
	// print_graph(all_grphs[300]);
	// print_graph(all_grphs[1]);
}
