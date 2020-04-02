#include <cstddef>
#include "obstacle.h"
#include "includes.h"
using namespace std;

namespace {
	template<typename T>
	class has_begin_end {
		using yes = byte;
		using no = struct { yes dummy[2]; };

		template<class U>
		static auto test(U* u) -> decltype((*u).begin(), (*u).end(), yes());

		static no   test(...);
	public:
		static constexpr bool value = (sizeof(test((T*)nullptr)) == sizeof(yes));
	};
}

void io_file_manager(int, char**);
string& input_path();
string& output_path();

void parse_map(
	sommet* const start,
	sommet* const finish,
	vector<obstacle>* const obstacles
);

void write_obstacles(vector<obstacle> const&);
template<typename path_holder>
inline
typename enable_if<has_begin_end<path_holder>::value>::type
write_path(const path_holder& cont) {
	ifstream src( input_path(), ios::binary);
	ofstream dst(output_path(), ios::binary);
	dst << src.rdbuf();
	src.close();
	dst << endl;
	dst << "[$OptPath]" << endl;
	for (const auto& elem : cont) {
		dst << elem.x() << ' ' << elem.y() << endl;
	}
	dst.close();
}