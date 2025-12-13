/*
 * Author: snowysecret, adapted from KACTL
 * Description: Returns pair (p, q), such that the solution to ax = b mod n
 * is given by x = p mod q, where 0 ≤ p < q
 * returns (-1, -1) if no solution.
 * Status: tested on CF2097C
 */

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a/b * x, d;
}
pii eqn(ll a, ll b, ll n) {
  a %= n;
  b %= n;
  if (a < n) a += n;
  if (b < n) b += n;
  ll x, y;
  ll g = euclid(a, n, x, y);
  if (b % g) return {-1, -1};
  x *= (b / g);
  x %= (n / g); x += (n / g); x %= (n / g);
  return {x, n / g};
}
