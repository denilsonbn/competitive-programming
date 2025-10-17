#include <bits/stdc++.h>

using namespace std;

vector<int> nums;
vector<int> nums_in;
vector<int> seg;
vector<int> prefix;
vector<int> suf;

void build(int k, int l, int r) {
    if (l == r) {
        seg[k] = nums_in[l];
        return;
    }

    int m = (l + r) / 2;

    build(k*2, l, m);
    build(k*2+1, m+1, r);

    seg[k] = min(seg[k*2], seg[k*2+1]);
}

int query(int a, int b, int l, int r, int k = 1) {
    if (l >= a && r <= b) return seg[k];
    if (l > b || r < a) return INT_MAX;

    int m = (r + l) / 2;

    return min(query(a, b, l, m, k*2), query(a, b, m+1, r, k*2+1));
}

void pr(int n) {

    prefix[0] = nums[0];

    for (int i = 1; i < n; i++) {
        prefix[i] = min(prefix[i-1], nums[i]);
    }

}

void su(int n) {

    suf[n-1] = nums[n-1];

    for (int i = n - 2; i >= 0; i--) {
        suf[i] = min(suf[i+1], nums[i]);
    }
}

int main() {

    cin.tie(0)->ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    nums.resize(n);
    nums_in.resize(n);
    seg.resize(4*n);
    prefix.resize(n);
    suf.resize(n);

    for (int i = 0; i < n; i++) cin >> nums[i];

    for (int i = 0; i < n; i++) {
        nums_in[i] = nums[i] + i;
    }

    build(1, 0, n-1);
    pr(n);
    su(n);

    int ans = 0;

    for (int l = 0, r = 0; r < n;) {
        if (r - l + 1 <= k) {
            int a = l == 0 ? INT_MAX : prefix[l - 1];
            int c = r == n - 1 ? INT_MAX : suf[r + 1];
            int b = query(l, r, 0, n-1);
            //cout << "b: " << b << "\n";
            b = (nums[r] + k) - nums_in[r] + b;
            int curr = min(min(a, c), b);
            ans = max(curr, ans);
            r++;
            //cout << a << " " << b << " " << c << "\n";
        }
        else {
            l++;
        }
    }

    cout << ans << "\n";

    return 0;
}

// a[i] = a[i] + i;
