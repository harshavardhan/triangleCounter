#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr(i,a,b) for(ll i=a;i <= b;i++)
#define rep(i,n) for(ll i=0;i<n;i++)
#define sz(x) x.size()
#define pll pair<ll,ll>
#define mp make_pair
#define pb push_back

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
 
namespace std
{
  template<typename S, typename T> struct hash<pair<S, T>>
  {
    inline size_t operator()(const pair<S, T> & v) const
    {
      size_t seed = 0;
      ::hash_combine(seed, v.first);
      ::hash_combine(seed, v.second);
      return seed;
    }
  };
}

ll n,m;
vector<vector<ll> > edg;
bool * isHeavy;
unordered_map<pll,ll> pres;
 
ll numTri() {
	ll cnt = 0;
	ll tem = sqrt(m)+1;
	vector<ll> heavy;
	fr(i,0,n-1) {
		if(sz(edg[i]) >= tem) {
			isHeavy[i] = true;
			heavy.pb(i);
		}
	}
	ll tem1 = 0,tem2 = 0,tem3 = 0,tem4 = 0;
	fr(i,0,n-1) {
		rep(j,sz(edg[i])) {
			if(isHeavy[i] and isHeavy[edg[i][j]]) {
				rep(k,sz(heavy)) {
					if( pres.count(mp(i,heavy[k])) != 0 and pres.count(mp(edg[i][j],heavy[k])) != 0 ) tem1 += 1; 
				}
			}
		}
	}
	tem1 /= 6;
	rep(k,sz(heavy)) {
		fr(i,0,n-1) {
			rep(j,sz(edg[i])) {
				ll st = 0;
				st += isHeavy[i]; st += isHeavy[edg[i][j]];
				if(st == 1) {
					if( pres.count(mp(i,heavy[k])) != 0 and pres.count(mp(edg[i][j],heavy[k])) != 0 ) tem2 += 1;	
				}
				else if(st == 0) {
					if( pres.count(mp(i,heavy[k])) != 0 and pres.count(mp(edg[i][j],heavy[k])) != 0 ) tem3 += 1;
				}
			}
		}		
	}
	tem2 /= 4;
	tem3 /= 2;
	fr(i,0,n-1) {
		rep(j,sz(edg[i])) {
			ll oth = edg[i][j];
			if(!isHeavy[i] and !isHeavy[oth]) {
				rep(y,sz(edg[i])) {
					if(!isHeavy[edg[i][y]] and edg[i][y] != oth) {
						ll nex = edg[i][y];
						if(pres.count(mp(oth,nex)) != 0) {
							tem4 += 1;
						}
					} 
				}
			}
		}
	}
	tem4 /= 6;
	cnt = tem1 + tem2 + tem3 + tem4; 
	return cnt;
}

int main() {
	cin >> n >> m;
	fr(i,0,n-1) {
		vector<ll> temp;
		edg.pb(temp);
	}
	isHeavy = (bool *) malloc(n * sizeof(bool));
	fr(i,0,n-1) isHeavy[i] = false;
	fr(j,1,m) {
		ll u,v; cin >> u >> v;
		edg[u].pb(v); edg[v].pb(u);
		pres[mp(u,v)] = 1; pres[mp(v,u)] = 1;
	}
	const clock_t begin_time = clock();
	cout << numTri() << "\n";
	const clock_t end_time = clock();
	cout << "Time taken " << float(end_time - begin_time)/CLOCKS_PER_SEC << "seconds" << endl;
}