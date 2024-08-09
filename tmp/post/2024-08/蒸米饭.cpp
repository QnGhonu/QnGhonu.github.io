#include <iostream>
#include <future>
#include <chrono>

// һ����ʱ�ĺ���
int cook_rise(int timestask) {
	std::cout << "Making rise..." << std::endl;
	// ģ�����׷���ʱ��
	std::this_thread::sleep_for(std::chrono::seconds(timestask));
	// �׷�������
	return 1;
}

int main() {

	// ��ʼ���׷�(ͬ��)
	std::cout << "Function result: "
	          << cook_rise(5)
	          << std::endl;

	// ��ʼ���׷�(�첽)
	std::future<int> f1 =
	    std::async(std::launch::async, cook_rise, 5);
	// �������鶼�����ˣ�����׷�����û
	std::future_status status_1;
	int outs = 0;
	do {
		printf("\r�������׷�...%c", outs==0?'\\':outs==1?'-':'/');
		outs = outs==3?0:outs+1;
		status_1 = f1.wait_for(std::chrono::milliseconds(300));
	} while (status_1 != std::future_status::ready);
	putchar('\n');
	// ������
	std::cout << "Function_1 result: " << f1.get() << std::endl;

	return 0;
}

/*ģ��
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

