#include <cstdint>
#include <cstddef>
#include <iterator>

namespace rose {
typedef uint32_t utf8code;

struct utf8range {
	const char * head;
	int tail_in_bytes;

	utf8code peek(int & bytes) const;
	utf8code peek() const {
        int bytes = 0;
        return peek(bytes);
    }

    bool operator==(utf8range rhs) const { return head == rhs.head && tail_in_bytes == rhs.tail_in_bytes; }
    bool operator!=(utf8range rhs) const { !(*this == rhs); }
};

struct utf8iterator : utf8range {
    // Required typedefs
    typedef std::ptrdiff_t difference_type;
    typedef utf8range value_type;
    typedef utf8range* pointer;
    typedef utf8range& reference;
    typedef std::forward_iterator_tag iterator_category;

    void increment() {
    	int bytes;
    	utf8code code = peek(bytes);
    	(void)(code);
        //TODO: check overflow
    	head += bytes;
    	tail_in_bytes -= bytes;
    }

    // Required member functions
    utf8iterator& operator++() {
    	increment();
    	return *this;
    }

    utf8iterator operator++(int) {
    	utf8iterator copy = *this;
    	increment();    
    	return copy;
    }

    reference operator*() { return *this; }
    pointer operator->() { return this; }
};

struct utf8span {
	utf8iterator it;

    utf8span(const char * str, int length) : it({str, length}) {}

	utf8iterator begin() const { return it; }
	utf8iterator end() const { return { it.head + it.tail_in_bytes, 0 }; }

    int length() const {
        int result = 0;
        auto my_end = end();
        for(auto current = begin(); current != my_end; ++current) {
            ++result;
        }
        return result;
    }
};

struct utf8reader {
    int handle = 0;

	virtual ~utf8reader() {}
	virtual utf8span get(int) const = 0;

	operator utf8span() const { return get(handle); }
    utf8span operator->() const { return get(handle); }
};

struct utf8writer : utf8reader {
	virtual utf8writer append(utf8span) = 0;
};

}
