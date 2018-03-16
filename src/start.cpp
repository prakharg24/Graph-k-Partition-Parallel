#include <bits/stdc++.h>
MAX_N = 100000
using namespace std;

int weight_node[MAX_N];
vector <pair<int,int> >  adj_list[MAX_N];

int main(int argc,char ** argv)
{
  int n,e;
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
    adj_list[u].push_back(make_pair(v,c));
    adj_list[v].push_back(make_pair(u,c));
  }
}
