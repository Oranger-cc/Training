#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const double pi = acos(-1.0);
template <typename Tp>
int getmin(Tp &x, Tp y) { return y < x ? x = y, 1 : 0; }
template <typename Tp>
int getmax(Tp &x, Tp y) { return y > x ? x = y, 1 : 0; }
template <typename Tp>
void read(Tp &x)
{
	x = 0;
	char ch = getchar();
	int f = 0;
	while (ch != '-' && (ch < '0' || ch > '9'))
		ch = getchar();
	if (ch == '-')
		f = 1, ch = getchar();
	while ('0' <= ch && ch <= '9')
		x = x * 10 + ch - '0', ch = getchar();
	if (f)
		x = -x;
}
int main()
{
	int n, m;
	double ans = 0.0, cur;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
		{
			//j<i *2
			cur = 0.0;
			for (int r = 1; r < m; r++)
			{
				if (r * pi < 2.0 * m)
					cur += (i - j) * m + j * r * pi;
				else
					cur += (i + j) * m;
			}
			cur *= 2;
			cur += (i - j) * m; //r=0
			cur += (i + j) * m; //r=m
			if (j < i) cur *= 2;
			ans += cur;
		}
	if(m != 1) ans += n * (n + 1) * m;
	printf("%.10lf\n", ans);
	return 0;
}
