#include <bits/stdc++.h>
const int MAX_N = 100000;
using namespace std;

int weight_node[MAX_N];
vector <pair<int,int> >  adj_list[MAX_N];
int n,e;
vector <int> divided_nodes;

void GGGP()
{
  int gain[n];
  set <pair<int,int> > possible;
  for(int i=0;i<n;i++)
  {
    gain[i] = 0;
    for(int j=0;j<adj_list[i].size();j++)
    {
      gain[i] += adj_list[i][j].second;
    }
  }
  int total_wt_node = 0;
  for(int i=0;i<n;i++)
  {
    total_wt_node += weight_node[i];
  }
  int sum_node_wt = 0;
  int curr_node = rand() % n;
  divided_nodes.push_back(curr_node);
  sum_node_wt += weight_node[curr_node];
  while(sum_node_wt < (total_wt_node /2))
  {
    cout << curr_node<<endl;
    for(int i=0;i<adj_list[curr_node].size();i++)
    {
      int neighbor = adj_list[curr_node][i].first;
      if(possible.find(make_pair(gain[neighbor],neighbor))!=possible.end())
      {
        possible.erase(make_pair(gain[neighbor],neighbor));
        gain[neighbor] += adj_list[curr_node][i].second;
        possible.insert(make_pair(gain[neighbor],neighbor));
      }
      else
      {
        gain[neighbor] = adj_list[curr_node][i].second - gain[neighbor];
        possible.insert(make_pair(gain[neighbor],neighbor));
      }
    }
    curr_node = possible.rbegin()->second;
    divided_nodes.push_back(curr_node);
    sum_node_wt += weight_node[curr_node];
  }
}



int main(int argc,char ** argv)
{

  cin >> n >>e;
  for(int i=0;i<n;i++)
  {
    cin >> weight_node[i];
  }
  for(int i=0;i<e;i++)
  {
    int u,v,c;
    cin >>u >>v>>c;
    u--;v--;
    adj_list[u].push_back(make_pair(u,c));
    adj_list[v].push_back(make_pair(v,c));
  }
  GGGP();

}
