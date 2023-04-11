#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;

class segment
{
public:
  vector<ld> arr;
  ll n;

  void init(ll n)
  {
    this->n = n;
    arr.resize(4 * n, 0);
  }

  void build(vector<ld> &distance)
  {
    build(distance, 0, n - 1, 0);
    return;
  }

  void build(vector<ld> &distances, ll start, ll end, ll node)
  {
    if (start == end)
    {
      arr[node] = distances[start];
      return;
    }

    ll mid = (start + end) / 2;

    build(distances, start, mid, 2 * node + 1);
    build(distances, mid + 1, end, 2 * node + 2);

    arr[node] = min(arr[2 * node + 1], arr[2 * node + 2]);
    return;
  }

  void update(ll dist, ll ind)
  {
    update(0, n - 1, dist, ind, 0);
    return;
  }

  void update(ll start, ll end, ll dist, ll ind, ll node)
  {
    if (start == end)
    {
      arr[node] = dist;
      return;
    }

    ll mid = (start + end) / 2;

    if (mid < ind)
    {
      update(mid + 1, end, dist, ind, 2 * node + 2);
    }
    else
    {
      update(start, mid, dist, ind, 2 * node + 1);
    }

    arr[node] = min(arr[2 * node + 1], arr[2 * node + 2]);
    return;
  }

  ld query(ll left, ll right)
  {
    return (query(0, n - 1, left, right, 0));
  }

  ld query(int start, ll end, ll left, ll right, ll node)
  {
    if (start >= left && end <= right)
    {
      return arr[node];
    }

    ll mid = (start + end) / 2;

    if (mid < left)
    {
      return (query(mid + 1, end, left, right, 2 * node + 2));
    }
    else if (mid >= right)
    {
      return (query(start, mid, left, right, 2 * node + 1));
    }
    else
    {
      ld ans1 = query(start, mid, left, right, 2 * node + 1);
      ld ans2 = query(mid + 1, end, left, right, 2 * node + 2);
      return min(ans1, ans2);
    }
  }
};

void solve()
{
  segment tree;

  string target_city;
  cin >> target_city;

  ll targetx, targety;
  cin >> targetx >> targety;

  ll total_cities;
  cin >> total_cities;

  tree.init(total_cities);

  map<ld, string> cities;

  vector<ld> distances;

  for (ll i = 0; i < total_cities; i++)
  {
    string city;
    cin >> city;
    ll x, y;
    cin >> x >> y;

    ld dist = sqrt(((x - targetx) * (x - targetx)) + ((y - targety) * (y - targety)));
    cities[dist] = city;

    distances.push_back(dist);
  }

  tree.build(distances);

  ll queries;
  cin >> queries;

  while (queries--)
  {
    ll left, right;
    cin >> left >> right;
    ld ans = tree.query(left - 1, right - 1);

    cout << "In given range, the closest city from ";
    cout << target_city << " is " << cities[ans];
    cout << " at a distance of ";
    cout << ans << endl;
  }

  //  Sample input
  //   delhi
  //   0 0
  //   5
  //   mumbai
  //   4 5
  //   punjab
  //   1 2
  //   haryana
  //   3 4
  //   kolkata
  //   10 9
  //   bangalore
  //   10 8
  //   5
  //   1 5
  //   4 5
  //   1 2
  //   2 5
  //   1 3
}

int main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ll TEST_CASES = 1;
  // cin>>TEST_CASES; //comment for single test case
  while (TEST_CASES--)
  {
    solve();
  }
  return 0;
}