/**************************************************
* Code written by Thuy-Trang Tran (thuytrang12a2) *
**************************************************/

#include<bits/stdc++.h>
#define ll long long
#define ii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
#define MOD 1000000007
using namespace std;

int main() {
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	ios_base::sync_with_stdio(0); cin.tie(NULL);
	ll n, a, b; cin >> n >> a >> b;
	for (ll i=0; i<=n/a; i++) {
		if ((n-a*i) % b == 0) {
			cout << "YES\n" << i << " " << (n - a * i) / b;
			return 0;
		}
	}
	cout << "NO";
	return 0;
}

