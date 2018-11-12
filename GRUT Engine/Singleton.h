#pragma once

namespace GRUT {
	template<typename T>
	class Singleton {
	protected:
		Singleton() {}
		~Singleton() {}
	public:
		Singleton(Singleton const &) = delete;
		Singleton& operator=(Singleton const &) = delete;
		static T& Instance() {
			static T instance;
			return instance;
		}
	};
}