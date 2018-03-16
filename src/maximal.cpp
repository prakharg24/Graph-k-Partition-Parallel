#include <bits/stdc++.h>
const int MAX_N = 10000000;
using namespace std;

struct Graph{
	vector<int> weight_node;
	vector< vector< pair<int, int> > > adj_list;
	vector< pair<int, int> > merged_pairs;
	vector<int> partitioned;
};

vector<Graph> all_grphs;
Graph main_graph;
int vis[MAX_N];
int merged[MAX_N];
int p[MAX_N];

void maximal(int ind){
	Graph ans_gp;
	int n = all_grphs[ind].weight_node.size();
	for(int i=0;i<n;i++)
	{
		vis[i] = 0;
		p[i] = i;
	}
	int counter = 0;
	for (int i=n; i>0; --i){
		int j = rand()%i;
		int temp = p[i];
		p[i] = p[j];
		p[j] = temp;
	}
	int rand_num = rand()%n;
	for(int it=0;it<n;it++){
		int i = p[it];
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
				merged[i] = counter;
				merged[maxind] = counter;
				ans_gp.merged_pairs.push_back(make_pair(i, maxind));
				counter++;
			}
			else{
				vis[i] = 1;
				merged[i] = counter;
				ans_gp.merged_pairs.push_back(make_pair(i, -1));
				counter++;
			}
		}
	}

	for(int i=0;i<ans_gp.merged_pairs.size();i++){
		ans_gp.partitioned.push_back(0);
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
			int node = merged[all_grphs[ind].adj_list[first_p][j].first];
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
				int node = merged[all_grphs[ind].adj_list[second_p][j].first];
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


void GGGP(int index)
{
	int n = all_grphs[index].weight_node.size();
	int gain[n];
	set <pair<int,int> > possible;
	for(int i=0;i<n;i++)
	{
		gain[i] = 0;
		for(int j=0;j<all_grphs[index].adj_list[i].size();j++)
		{
			gain[i] += all_grphs[index].adj_list[i][j].second;
		}
	}
	int total_wt_node = 0;
	int vis[n];
	for(int i=0;i<n;i++)
	{
		vis[i] = 0;
		total_wt_node += all_grphs[index].weight_node[i];
	}
	int sum_node_wt = 0;
	for(int j=0;j<n;j++)
	{
		if(sum_node_wt > (total_wt_node/2))
			break;
		if(vis[j]==0)
		{
			int curr_node = j;
			vis[curr_node] = 1;
			all_grphs[index].partitioned[curr_node] = 1;
			sum_node_wt += all_grphs[index].weight_node[curr_node];
			while(sum_node_wt < (total_wt_node /2))
			{
				for(int i=0;i<all_grphs[index].adj_list[curr_node].size();i++)
				{
					int neighbor = all_grphs[index].adj_list[curr_node][i].first;
					if(vis[neighbor]==0)
					{
						if(possible.find(make_pair(gain[neighbor],neighbor))!=possible.end())
						{
							possible.erase(make_pair(gain[neighbor],neighbor));
							gain[neighbor] += all_grphs[index].adj_list[curr_node][i].second;
							possible.insert(make_pair(gain[neighbor],neighbor));
						}
						else
						{
							gain[neighbor] = all_grphs[index].adj_list[curr_node][i].second - gain[neighbor];
							possible.insert(make_pair(gain[neighbor],neighbor));
						}
					}
				}
				if(possible.size()!=0)
				{
					curr_node = possible.rbegin()->second;
					sum_node_wt += all_grphs[index].weight_node[curr_node];
					if(sum_node_wt)
						vis[curr_node] = 1;
					possible.erase(make_pair(gain[curr_node],curr_node));
					all_grphs[index].partitioned[curr_node] = 1;
				}
				else
				{
					break;
				}
				
			}
		}
	}
}


void uncoarse(int ind){
	for(int i=0;i<all_grphs[ind].merged_pairs.size();i++){
		int first_p = all_grphs[ind].merged_pairs[i].first;
		int second_p = all_grphs[ind].merged_pairs[i].second;
		all_grphs[ind-1].partitioned[first_p] = all_grphs[ind].partitioned[i];
		if(second_p!=-1){
			all_grphs[ind-1].partitioned[second_p] = all_grphs[ind].partitioned[i];
		}
	}
	int index = ind - 1;
	set <pair <int,int> > part_f;
	set <pair <int,int> > part_s;
	vector<int> gains;
	int weight_f = 0;
	int weight_s = 0;
	vector<int> vis;
	for(int i=0;i<all_grphs[index].weight_node.size();i++)
	{
		int ie = 0;
		int ee = 0;
		for(int j=0;j<all_grphs[index].adj_list[i].size();j++)
		{
			int neighbor = all_grphs[index].adj_list[i][j].first;
			int cost = all_grphs[index].adj_list[i][j].second;
			if(all_grphs[index].partitioned[neighbor]==all_grphs[index].partitioned[i])
				ie += cost;
			else
				ee += cost;
		}
		if(all_grphs[index].partitioned[i]==0)
		{
			part_f.insert(make_pair(ee-ie,i)); // TODO add only boundary
			weight_f += all_grphs[index].weight_node[i];
		}
		else
		{
			part_s.insert(make_pair(ee-ie,i));
			weight_s += all_grphs[index].weight_node[i];
		}
		gains.push_back(ee-ie);
		vis.push_back(0);
	}
	for(int i=0;;i++) //todo
	{
		if(weight_f>weight_s)
		{
			if(part_f.size()!=0)
			{
				int curr_node = part_f.rbegin()->second;
				if(vis[curr_node]==1 || gains[curr_node]<0)
					break;
				all_grphs[index].partitioned[curr_node] = 1 - all_grphs[index].partitioned[curr_node];
				part_f.erase(make_pair(gains[curr_node],curr_node));
				weight_f -= all_grphs[index].weight_node[curr_node];
				gains[curr_node] = -1 * gains[curr_node];
				part_s.insert(make_pair(gains[curr_node],curr_node));
				weight_s += all_grphs[index].weight_node[curr_node];
				vis[curr_node] = 1;
				for(int j=0;j<all_grphs[index].adj_list[curr_node].size();j++)
				{
					int neighbor = all_grphs[index].adj_list[curr_node][j].first;
					int cost = all_grphs[index].adj_list[curr_node][j].second;
					if(all_grphs[index].partitioned[neighbor]==0)
					{
						part_f.erase(make_pair(gains[neighbor],neighbor));
						gains[neighbor] += (2*cost);
						part_f.insert(make_pair(gains[neighbor],neighbor));
					}
					else
					{
						part_s.erase(make_pair(gains[neighbor],neighbor));
						gains[neighbor] -= (2*cost);
						part_s.insert(make_pair(gains[neighbor],neighbor));
					}

				}
			}
			else
				break;

		}
		else
		{
			if(part_s.size()!=0)
			{
				int curr_node = part_s.rbegin()->second;
				if(vis[curr_node]==1 || gains[curr_node]<0)
					break;
				all_grphs[index].partitioned[curr_node] = 1 - all_grphs[index].partitioned[curr_node];
				part_s.erase(make_pair(gains[curr_node],curr_node));
				weight_s -= all_grphs[index].weight_node[curr_node];
				gains[curr_node] = -1 * gains[curr_node];
				part_f.insert(make_pair(gains[curr_node],curr_node));
				weight_f += all_grphs[index].weight_node[curr_node];
				vis[curr_node] = 1;
				for(int j=0;j<all_grphs[index].adj_list[curr_node].size();j++)
				{
					int neighbor = all_grphs[index].adj_list[curr_node][j].first;
					int cost = all_grphs[index].adj_list[curr_node][j].second;
					if(all_grphs[index].partitioned[neighbor]==1)
					{
						part_s.erase(make_pair(gains[neighbor],neighbor));
						gains[neighbor] += (2*cost);
						part_s.insert(make_pair(gains[neighbor],neighbor));
					}
					else
					{
						part_f.erase(make_pair(gains[neighbor],neighbor));
						gains[neighbor] -= (2*cost);
						part_f.insert(make_pair(gains[neighbor],neighbor));
					}

				}
			}
			else
				break;
		}
	}

}


vector<int> parts(int k,Graph g)
{
	if(k==1)
	{
		return g.partitioned;
	}
	all_grphs.clear();
	all_grphs.push_back(g);
	for(int i=0;i<50;i++){
		maximal(i);
	}
	// cout<<"yoooo"<<endl;
	GGGP(50);
	cout<<"GGGP done"<<endl;
	for(int i=0;i<50;i++){
		uncoarse(50-i);
	}
	vector<int> partitioned = all_grphs[0].partitioned;
	Graph f;
	Graph s;
	int iter_f = 0;
	int iter_s = 0;
	vector <int> mappings;
	for(int i=0;i<g.weight_node.size();i++)
	{
		if(partitioned[i]==0)
		{
			mappings.push_back(iter_f);
			iter_f++;
		}
		else
		{
			mappings.push_back(iter_s);
			iter_s++;
		}
	}
	for(int i=0;i<g.weight_node.size();i++)
	{
		if(partitioned[i]==0)
		{	
			int size_g = f.partitioned.size();
			f.partitioned.push_back(0);
			f.weight_node.push_back(g.weight_node[i]);
			f.merged_pairs.push_back(make_pair(size_g,-1));
			vector <pair <int,int> > temp;
			for(int j=0;j<g.adj_list[i].size();j++)
			{
				int neighbor = g.adj_list[i][j].first;
				int cost = g.adj_list[i][j].second;
				if(partitioned[neighbor]==0)
				{
					temp.push_back(make_pair(mappings[neighbor],cost));
				}
			}
			f.adj_list.push_back(temp);
		}
		else
		{
			int size_g = s.partitioned.size();
			s.partitioned.push_back(0);
			s.weight_node.push_back(g.weight_node[i]);
			s.merged_pairs.push_back(make_pair(size_g,-1));
			vector <pair <int,int> > temp;
			for(int j=0;j<g.adj_list[i].size();j++)
			{
				int neighbor = g.adj_list[i][j].first;
				int cost = g.adj_list[i][j].second;
				if(partitioned[neighbor]==1)
				{
					temp.push_back(make_pair(mappings[neighbor],cost));
				}
			}
			s.adj_list.push_back(temp);
		}
	}
	cout << "first graph" << iter_f<<endl;
	cout << "second graph" << iter_s<<endl;
	vector<int> partition_s = parts(k/2,s);
	vector<int> partition_f = parts(k/2,f);
	iter_f = 0;
	iter_s = 0;
	for(int i=0;i<partitioned.size();i++)
	{
		if(partitioned[i]==0)
		{
			partitioned[i] = partition_f[iter_f];
			iter_f++;
		}
		else
		{
			partitioned[i] = partition_s[iter_s] + (k/2);
			iter_s++;
		}
	}
	return partitioned;
}


int main(int argc,char ** argv)
{
	srand (static_cast <unsigned> (time(0)));
	int n,e;
	cin >> n >>e;
	Graph full_graph;
	vector< pair<int, int> > empty;
	for(int i=0;i<n;i++)
	{
		full_graph.weight_node.push_back(1);
		full_graph.partitioned.push_back(0);
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
	int prts = 8;
	int iter = 0;
	vector<int> ans = parts(prts,full_graph);
	int count[prts];
	// vector<int> ans;
	// for(int i=0;i<n;i++){
	// 	ans.push_back(iter);
	// 	iter = (iter+1)%prts;
	// }
	for(int i=0;i<prts;i++){
		count[i] = 0;
	}
	for(int i=0;i<ans.size();i++){
		count[ans[i]]++;
	}
	for(int i=0;i<prts;i++){
		cout<<count[i]<<" ";
	}
	cout<<endl;
	cout<<endl;

	int sum = 0;
	for(int i=0;i<ans.size();i++){
		for(int j=0;j<full_graph.adj_list[i].size();j++){
			if(ans[i]!=ans[full_graph.adj_list[i][j].first]){
				sum += full_graph.adj_list[i][j].second;
			}
		}
	}
	cout<<sum/2<<endl;

	// all_grphs.push_back(full_graph);
	// for(int i=0;i<30;i++){
	// 	maximal(i);
	// }
	// cout<<"maximal done"<<endl;
	// GGGP(30);
	// cout<<"GGGP done"<<endl;
	// uncoarse(30);
	// // print_graph(all_grphs[300]);
	// print_graph(all_grphs[1]);
}
