	// A hello world program in C++

	#include<iostream>
	using namespace std;

	class Foo {
		public:
			void test(int &val) {
				for (int i = 0; i < 5; ++i) {
					++val;
				}
			}
	};

	int main()
	{
		int mainVar = 0;
		cout << "The old val is " << mainVar << endl;
		Foo thisFoo;

		thisFoo.test(mainVar);
		cout << "The new val is " << mainVar << endl;
		
		return 0;
	}