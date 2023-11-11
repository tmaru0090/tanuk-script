/****singleton.hh****/
/****Singleton Class****/
#pragma once
template <typename Single>
class Singleton {
       public:
	static Single* instance() {
		static Single inst;
		return &inst;
	}

       protected:
	Singleton(){}
	Singleton(const Singleton& rhs) {}
	virtual ~Singleton() = default;
};
