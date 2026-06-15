struct XOR3Basis {
    int K;
    vector<bool> have[3];
    vector<vector<int>> basis[3];
    XOR3Basis(int K) : K(K) {
        for (int i=1; i<=2; i++) {
            have[i].resize(K);
            basis[i].resize(K);
        }
    }
    void insert(vector<int> v) {
        for (int i=K-1; i>=0; i--) {
            if (v[i] == 0) continue;
            if (!have[v[i]][i]) {
                have[v[i]][i] = 1;
                basis[v[i]][i].resize(K);
                for (int j=0; j<K; j++) {
                    basis[v[i]][i][j] = v[j];
                }
                // cout << v[i] << " " << i << ": ";
                // print(basis[v[i]][i]);
                if (!have[3 - v[i]][i]) {
                    have[3 - v[i]][i] = 1;
                    basis[3 - v[i]][i].resize(K);
                    for (int j=0; j<K; j++) {
                        basis[3 - v[i]][i][j] = (v[j] == 0 ? 0 : 3 - v[j]);
                    }
                    // cout << 3 - v[i] << " " << i << ": ";
                    // print(basis[3 - v[i]][i]);
                }
                return;
            }
            v = sub(v, basis[v[i]][i]);
        }
    }
    bool query(vector<int> v) {
        for (int i=K-1; i>=0; i--) {
            if (v[i] == 0) continue;
            // basis[v[i]][i] must exist
            if (basis[v[i]][i].empty()) return false;
            v = sub(v, basis[v[i]][i]);
        }
        for (int i=0; i<K; i++) if (v[i] > 0) return false;
        return true;
    }
};
