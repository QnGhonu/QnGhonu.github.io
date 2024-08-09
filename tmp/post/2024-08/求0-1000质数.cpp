#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
std::mutex mtx;
int wait_time;

// ---------- ��һ������ĳ���
std::vector<int> primes;    // ����Ĵ�
// �ж��ǲ�������
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0) return false;
    return true;
}
void func(int beginning, int maxnum) {
    for (int i = beginning; i <= maxnum; ++i) {
        if (is_prime(i)) {
            mtx.lock();
            primes.push_back(i);    // ����ǣ��ͼ���������
            mtx.unlock();
        }
	}
}
// ---------- ����������

int cores = 4; // �������㽫�ö����߳���������
int main() {
    primes.clear();
    std::vector<std::thread> tasks;
    int num_threads = cores;
    int num_per_thread = 10000000 / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * num_per_thread;
        int end = (i + 1) * num_per_thread - 1;
        if (i == num_threads - 1 && end != 10000000) end = 10000000;
        tasks.push_back(std::thread([start, end]() {
            func(start, end);
        }));
    }
    for (auto& thread : tasks) thread.join();
    for (int i : primes) {
    	std::cout << i << ' ';
	}
    return 0;
}

