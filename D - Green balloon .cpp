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
#define int ll
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
typedef vector<bool> vb;

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

const int N = 2e5 + 5; //change this
int mod1, mod2, base1, base2;
int pw1[N], inv1[N], pw2[N], inv2[N];
pair<int, int> hashing[N];
void gen_rand_mods() {
    random_device rd;
    mt19937 mt(rd());
    auto check = [](int x) {
        for (int i = 2; i * i <= x; ++i)
            if (!(x % i))return false;
        return true;
    };
    auto rnd = [&](int l, int r) {
        return uniform_int_distribution<int>(l, r)(mt);
    };
    mod1 = rnd(1e8, 2e9);
    mod2 = rnd(1e8, 2e9);
    base1 = rnd(10, 300);
    base2 = rnd(10, 300);
    while (!check(mod1))--mod1;
    while (mod1 == mod2 or !check(mod2))--mod2;
}
int add(int a, int b, int mod)
{
    int ans = a + b;
    if(ans >= mod)
        ans -= mod;
    if(ans < 0)
        ans += mod;
    return ans;
}
int mul(int a, int b, int mod)
{
    int ans = (a * 1ll * b) % mod;
    if(ans < 0)
        ans += mod;
    return ans;
}
int power(int a, int b, int mod) {
    if (b <= 0) return 1; // you may need to make it inverse
    int ret = power(mul(a, a, mod), b / 2, mod);
    if (b % 2) ret = mul(ret, a, mod);
    return ret;
}
void PreCalc() // Don't forget to call it before all the test cases
{
    gen_rand_mods();
    pw1[0] = inv1[0] = pw2[0] = inv2[0] = 1;
    int pw_inv1 = power(base1, mod1 - 2, mod1);
    int pw_inv2 = power(base2, mod2 - 2, mod2);
    for (int i = 1; i < N; ++i) {
        pw1[i] = mul(pw1[i - 1], base1, mod1);
        inv1[i] = mul(inv1[i - 1], pw_inv1, mod1);
        pw2[i] = mul(pw2[i - 1], base2, mod2);
        inv2[i] = mul(inv2[i - 1], pw_inv2, mod2);
    }
}
void BuildHash(string &s)
{
    int n = s.length();
    for (int i = 0; i < n; ++i) {
        hashing[i].first = add(((i == 0) ? 0 : hashing[i - 1].first), mul(pw1[i], s[i] - 'a' + 1, mod1), mod1);
        hashing[i].second = add(((i == 0) ? 0 : hashing[i - 1].second), mul(pw2[i], s[i] - 'a' + 1, mod2), mod2);
    }
}
pair<int, int> GetFullHash(string &s) // Get the final hash of a string not for every substring of it
{
    int n = s.length();
    pair<int, int> hash[2];
    for (int i = 0; i < n; ++i) {
        hash[i&1].first = add(((i == 0) ? 0 : hash[(i - 1)&1].first), mul(pw1[i], s[i] - 'a' + 1, mod1), mod1);
        hash[i&1].second = add(((i == 0) ? 0 : hash[(i - 1)&1].second), mul(pw2[i], s[i] - 'a' + 1, mod2), mod2);
    }
    return hash[(n-1)&1];
}
pair<int, int> GetHash(int l, int r)  // send l, r (0indexed)
{
    if(l > r)
        return {0, 0};
    pair<int, int> ans;
    ans.first = add(hashing[r].first, ((l==0)?0:-hashing[l - 1].first), mod1);
    ans.second = add(hashing[r].second, ((l==0)?0:-hashing[l - 1].second), mod2);
    ans.first = mul(ans.first, inv1[l], mod1);
    ans.second = mul(ans.second, inv2[l], mod2);
    return ans;
}

void solve()
{

    int n; cin >> n;
    string s; cin >> s;
    BuildHash(s);

    map<pair<int, int>, bool> freq;

    for (int i = 0; i <= n-2; ++i) {
        pair<int, int> h1 = GetHash(0, i - 1);
        pair<int, int> h2 = GetHash(i+2, n-1);
        int len = i;
        h2.first = mul(h2.first, pw1[len], mod1);
        h2.second = mul(h2.second, pw2[len], mod2);
        h1.first = add(h1.first, h2.first, mod1);
        h1.second = add(h1.second, h2.second, mod2);
        freq[h1] = 1;
    }

    cout << freq.size() << "\n";
}


signed main()
{

    PreCalc();
    fastIO(); fileIO();
    cout << setprecision(10) << fixed;
    int t = 1; cin >> t;

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