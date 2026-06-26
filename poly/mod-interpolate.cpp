// Reference: https://contest.ucup.ac/submission/2195950
// Lagrange interpolation modulo (prime) MOD, O(N^2) time complexity

vi interpolate(vi x, vi y, int n) {
	vi res(n), temp(n);
	rep(k,0,n-1) rep(i,k+1,n)
		y[i] = (y[i] - y[k] + MOD) * modinv(x[i] - x[k] + MOD) % MOD; // modinv can be replaced with inv
	int last = 0; temp[0] = 1;
	rep(k,0,n) rep(i,0,n) {
		res[i] += y[k] * temp[i] % MOD;
        res[i] %= MOD;
		swap(last, temp[i]);
		temp[i] -= last * x[k] % MOD;
        temp[i] = (temp[i] + MOD) % MOD;
	}
	return res;
}
