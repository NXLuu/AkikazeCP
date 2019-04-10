/********************************************************
*||  Code written by Akikaze                          ||*
*||  Duy-Bach Le, #Team4T's Chief Executor            ||*
*||  #Team4T Tertiary Flagship - Oblivion             ||*
*||                                                   ||*
*||  Written by a random fan of momocashew and Chiho  ||*
********************************************************/

/***********************************************
** File name: H.cpp
** Time created: Wed Apr 10 2019 09:02
***********************************************/

/************** [OPTIMIZATION PROTOCOL] **************/
#pragma GCC optimize("Ofast")
/*****************************************************/

/************** [LIBRARY PROTOCOL] **************/
#include <bits/stdc++.h>
using namespace std;
/************************************************/

/************** [GNU OMISSIONS] **************/
#define y0 withindarkness
#define y1 apinklotusbloomed
#define yn carryingapurplesoul
#define j1 togetherformingtheTeam
/*********************************************/

/************** [LEGENDS/CONSTANTS] **************/
#define endl '\n'
#define i64 long long
#define ld long double
const long long Mod = 1000000007LL, INF = 1e9, LINF = 1e18;
const long double Pi = 3.141592653589793116L;
const long double EPS = 0.000000001L, Gold = ((1.0L+sqrt(5.0L))/2.0L);
long long keymod[] = {1000000007LL, 1000000009LL, 1000000021LL, 1000000033LL};
mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
/*************************************************/

/************** [MASTER CONTROLS - PHASE 1] **************/
int OImode = 0;
int MultiTest = 1;
int Interactive = 0;

void ConfigMonitor();
char infile[] = "FILE.IN";
char outfile[] = "FILE.OUT";
/*********************************************************/

/************** [GLOBAL VARIABLES] **************/
int n, q; string s;
int tolerance[6000][6000];
/************************************************/

/************** [FUNCTIONS] **************/
int binsearch(int l, int r, int max_tol, int top, int bot) {
	int res = bot;
	while (top <= bot) {
		int mid = (top + bot) / 2;
		if (tolerance[l+mid][r-mid] <= max_tol) {
			res = mid; bot = mid - 1;
		}
		else top = mid + 1;
	}
	return res;
}

void Input() {
	cin >> s; n = s.size();
	for (int x=0; x<n; x++) {
		int y = x;
		tolerance[x][y] = abs(s[x] - s[y]);
		for (int i=1; x-i>=0 && y+i<n; i++) {
			tolerance[x-i][y+i] = tolerance[x-i+1][y+i-1] + abs(s[x-i] - s[y+i]);
		}
		if (x == n-1) continue;
		y = x + 1;
		tolerance[x][y] = abs(s[x] - s[y]);
		for (int i=1; x-i>=0 && y+i<n; i++) {
			tolerance[x-i][y+i] = tolerance[x-i+1][y+i-1] + abs(s[x-i] - s[y+i]);
		}
	}
}

void Solve() {
	cin >> q;
	while (q--) {
		int l, r, max_tol; cin >> l >> r >> max_tol; l--; r--;
		int step = binsearch(l, r, max_tol, 0, (r-l+1)/2);
		cout << (r - l + 1 - step * 2) << endl;
	}
}
/*****************************************/

/************** [MAIN] **************/
int main(int argc, char* argv[]) {
	ConfigMonitor();
	ios_base::sync_with_stdio(false);
	if (!Interactive) cin.tie(NULL);
	
	int T = 1; if (MultiTest) cin >> T;
	while(T--) {Input(); Solve();}
	
	return 0;
}
/************************************/

/************** [MASTER CONTROLS - PHASE 2] **************/
void ConfigMonitor() {
	#ifdef Akikaze
		cout << "Source code by #Team4T-Akikaze.\n";
		cout << "Input: " << ((OImode) ? infile : "stdin");
		cout << " | Output: " << ((OImode) ? outfile : "stdout") << endl << endl;
		cout << "MultiTest-Mode: " << ((MultiTest) ? "ON\n" : "OFF\n");
		cout << "Interactive-Mode: " << ((Interactive) ? "ON\n\n" : "OFF\n\n");
	#else
		if (OImode) {
			freopen(infile, "r", stdin);
			freopen(outfile, "w", stdout);
		}
	#endif
}
/*********************************************************/