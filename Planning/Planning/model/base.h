#ifndef BASE_H
#define BASE_H

using namespace std;

class base {

public:

	base() = default;
	virtual ~base() {};
	base(const base&) = default;
	base(base&&) = default;
	base& operator=(const base&) = default;
	base& operator=(base&&) = default;
protected:

private:

};



#endif // !BASE_H
