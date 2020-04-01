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

int io_file_manager(int, char**);
fs::path& input_path();
fs::path& output_path();

int parse_map(
	const fs::path& filename,
	sommet* const start,
	sommet* const finish,
	vector<obstacle>* const obstacles
);

void write_obstacles(vector<obstacle> const&);
template<typename ptrs_holder>
inline
typename enable_if<has_begin_end<ptrs_holder>::value>::type
write_ptrs(const ptrs_holder& cont) {
	fs::copy_file(input_path(), output_path(), fs::copy_options::overwrite_existing);
	ofstream out(output_path(), ios::app);
	out << endl;
	out << "[$OptPath]" << endl;
	for (const auto& elem : cont) {
		out << elem.x() << ' ' << elem.y() << endl;
	}
	out.close();
}