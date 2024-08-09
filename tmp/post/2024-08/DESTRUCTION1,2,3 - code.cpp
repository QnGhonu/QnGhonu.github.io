#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#include <windows.h>
using namespace std;

int core, ram, sata;

std::mutex mtx;
int wait_time;
std::vector<int> primes;
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0) return false;
    return true;
}
void gets(int beginning, int maxnum) {
    for (int i = beginning; i <= maxnum; ++i) {
        if (is_prime(i)) {
            mtx.lock();
            primes.push_back(i);
            mtx.unlock();
        }
	}
}
int test(int howmany, int howlong) {
    primes.clear();
    std::vector<std::thread> tasks;
    int num_threads = howmany;
    int num_per_thread = howlong / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * num_per_thread;
        int end = (i + 1) * num_per_thread - 1;
        if (i == num_threads - 1 && end != howlong) end = howlong;
        tasks.push_back(std::thread([start, end]() {
            gets(start, end);
        }));
    }
    for (auto& thread : tasks) thread.join();
    return primes.size();
}
int to_cpu() {
	printf("开始占用CPU线程");
    int answer = 0;
    test(core, 300000000);
    return 0;
}

void createEmptyFile(const string& filename, long long sizeInBytes) {
    ofstream ofs(filename, ios::binary | ios::out);
    if (!ofs) {
        cerr << "Creating this file was error: " << filename << endl;
        return;
    }
    ofs.seekp(sizeInBytes - 1);
    ofs.write("", 1);
    ofs.close();
}
void to_make() {
    string filename = "C:\\reserved_space.QnGhonu";
    long long reservedSize = sata * 1024 * 1024 * 1024LL;
    createEmptyFile(filename, reservedSize);
    cout << "Successfully created an empty file with " << reservedSize << " bytes." << endl;
}

void to_ram() {
    long long reservedSize = ram * 1024 * 1024 * 1024LL;
    for (int i=0; i!=ram; i++) {
    	for (int j=0; j!=1024; j++) {
    		for (int k=0; k!=1024; k++) {
				malloc(1024);
			}
		}
	}
    cout << "Successfully requested with " << reservedSize << " bytes." << endl;
}

void to_init() {
	core = 20;
	ram = 4;
	sata = 50;
}

int main() {
	to_init();
	to_make();
	to_ram();
	to_cpu();
	system("pause");
	system("del C:\\reserved_space.QnGhonu");
    return 0;
}

