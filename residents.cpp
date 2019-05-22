// 记录！ 大战了一个下午。。。 二分+贪心 
#include<iostream> 
#include<algorithm>
#include<cmath>
using namespace std;

// 用来保存输入 也可以认为是居住地的结构体 
struct NODE {
	int num;
	int pos;
	bool operator < (NODE other) const{
		return pos < other.pos;
	}
}*nodes;

// 居民的结构体 
struct SEG {
	int left;
	int right;
	int num;
	// 这里的排序规则为左端点小的在前 右端点远的可以后面再处理 体现贪心 因此左端点一致时右端点较近的靠前 
	bool operator < (SEG other) const{
		if(left != other.left) return left < other.left;
		else return right < other.right;
	}
}*segs;

int len;  // len不同于n，是居住地的数量 

// O(n)?
int check(long long mid, long long n, long long R){
	int preSegPos, preSegNum;
	// 坑点 有可能出现第一个居住地就是0的情况 因此要找到第一个非0的居民处 
	for(long long i = 0; i < n; i++){
		if(segs[i].num != 0){
			preSegPos = i;
			preSegNum = segs[i].num;
			break;
		}
		if(i == n-1) return 1;
	}
	// currentPos为当前居住地的位置 maxValue为check允许的最大居民数 
	int currentPos, maxValue;
	for(int i = 0; i < len; i++){
		currentPos = nodes[i].pos;
		maxValue = mid;
		// 注意这里是j <= n 因为j == n的判断语句在第一行 这样才能保证处理j == n-1的情况 
		for(int j = preSegPos; j <= n; j++){
			if(j == n) return 1;
			// 当前需要处理的居民的右端点已经无法触及时 表示调度失败 
			if(segs[j].right < currentPos) return 0;
			// 当需要处理的居民的左端点已经越过了当前的居住地 进行处理下一个居住地 
			if(segs[j].left > currentPos){
				preSegPos = j;
				preSegNum = segs[j].num;
				break;
			}
			else{
				// 使用cnt 才能正确处理上一个居民地无法完整容纳当前居民的情况 
				int cnt = (j == preSegPos)?preSegNum:segs[j].num;
				// 如果当前居民地可以完整容纳 继续处理下一个居民体 
				if(cnt <= maxValue){
					maxValue -= cnt;
				}
				// 否则容纳一部分 处理下一个居住地 
				else{
					preSegPos = j;
					preSegNum = cnt-maxValue;
					maxValue = 0;
					break;
				}
			}
		}
	}
	return 0;
}

// O(n^2)
int getResult(int n, int R){
	long long sum = 0;
	int maxValue = 0;
	for(int i = 0; i < len; i++){
		sum += nodes[i].num;
		maxValue = max(maxValue, nodes[i].num);
	}
	// 左边界是平均值 这是最理想的 
	int left = sum/n;
	// 右边界是居民的最大值 
	int right = maxValue;
	// 二分枚举 这是最大值最小化问题 
	while(left < right){
		long long mid = (left+right)/2;
		if(check(mid, n, R)){
			right = mid;
		}
		else{
			left = mid+1;
		}
	}
	return right;
}

// O(n^3)
int main(){
	int T;
	cin >> T;
	while(T--){
		len = 0;
		int n, R;
		cin >> n >> R;
		nodes = new NODE[n];
		segs = new SEG[n];
		int pos, num;
		for(int i = 0; i < n; i++){
			cin >> pos >> num;
			// 可能会出现多个输入表示同一个居住地 需要进行整合 
			if(pos == nodes[len-1].pos){
				nodes[len-1].num += num;
			}
			else{
				nodes[len].pos = pos;
				nodes[len].num = num;
				len++;
			}
			// 但是居民体就需要分开统计 
			segs[i].left = pos-R;
			segs[i].right = pos+R;
			segs[i].num = num;
		}
		sort(nodes, nodes+len);
		sort(segs, segs+n);
		int ans = getResult(n, R);
		cout << ans << endl;
		delete[] nodes;
		delete[] segs;
	}
	return 0;
}
