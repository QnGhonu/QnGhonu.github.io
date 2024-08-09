#include <iostream>
#include <future>
#include <chrono>

// 一个耗时的函数
int cook_rise(int timestask) {
	std::cout << "Making rise..." << std::endl;
	// 模拟蒸米饭的时间
	std::this_thread::sleep_for(std::chrono::seconds(timestask));
	// 米饭做好了
	return 1;
}

int main() {

	// 开始蒸米饭(同步)
	std::cout << "Function result: "
	          << cook_rise(5)
	          << std::endl;

	// 开始蒸米饭(异步)
	std::future<int> f1 =
	    std::async(std::launch::async, cook_rise, 5);
	// 其他事情都做完了，检测米饭蒸熟没
	std::future_status status_1;
	int outs = 0;
	do {
		printf("\r正在蒸米饭...%c", outs==0?'\\':outs==1?'-':'/');
		outs = outs==3?0:outs+1;
		status_1 = f1.wait_for(std::chrono::milliseconds(300));
	} while (status_1 != std::future_status::ready);
	putchar('\n');
	// 蒸好了
	std::cout << "Function_1 result: " << f1.get() << std::endl;

	return 0;
}

/*模板
std::future<int> f =
    std::async(std::launch::async, [](){
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 1;
	});
std::future_status status;
do {
	status = f.wait_for(std::chrono::seconds(1));
	switch (status) {
		case std::future_status::deferred:
			std::cout << "deferred\n";
			break;
		case std::future_status::timeout:
			std::cout << "timeout\n";
			break;
		case std::future_status::ready:
			std::cout << "ready\n";
			break;
	}
} while (status != std::future_status::ready);
return f.get();
*/

