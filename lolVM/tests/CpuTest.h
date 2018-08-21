#pragma once
#include "../cpu_core.h"

class CpuTest
{
public:
	CpuTest();
	CpuTest(cpu * c);
	~CpuTest();

	void RunTests();
	void free() {
		if (c != nullptr) {
			if (m_cpuPassed == false) {
				c->free();
				delete c;
				c = nullptr;
			}
		}
	}

private:

	void test_hlt();
	//Move tests
	void test_movrtr();
	void test_movrtm();
	void test_movmtr();
	void test_movctr();
	void test_movctm();

	//Stack Tests
	void test_pshreg();
	void test_pshmem();
	void test_popstk();

	//math
	void test_add();
	void test_sub();
	void test_mul();

	//compare
	void test_cmprtr();
	void test_cmprtm();

	//Jumping
	void test_jmp();
	void test_jne();
	
	void test_loop();

	cpu * c;
	bool m_cpuPassed;


};

