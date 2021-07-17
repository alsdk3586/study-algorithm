#include<algorithm>
#include<iostream>

using namespace std;

const int MAX = 3000000;

int arr[MAX];
int dish[3001];
//�쉶�쟾珥덈갈 踰⑦듃�뿉 �넃�씤 �젒�떆瑜� �삤瑜몄そ�쑝濡� �븳移몄뵫 �씠�룞�븯硫댁꽌 珥덈갈醫낅쪟瑜� �꽭�뼱�빞 �븯誘�濡�
//�닾�룷�씤�꽣 && �뒳�씪�씠�뵫 �쐢�룄�슦 �븣怨좊━利섏쓣 �씠�슜�븳�떎
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int N, d, k, c, left, right, cnt = 0, result = 0;
	cin >> N >> d >> k >> c;

	//�닾�룷�씤�꽣 �븣怨좊━利� �궗�슜�쓣 �쐞�븳 蹂��닔 珥덇린�솕
	left = 0, right = k - 1;

	for (int i = 0; i < N; i++)
	{
		//arr �뿉 N源뚯�� 醫낅쪟 �엯�젰諛쏆쓬
		cin >> arr[i];
	}

	for (int j = 0; j < k; j++)
	{
		//k媛쒓퉴吏� �엯�젰諛쏆쑝硫댁꽌 �빐�떦�뒪�떆�쓽 媛쒖닔 dish�뿉 �엯�젰 �떆�궡
		dish[arr[j]]++;

		//k媛쒓퉴吏��쓽 �뒪�떆 醫낅쪟 count
		if (dish[arr[j]] == 1)
			cnt++;
	}

	//蹂대꼫�뒪 �뒪�떆 怨꾩궛
	dish[c]++;
	if (dish[c] == 1)
		cnt++;

	//left媛� N蹂대떎 �옉�쓣 �븣源뚯��留� 諛섎났
	while (left < N)
	{
		//異쒕젰媛믪�� 媛�吏볦닔�쓽 理쒕뙎媛믪씠誘�濡� max怨꾩궛
		result = max(result, cnt);
		//left瑜� �븳移� �뒛由щ㈃�꽌 �쁽�옱�쐞移섏쓽 珥덈갈醫낅쪟瑜� --�떆�궓�떎.
		//留뚯빟 �젣嫄고븳 珥덈갈�씠 �쁽�옱 �븯�굹�룄 �뾾�쑝硫� cnt瑜� 1以꾩엫.
		if (--dish[arr[left++]] == 0)
			cnt--;
		//right�뒗 N蹂대떎 �겕硫� �븞�릺怨�, �궗�씠�겢�쓣 �삎�꽦 �빐�빞�븯誘�濡�,
		//right�뒗 right+1�쓣 N�쑝濡� �굹�늿 �굹癒몄��
		right = (right + 1) % N;

		//right瑜� �븳移� �뒛由고썑 異붽�� �맂 珥덈갈醫낅쪟瑜� ++�떆�궓�떎.
		//異붽���맂 珥덈갈�씠 �깉濡쒖슫 醫낅쪟�씪硫�(利� dish[]==1) cnt瑜� 1利앷���떆�궡.
		if (++dish[arr[right]] == 1)
			cnt++;
	}

	cout << result << "\n";
	return 0;
}
//deque �궗�슜
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

const int MAX = 3000000;
int N, d, k, c;
int arr[MAX];
int dish[3001] = { 0 };
deque<int> dq;

int main()
{

	//cin, cout �냽�룄�뼢�긽
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int cnt = 0, result = 0;
	cin >> N >> d >> k >> c;

	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];	//N源뚯�� �룎硫댁꽌 arr[i]�뿉 媛� �엯�젰諛쏄린
	}

	//泥ル쾲吏� �뒪�떆遺��꽣 k踰덉㎏源뚯�� �뜳�뿉 �꽔怨� �뒪�떆�쓽 醫낅쪟瑜� �꽱�떎
	for (int i = 0; i < k; i++)
	{
		dq.push_back(arr[i]);
		if (!dish[arr[i]]++)
		{
			cnt++;
		}
		result = max(result, cnt);
	}

	//�뒳�씪�씠�뵫 �쐢�룄�슦 �궗�슜
	for (int i = 0; i < N - 1; i++)
	{
		dq.pop_front();
		//�빐�떦 (dq�뿉�꽌 類�) �뒪�떆�쓽 醫낅쪟媛� �뾾�쓣 寃쎌슦(利� 0�씠硫�) cnt瑜� 類��떎
		if (!--dish[arr[i]])
			cnt--;

		//�떎�쓬 �뒪�떆((i+k)瑜� N�쑝濡� �굹�늿 �굹癒몄��)瑜� �뜳�뿉 �꽔�쓬
		dq.push_back(arr[(i + k) % N]);

		//�깉濡쒖슫 醫낅쪟�쓽 �뒪�떆�씪硫�(利� 1�씠硫�) cnt瑜� �뜑�빐以��떎
		if (!(dish[arr[(i + k) % N]])++)
			cnt++;

		//�뜳�뿉 荑좏룿�뒪�떆媛� �뾾�떎硫�
		if (!dish[c])
		{
			result = max(result, cnt + 1);
		}
		//�뜳�뿉 荑좏룿�뒪�떆媛� �엳�떎硫�
		else
			result = max(result, cnt);
	}

	cout << result << "\n";
	return 0;

}
