#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define all(n) (n).begin(),(n).end()
#define fi first
#define se second
#define mset(x,v) memset((x),(v),sizeof(x))

typedef pair<int, int> PII;
typedef long long ll;

const int MOD = 1e9+7;
const int MAXN=1005;
// 2d Fenwick
ll t[MAXN][MAXN];
void update(ll v, int y, int x) { // switched because arrays are represented that way
	for (;x<MAXN;x+=(x&(-x))) {
		for (int y2 = y;y2<MAXN;y2+=(y2&(-y2)))
			 t[x][y2]+=v;
	}
}
ll query(int y, int x) {
	ll ret = 0;
	for (;x;x-=(x&(-x))) {
		for (int y2=y;y2;y2-=(y2&(-y2))) 
			ret+=t[x][y2];
	}
	return ret;
}
int main() {

	ios::sync_with_stdio(0);
	cin.tie(0);

	update(69,5,10);
	update(420,600,69);


	printf("%lld %lld",query(1000,1000),query(69,69));

}
