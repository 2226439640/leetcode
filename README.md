###### 并查集优化，压缩高度

```
    vector<int> parents;
    void Union(int x, int y)
    {
        int xp = Find(x);
        int yp = Find(y);
        int U = parents[xp] + parents[yp];
        if(xp>yp)                           //加权和，防止出现数的高度累积
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
        if (parents[x] < 0)
        {
            return x;
        }
        int temp = x;
        for(temp; parents[temp]>=0; temp=parents[temp]);
        while(parents[x]!=temp)                    // 压缩数的高度
        {
            int ktemp = parents[x];
            parents[x] = temp;
            x = ktemp;
        }
        return temp;
    }

```

