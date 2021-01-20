#include<iostream>
#include<vector>
#include<map>

using namespace std;

class Solution {
public:
    vector<int> parents;
    void Union(int x, int y)
    {
        int xp = Find(x);
        int yp = Find(y);
        int U = parents[xp] + parents[yp];
        if(xp>yp)
        {
            parents[xp] = yp;
            parents[yp] = U;
        }else
        {
            parents[yp] = xp;
            parents[xp] = U;
        }
    }

    int Find(int x)
    {
        int temp = x;
        for(temp; parents[temp]>=0; temp=parents[temp]);
        while(parents[x]>=0 && parents[x]!=temp)
        {
            int ktemp = parents[x];
            parents[x] = temp;
            x = ktemp;
        }
        return temp;
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        parents.resize(points.size(), -1);
        multimap<int, pair<int, int>, less<int>> Edges;
        for(int i=0; i<points.size(); ++i)
        {
            for(int j=i+1; j<points.size(); ++j)
            {
                Edges.insert(make_pair(abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]), make_pair(i, j)));
            }
        }
        multimap<int, pair<int, int>, less<int>>::iterator iter;
        long length=0;
        int count=0, EdgeNums = points.size()-1;
        for(iter=Edges.begin(); iter!=Edges.end(); ++iter)
        {
            if(count == EdgeNums)
            {
                break;
            }
            if(-1 == parents[iter->second.first] && -1 == parents[iter->second.second])
            {
                cout<<1<<" "<<iter->second.first<<" "<<iter->second.second<<endl;
                length += iter->first;
                parents[iter->second.second] = iter->second.first;
                parents[iter->second.first] = -2;
                ++count;
                continue;
            }
            if(-1 == parents[iter->second.first])
            {
                cout<<2<<" "<<iter->second.first<<" "<<iter->second.second<<endl;
                int p = Find(iter->second.second);
                cout<<p<<endl;
                parents[iter->second.first] = p;
                parents[p] -= 1;
            }else if(-1 == parents[iter->second.second])
            {
                cout<<3<<" "<<iter->second.first<<" "<<iter->second.second<<endl;
                int p = Find(iter->second.first);
                cout<<p<<endl;
                parents[iter->second.second] = p;
                parents[p] -= 1;
            }
            else
            {
                cout<<4<<" "<<iter->second.first<<" "<<iter->second.second<<endl;
                cout<<Find(iter->second.first)<<" "<<Find(iter->second.second)<<endl;
                int px = Find(iter->second.first);
                int py = Find(iter->second.second);
                if(px == py)
                {
                    continue;
                }else{
                    Union(px, py);
                }
            }
            length += iter->first;
            ++count;
        }
        return length;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> points = {{3,12},{2,2},{3,10},{5,2},{-17,-15}};
    cout<<s.minCostConnectPoints(points);
    return 0;
}
