#include <algorithm>
#include <cstdio>
using namespace std;
const double eps = 1e-8;
int z;
double n, x1, v1, x2, v2, ans;
template <typename Tp>
int getmin(Tp &x, Tp y) { return y < x ? x = y, 1 : 0; }
double calc(double l,double p,double r)
{
    return min(p - l, r - p) + r - l;
}
double solve()
{
    double l, r, mid, ls = 1e8, rs, res=1e8;
    l = x1;
    r = x2;
    while(l+eps<=r)
    {
        mid = (l + r) / 2.0;
        ls = calc(0, x1, mid) / v1;
        rs = calc(mid, x2, n) / v2;
        getmin(res, max(ls, rs));
        if(ls<rs)
            l = mid;
        else
            r = mid;
    }
    return res;
}
int main()
{
    scanf("%d", &z);
    while(z--)
    {
        scanf("%lf%lf%lf%lf%lf", &n, &x1, &v1, &x2, &v2);
        if(x1>x2)
        {
            swap(x1, x2);
            swap(v1, v2);
        }
        ans = min(x1 + n, n + n - x1) / v1;
        getmin(ans, min(x2 + n, n + n - x2) / v2);
        getmin(ans, max((n - x1) / v1, x2 / v2));
        getmin(ans, solve());
        printf("%.10lf\n", ans);
    }
    return 0;
}