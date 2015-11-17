#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
vector<int> p;

// [min, max)
static int seed = time(NULL);
int get_random_num (int min, int max) {
	srand(seed);
	seed = rand();
	return (rand()%(max-min)) + min;
}

static unsigned seed_mt = std::chrono::system_clock::now().time_since_epoch().count();
int get_random_num_mt (int min, int max) {
	std::mt19937 g1(seed_mt);
	seed_mt = g1();
	return g1() % (max - min) + min;
}

void init () {
	p.clear();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		p.push_back(i);
}

void print_out () {
	for (int i = 0; i < p.size(); i++)
		cout << p[i] << " ";
	cout << endl;
}

void method1 () {
	init();
	for (int i = p.size()-1; i >= 1; i--) {
		int k = get_random_num(0, i+1);
		int t = p[k];	p[k] = p[i];	p[i] = t;
	}
}

void method2 () {
	init();
	for (int i = 0; i < p.size(); i++) {
		int k = get_random_num(0, i+1);
		p[i] = p[k];
		p[k] = i;
	}
}

void next_permutation () {
	int j;
	// L2	find j, where p[j] to be increase.
	for (j = p.size()-2; j >= 0; j--) {
		if (p[j] >= p[j+1])
			continue;
		else break;
	}
	// L3	find i, p[j] <- p[i], so p[i] should be the smallest number of bigger numbers.
	int i = p.size()-1;
	while (p[j] > p[i] && j != i) i--;
	int t = p[i];	p[i] = p[j];	p[j] = t;
	// L4	reverse p[j+1 : p.size()]
	for (int l = j+1, r = p.size()-1; l <= r; l++, r--) {
		int t = p[r];	p[r] = p[l];	p[l] = t;
	}
}

void quick_sort (int low, int high) {
	if (low >= high) return;

	int i = low;
	int pivot = p[high];
	// 将轴值放到正确位置
	while (i < high && p[i] <= pivot)
		i++;
	int j = i;
	for (; j != high; j++) {
		if (p[j] < pivot) {
			int t = p[i];	p[i] = p[j]; p[j] = t;
			i++;
		}
	}
	p[j] = p[i];
	p[i] = pivot;
	// 递归调用
	quick_sort(low, i-1);
	quick_sort(i+1, high);
}

int find_peak_element () {
	int l = 0, r = p.size() - 1;
	while (l != r) {
		int m = (l + r) / 2;
		if (p[m + 1] - p[m] > 0)
			l = m + 1;	// middle cannot be the peak
		else
			r = m;		// middle is always different from right
	}
	return l;
}


void shuffle_deck () {
	method2();	// 生成一个全排列
	using card = int;
	// 匿名函数，利用生成的全排列，映射到牌面
	auto suit = [] ( card c ) { return "SHDC"[ c/13 ]; };
	auto rank = [] ( card c ) { return "AKQJT98765432"[ c%13 ]; };
	
	int count = 0;
	for ( card c : p ) {
		cout << '_' << rank(c) << suit(c);
		count++;
		if (count % 13 == 0) cout << endl;
	}
}

int main () {
	int sel = get_random_num(0, 2);
	switch (sel) {
		case 0: method1(); break;
		case 1: method2(); break;
	}

	// print_out();
	
	// 测试生成接下一来5个排列
	/*
	cout << "Next 5 permutations are: " << endl;
	for (int i = 0; i < 5; i++) {
		next_permutation();
		print_out();
	}
	*/
	
	// 测试查找一个 peak element 的位置
	/*
	print_out();
	cout << "One peak element's index is: " << find_peak_element() << endl;
	*/

	// 测试快速排序算法
	/*
	cout << "Sorted: " << endl;
	quick_sort(0, p.size()-1);
	print_out();
	*/

	// 测试洗牌
	
	cout << "random permutation: " << endl;
	print_out();
	cout << endl << "Shuffled deck order [ S--spade, H--heart, D--diamond, C--club ]" << endl;
	shuffle_deck();
	
	return 0;
}

/*
	for (int i = 0; i < 20; i++) {
		cout << get_random_num_mt(0, 10) << " ";
	}
	cout << endl;*/
