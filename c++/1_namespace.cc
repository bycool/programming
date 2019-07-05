#include <iostream>

using namespace std;

namespace spaa {
	int a = 10;
}

namespace spab {
	int a = 20;
	namespace spac {
		int a = 30;
	}
}


int main(){
	using namespace spaa;
	cout<<a<<endl;

	using namespace spab;
	cout<<spab::a<<endl;

	using namespace spac;
	cout<<spac::a<<endl;

	cout<<spab::spac::a<<endl;

	using namespace spab::spac;
	cout<<spac::a<<endl;
}
