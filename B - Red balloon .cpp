#define _USE_MATH_DEFINES

/*
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
*/

#include <cmath>
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void fileIO(void) {

#ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#endif

}

void fastIO(void) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

}
typedef long long ll;
typedef tree<int , null_type, greater_equal<int>, rb_tree_tag, tree_order_statistics_node_update> Ordered_Set; // find_by_order : element at index i
// order_of_key  : how many elements < A
// greater<int>
// less_equal<int>, greater_equal<int> : multiset


typedef unsigned long long ull;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<int, pi> p3i;

typedef pair<ll, ll> pll;
typedef pair<ll, pll> p3ll;

typedef pair<ll, ld> plld;
typedef pair<double, pi> pd2i;

typedef vector<int> vi;
typedef vector<pi> v2i;
typedef vector<p3i> v3i;

typedef vector<ll> vll;
typedef vector<pll> v2ll;
typedef vector<p3ll> v3ll;

typedef vector<string> vs;
typedef vector<int> vb;

typedef vector<vi> vvi;
typedef vector<vll> vvl;

typedef priority_queue<int> pq_max;
typedef priority_queue<int, vi, greater<int>> pq_min;

#define loop(n)          for(int i = 0; i < (n); i++)
#define lp(x, s, e)      for(ll x = (s); x < (e); x++)
#define lpe(x, s, e)     for(ll x = (s); x <= (e); x++)

#define loop_r(n)          for(ll i = (n) - 1; i >= 0; i--)
#define lp_r(x, s, e)      for(ll x = (e) - 1; x >= (s); x--)
#define lpe_r(x, s, e)     for(ll x = (e); x >= (s); x--)

#define MP make_pair
#define PB push_back
#define EmB emplace_back
#define Em emplace
#define len(s)   (ll)s.length()
#define sz(v)    (ll)v.size()
#define all(a)   a.begin(),a.end()
#define all_r(a)   a.rbegin(),a.rend()
#define clr(x, val)    memset((x), (val), sizeof(x))
#define maxEle *max_element
#define minEle *min_element

#define tests ll t; cin >> t; ll i_t = 0; while(i_t++ < t)
#define SetPre(n, x)  cout << fixed << setprecision(n) << x

#define endl '\n'
#define kill return 0


#define ceil_i(a, b) (((ll)(a)+(ll)(b-1))/(ll)(b))
#define floor_i(a, b) (a/b)
#define round_i(a, b) ((a+(b/2))/b)

int dx_all[8] = {1, 0, -1, 0, 1, 1, -1, -1},
        dy_all[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int dx[4] = {1, 0, -1, 0},
        dy[4] = {0, 1, 0, -1};


struct Node
{
    int is_good;
    int right;
    int left;
    int lazy;
    int is_lazy;

    Node()
    {
        // update this variable to a value that has no effect on the answer of the operation
        right = 2;
        left = 3;
        lazy = is_lazy = 0;
        is_good = 1;
    }

    Node(int x)
    {
        is_good = 1;
        right = left = x;
        is_lazy = 0;
        lazy = 0;
    }

    void upd(int times)
    {
        if(times&1) {
            if(left < 2)
                left = 1 - left;
            if(right < 2)
                right = 1 - right;
        }

        lazy += times;
        is_lazy = 1;
    }
};

struct SegTree
{
    int tree_size;
    vector<Node> seg_data;
    SegTree(int n)
    {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        seg_data.resize(2 * tree_size, Node());
    }

    // update this function for the desired operation
    Node merge(Node & lf, Node & ri)
    {
        Node ans = Node();

        if(lf.is_good==1 && ri.is_good==1 && lf.right != ri.left)
            ans.is_good = 1;
        else ans.is_good = 0;

        ans.left = lf.left;
        ans.right = ri.right;

        return ans;
    }

    void init(vector<int> & nums, int ni, int lx, int rx) {

        if(rx - lx == 1)
        {
            if(lx < sz(nums))
            {
                seg_data[ni] = Node(nums[lx]);
            }
            return;
        }

        int mid = lx + (rx - lx) / 2;
        init(nums, 2 * ni + 1, lx, mid);
        init(nums, 2 * ni + 2, mid, rx);

        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2 * ni + 2]);
    }

    void init(vector<int> & nums)
    {
        init(nums, 0, 0, tree_size);
    }

    void propagete(int ni, int lx, int rx)
    {
        if(rx - lx == 1 || seg_data[ni].is_lazy == 0)
            return;

        seg_data[ 2 * ni + 1].upd(seg_data[ni].lazy);
        seg_data[ 2 * ni + 2].upd(seg_data[ni].lazy);

        seg_data[ni].is_lazy = 0;
        seg_data[ni].lazy = 0;
    }

    void set(int l, int r, int node, int lx, int rx)
    {
        propagete(node, lx, rx);

        if(lx >= l && rx <= r)
        {
            seg_data[node].upd(1);
            return;
        }
        if(rx <= l || lx >= r)
            return;

        int mid = lx + (rx - lx) / 2;
        set(l, r, 2 * node + 1, lx, mid);
        set(l, r, 2 * node + 2, mid, rx);

        seg_data[node] = merge(seg_data[2 * node + 1], seg_data[2 * node + 2]);
    }
    void set(int l, int r) // // zero indexed range and set from l to r-1, i.e [l,r)
    {
        set(l, r, 0, 0, tree_size);
    }

    Node get_range(int l, int r, int node, int lx, int rx)
    {
        propagete(node, lx, rx);

        if(lx >= l && rx <= r)
            return seg_data[node];
        if(rx <= l || lx >= r)
            return Node();

        int mid = (lx + rx) / 2;

        Node lf = get_range(l, r, 2 * node + 1, lx, mid);
        Node ri = get_range(l, r, 2 * node + 2, mid, rx);
        return merge(lf, ri);
    }

    int get_range(int l, int r) // zero indexed range and get from l to r-1, i.e [l,r)
    {
        return get_range(l, r, 0, 0, tree_size).is_good;
    }
};
void solve()
{
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = s[i]-'0';
    }

    SegTree st(n);
    st.init(data);

    while (q--) {
        int op; cin >> op;
        if(op == 1) {
            int l, r; cin >> l >> r;
            --l;
            st.set(l, r);
        }
        else {
            int l, r; cin >> l >> r;
            --l;
            cout << (st.get_range(l, r)==1?"Yes":"No") << "\n";
        }
    }

}

signed main()
{

    fastIO(); fileIO();
    cout << setprecision(10) << fixed;
    int t = 1; //cin >> t;

    for (int i = 1; i <= t; ++i)
    {
        solve();

        /*cout << solve() << endl;*/

        /*if(solve())
            cout << "YES\n";
        else
            cout << "NO\n";*/

        /*cout << "Case #" << i << ": ";*/


        /*cout << "Case #" << i << ": " << (solve() ? "YES" : "NO") << endl;*/
    }

    kill;
}