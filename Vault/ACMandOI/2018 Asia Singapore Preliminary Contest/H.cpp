/**********************************************************
 *     Code written by Akikaze                            *
 *     Duy-Bach Le, #Team4T's Chief Executor              *
 *     #Team4T Tertiary Flagship - Oblivion               *
 *                                                        *
 *     Written by a random fan of momocashew and Chiho    *
 *                                                        *
 *     Arigatougozaimasu, imouto-chan.                    *
 **********************************************************/

/************** [OPTIMIZATION PROTOCOL] **************/
#pragma comment(linker, "/stack:227420978")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
/*****************************************************/

/************** [LIBRARY PROTOCOL] **************/
#include <bits/stdc++.h>
using namespace std;
/************************************************/

/************** [LEGENDS/CONSTANTS] **************/
#define endl '\n'
#define i64 long long
#define ld long double
#define rsz resize
#define pub push_back
#define mp make_pair
#define fi first
#define se second
typedef vector<i64> vi;
typedef vector<ld> vd;
typedef vector<string> vs;
typedef vector<char> vc;
typedef vector<bool> vb;
typedef pair<i64, i64> pii;
typedef pair<i64, pii> pip;
typedef pair<pii, i64> ppi;
const long long Mod = 1000000007LL, INF = 1e9, LINF = 1e18;
const long double PI = 3.141592653589793116, EPS = 1e-9, GOLD = ((1+sqrt(5))/2);
i64 keymod[] = {1000000007LL, 1000000009LL, 1000000021LL, 1000000033LL};
i64 keyCount = sizeof(keymod) / sizeof(i64);
/*************************************************/

/************** [BITWISE FUNCTIONS] **************/
template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcount(s); }
/*************************************************/

/************** [MASTER CONTROLS - PHASE 1] **************/
auto TimeStart = chrono::steady_clock::now();
auto TimeEnd = chrono::steady_clock::now();
#define OImode 227420978
#define MultiTest 227420978

#undef OImode // Switch this off if submitting OI problems.
#undef MultiTest // Switch this off if submitting multi-test problems.

void ControlIO(int argc, char* argv[]);
void TimerStart();
void TimerStop();
void Exit();
/*********************************************************/

/************** [GLOBAL VARIABLES] **************/
i64 R, K, N, ans; vb vis; vi A, maxLine;
vector<pii> coor; map<pii, i64> Map;
vector<vb> eliminated;
/************************************************/

/************** [FUNCTIONS] **************/
void CalculateCoordinates() {
	i64 Line = 1, Size = R, Start = 1; maxLine[1] = R;
	for (i64 i=1; i<=N; i++) {
		if (i == Start + Size) {
			Line++; Start = i;
			if (Line <= R) Size++; else Size--;
			maxLine[Line] = Size;
		}
		i64 Col = i - Start + 1;
		coor[i] = mp(Line, Col);
		Map[coor[i]] = i;
	}
}

void RemoveAdjacent() {
	for (i64 i=0; i<K; i++) {
		for (i64 j=i+1; j<K; j++) {
			i64 x = A[i], y = A[j];
			if (x > y) swap(x, y);
			pii a = coor[x], b = coor[y];
			if (a.fi == b.fi && a.se + 1 == b.se) {
				eliminated[x][3] = true;
				eliminated[y][6] = true;
			}
			if (a.fi + 1 == b.fi && a.se - (a.fi >= R) == b.se) {
				eliminated[x][4] = true;
				eliminated[y][1] = true;
			}
			if (a.fi + 1 == b.fi && a.se + 1 - (a.fi >= R) == b.se) {
				eliminated[x][5] = true;
				eliminated[y][2] = true;
			}
		}
	}
}

void RemoveInner() {
	queue<i64> Q;
	for (i64 i=1; i<=N; i++) {
		if (vis[i]) continue;
		pii z = coor[i];
		if (z.fi == 1 || z.fi == R * 2 - 1 || z.se == 1 || z.se == maxLine[z.fi]) {
			Q.push(i); vis[i] = true;
		}
	}
	while (!Q.empty()) {
		i64 z = Q.front(); Q.pop();
		pii a = coor[z];
		if (Map.find(mp(a.fi, a.se+1)) != Map.end()) {
			i64 z = Map[mp(a.fi, a.se+1)];
			if (!vis[z]) {vis[z] = true; Q.push(z);}
		}
		if (Map.find(mp(a.fi-1, a.se+(a.fi > R))) != Map.end()) {
			i64 z = Map[mp(a.fi-1, a.se+(a.fi > R))];
			if (!vis[z]) {vis[z] = true; Q.push(z);}
		}
		if (Map.find(mp(a.fi-1, a.se-1+(a.fi > R))) != Map.end()) {
			i64 z = Map[mp(a.fi-1, a.se-1+(a.fi > R))];
			if (!vis[z]) {vis[z] = true; Q.push(z);}
		}
		if (Map.find(mp(a.fi, a.se-1)) != Map.end()) {
			i64 z = Map[mp(a.fi, a.se-1)];
			if (!vis[z]) {vis[z] = true; Q.push(z);}
		}
		if (Map.find(mp(a.fi+1, a.se-(a.fi >= R))) != Map.end()) {
			i64 z = Map[mp(a.fi+1, a.se-(a.fi >= R))];
			if (!vis[z]) {vis[z] = true; Q.push(z);}
		}
		if (Map.find(mp(a.fi+1, a.se+1-(a.fi >= R))) != Map.end()) {
			i64 z = Map[mp(a.fi+1, a.se+1-(a.fi >= R))];
			if (!vis[z]) {vis[z] = true; Q.push(z);}
		}
	}
	for (i64 q=1; q<=N; q++) {
		if (vis[q]) continue;
		for (i64 i=0; i<K; i++) {
			i64 x = q, y = A[i];
			bool swapped = false;
			if (x > y) {swap(x, y); swapped = true;}
			pii a = coor[x], b = coor[y];
			if (a.fi == b.fi && a.se + 1 == b.se) {
				if (swapped) eliminated[x][3] = true;
				else eliminated[y][6] = true;
			}
			if (a.fi + 1 == b.fi && a.se - (a.fi >= R) == b.se) {
				if (swapped) eliminated[x][4] = true;
				else eliminated[y][1] = true;
			}
			if (a.fi + 1 == b.fi && a.se + 1 - (a.fi >= R) == b.se) {
				if (swapped) eliminated[x][5] = true;
				else eliminated[y][2] = true;
			}
		}
	}
}

void Input() {
	cin >> R >> K; N = R * R * R - (R - 1) * (R - 1) * (R - 1);
	vis.rsz(N+1, false); coor.rsz(N+1); A.rsz(K); maxLine.rsz(R*2, 0); ans = K * 6;
	eliminated.resize(N+1, vb(7, false));
	for (i64 i=0; i<K; i++) {cin >> A[i]; vis[A[i]] = true;}
}

void Solve() {
	CalculateCoordinates();
	RemoveAdjacent();
	RemoveInner();
	for (i64 i=1; i<=N; i++) {
		for (i64 j=1; j<=6; j++) {
			ans -= eliminated[i][j];
		}
	}
	cout << ans;
}
/*****************************************/

/************** [MAIN] **************/
int main(int argc, char* argv[]) {
	//ios_base::sync_with_stdio(0); cin.tie(NULL);
	ControlIO(argc, argv);
	#ifndef MultiTest
		Input(); TimerStart();
		Solve(); TimerStop();
	#else
		int T; cin >> T; TimerStart();
		while(T--) {Input(); Solve();}
		TimerStop();
	#endif
	return 0;
}
/************************************/

/************** [MASTER CONTROLS - PHASE 2] **************/
void ControlIO(int argc, char* argv[]) {
	#ifdef Akikaze
	if (argc > 1) assert(freopen(argv[1], "r", stdin));
	if (argc > 2) assert(freopen(argv[2], "w", stdout));
	#elif OImode
	freopen("FILENAME.INP", "r", stdin);
	freopen("FILENAME.OUT", "w", stdout);
	#endif
}

void TimerStart() {
	#ifdef Akikaze
	TimeStart = chrono::steady_clock::now();
	#endif
}

void TimerStop() {
	#ifdef Akikaze
	TimeEnd = chrono::steady_clock::now();
	auto ElapsedTime = TimeEnd - TimeStart;
	cout << "\n\nTime elapsed: " << chrono::duration<double>(ElapsedTime).count() << " seconds.\n";
	#endif
}

void Exit() {
	TimerStop(); exit(0);
}
/*********************************************************/

/**********************************************************
 *             Watashi no sekai, kimi ga iru yo           *
 **********************************************************/