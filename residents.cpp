// ��¼�� ��ս��һ�����硣���� ����+̰�� 
#include<iostream> 
#include<algorithm>
#include<cmath>
using namespace std;

// ������������ Ҳ������Ϊ�Ǿ�ס�صĽṹ�� 
struct NODE {
	int num;
	int pos;
	bool operator < (NODE other) const{
		return pos < other.pos;
	}
}*nodes;

// ����Ľṹ�� 
struct SEG {
	int left;
	int right;
	int num;
	// ������������Ϊ��˵�С����ǰ �Ҷ˵�Զ�Ŀ��Ժ����ٴ��� ����̰�� �����˵�һ��ʱ�Ҷ˵�Ͻ��Ŀ�ǰ 
	bool operator < (SEG other) const{
		if(left != other.left) return left < other.left;
		else return right < other.right;
	}
}*segs;

int len;  // len��ͬ��n���Ǿ�ס�ص����� 

// O(n)?
int check(long long mid, long long n, long long R){
	int preSegPos, preSegNum;
	// �ӵ� �п��ܳ��ֵ�һ����ס�ؾ���0����� ���Ҫ�ҵ���һ����0�ľ��� 
	for(long long i = 0; i < n; i++){
		if(segs[i].num != 0){
			preSegPos = i;
			preSegNum = segs[i].num;
			break;
		}
		if(i == n-1) return 1;
	}
	// currentPosΪ��ǰ��ס�ص�λ�� maxValueΪcheck������������� 
	int currentPos, maxValue;
	for(int i = 0; i < len; i++){
		currentPos = nodes[i].pos;
		maxValue = mid;
		// ע��������j <= n ��Ϊj == n���ж�����ڵ�һ�� �������ܱ�֤����j == n-1����� 
		for(int j = preSegPos; j <= n; j++){
			if(j == n) return 1;
			// ��ǰ��Ҫ����ľ�����Ҷ˵��Ѿ��޷�����ʱ ��ʾ����ʧ�� 
			if(segs[j].right < currentPos) return 0;
			// ����Ҫ����ľ������˵��Ѿ�Խ���˵�ǰ�ľ�ס�� ���д�����һ����ס�� 
			if(segs[j].left > currentPos){
				preSegPos = j;
				preSegNum = segs[j].num;
				break;
			}
			else{
				// ʹ��cnt ������ȷ������һ��������޷��������ɵ�ǰ�������� 
				int cnt = (j == preSegPos)?preSegNum:segs[j].num;
				// �����ǰ����ؿ����������� ����������һ�������� 
				if(cnt <= maxValue){
					maxValue -= cnt;
				}
				// ��������һ���� ������һ����ס�� 
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
	// ��߽���ƽ��ֵ ����������� 
	int left = sum/n;
	// �ұ߽��Ǿ�������ֵ 
	int right = maxValue;
	// ����ö�� �������ֵ��С������ 
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
			// ���ܻ���ֶ�������ʾͬһ����ס�� ��Ҫ�������� 
			if(pos == nodes[len-1].pos){
				nodes[len-1].num += num;
			}
			else{
				nodes[len].pos = pos;
				nodes[len].num = num;
				len++;
			}
			// ���Ǿ��������Ҫ�ֿ�ͳ�� 
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
