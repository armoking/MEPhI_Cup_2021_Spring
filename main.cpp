#include <bits/stdc++.h>
#define all(x) begin(x),end(x)

using namespace std;

void solveA() {
  string s;
  cin >> s;
  cout << s << '\n';
}

void solveB() {
  int n, q;
  cin >> n >> q;
  vector<int> start(n, -1);
  int maxTime = 0;
  int answer = 0;
  for (int i = 0; i < q; i++) {
    int index;
    int type;
    cin >> type >> index;
    if (type == 1) {
      start[index - 1] = i;
    } else {
      int currentTime = i - start[index - 1];
      if (currentTime >= maxTime) {
        maxTime = currentTime;
        answer = index;
      }
    }
  }
  cout << answer << ' ' << maxTime << '\n'; 
}

void solveC() {
  int n, m;
  cin >> n >> m;
  vector<string> arr(n);
  int mnx = n, mny = m, mxx = -1, mxy = -1;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    for (int j = 0; j < m; j++) {
      if (arr[i][j] == '0') {
        mnx = min(mnx, i);
        mxx = max(mxx, i);
        mny = min(mny, j);
        mxy = max(mxy, j);
      }
    }
  }
  
  bool good = mnx <= mxx && mny <= mxy;
  for (int x = mnx; x <= mxx && good; x++) {
    good &= arr[x][mny] == arr[x][mxy] && arr[x][mny] == '0';
  }
  for (int y = mny; y <= mxy && good; y++) {
    good &= arr[mnx][y] == arr[mxx][y] && arr[mnx][y] == '0';
  }
  
  cout << (good ? "YES\n" : "NO\n");
}

void solveD() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    bool good = false;
    vector<int> indexes(6);
    iota(all(indexes), 0);
    
    do {
      bool cur = true;
      
      for (int i = 0; i < 6; i++) {
        if (s[indexes[i] * 6 + i] == '0') {
          cur = false;
        }
      }
      good |= cur;
    } while (next_permutation(all(indexes)));
    
    cout << (good ? "YES\n" : "NO\n");
  }
}

void solveE() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  
  vector<vector<int>> g (n);
  
  for (int i = 0; i < n - 1; i++) {
    int f, t;
    cin >> f >> t;
    f--, t--;
    g[f].push_back(t);
    g[t].push_back(f);
  }
  
  vector<pair<int, long long>> depth(n);
  
  function<void(int, int)> Dfs = [&] (int from, int parent) {
    depth[from].first = depth[parent].first + 1;
    depth[from].second = depth[parent].second + arr[from];
    for (int to : g[from]) {
      if (to == parent) continue;
      Dfs(to, from);
    }
  };
  
  Dfs(0, 0);
  
  int root = distance(begin(depth), max_element(all(depth)));
  depth.assign(n, {0, 0ll});
  
  Dfs(root, root);
  
  cout << accumulate(all(arr), 0ll) - (*max_element(all(depth))).second << '\n';
}

void solveF() {
  int X, Y;
  cin >> X >> Y;
  int N = max(X, Y) + 1;
  vector<int> minSeive(N, 1);
  vector<int> maxSeive(N, 1);
  vector<bool> used(N, false);
  
  for (int i = 2; i < N; i++) {
    if (used[i]) continue;
    for (int j = i; j < N; j += i) {
      if (!used[j]) {
        minSeive[j] = i;
        used[j] = true;
      }
      maxSeive[j] = i;
    }
  }
  
  vector<vector<long long>> arr(X, vector<long long>(Y, 0));
  for (int x = 0; x < X; x++) {
    for (int y = 0; y < Y; y++) {
      arr[x][y] = 1ll * minSeive[x + 1] * maxSeive[y + 1];
    }
  }
  
  for (int x = 1; x < X; x++) {
    for (int y = 0; y < Y; y++) {
      arr[x][y] += arr[x - 1][y];
    }
  }
  
  for (int x = 0; x < X; x++) {
    for (int y = 1; y < Y; y++) {
      arr[x][y] += arr[x][y - 1];
    }
  }
  
  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << arr[x - 1][y - 1] << '\n';
  }
}

void solveG() {
  int n;
  cin >> n;
  vector<string> g(n);
  for (int i = 0; i < n; i++) {
    cin >> g[i];
  }
  
  vector<bool> used(n, false);
  vector<bool> matched(n, false);
  vector<int> mt(n, -1);
  
  function<bool(int)> Increment = [&] (int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
      if (g[v][i] == '0') continue;
      int nxt = i;
      if (mt[nxt] == -1) {
        matched[v] = true;
        mt[nxt] = v;
        return true;
      }
    }
    
    for (int i = 0; i < g[v].size(); i++) {
      if (g[v][i] == '0') continue;
      int nxt = i;
      if (Increment(mt[nxt])) {
        matched[v] = true;
        mt[nxt] = v;
        return true;
      }
    }
    return false;
  };
  
  int answer = 0;
  for (int run = 1; run; ) {
    run = 0;
    fill(all(used), false);
    for (int i = 0; i < n; i++) {
      if (!matched[i] && Increment(i)) {
        run = 1;
        answer++;
      }
    }
  }
  
  cout << (answer == n ? "YES\n" : "NO\n");
}

void solveH() {
  int n;
  cin >> n;
  vector<tuple<int,int,int>> arr;
  for (int x = 0; x < n; x++) {
    int y;
    cin >> y;
    arr.emplace_back(x - y, x + y, x);
  }
  sort(all(arr));

  vector<int> from(n, -1);
  vector<int> len(n, 0);
  set<pair<int,int>> st;

  for (auto& [x, y, index] : arr) {
    auto it = st.lower_bound({y, INT_MAX});
    if (it == st.begin()) {
      len[index] = 1;
    } else {
      int prevIndex = prev(it)->second;
      len[index] = len[prevIndex] + 1;
      from[index] = prevIndex;
      if (it->first == y) {
        st.erase(it);
      }
    }

    auto currentIterator = st.insert({y, index}).first;
    while (next(currentIterator) != st.end()) {
      auto nextIterator = next(currentIterator);
      if (len[nextIterator->second] <= len[index]) {
        st.erase(nextIterator);
      } else {
        break;
      }
    }
  }
  
  int v = distance(begin(len), max_element(all(len)));
  vector<int> answer;
  
  while (v != -1) {
    answer.push_back(v);
    v = from[v];
  }
  
  cout << answer.size() << '\n';
  while (answer.size()) {
    cout << answer.back() + 1 << ' ';
    answer.pop_back();
  }
  cout << '\n';
}

int main() {
  solveF();
}
