#pragma once


template <class T>
class unique_pointer
{
private:
	T* internal_ptr;


public:
	explicit unique_pointer() noexcept;
	explicit unique_pointer(T* new_internal_ptr) noexcept;

	unique_pointer(const unique_pointer&) = delete;
	unique_pointer &operator=(const unique_pointer&) = delete;

	T* release() noexcept;
	void reset(T* new_ptr = nullptr) noexcept;

	unique_pointer(unique_pointer&& other) noexcept;
	unique_pointer &operator=(unique_pointer&& other) noexcept;

	explicit operator bool() const noexcept;
	T* get() const noexcept;
	T* operator->() const noexcept;
	T& operator*() const noexcept;

	~unique_pointer();


};

unique_pointer<class T>::unique_pointer() noexcept
	: internal_ptr(nullptr)
{}

template<class T>
inline unique_pointer<T>::unique_pointer(T* new_internal_ptr) noexcept
	: internal_ptr(new_internal_ptr)
{}

template<class T>
inline T* unique_pointer<T>::release() noexcept
{
	T* old = internal_ptr;
	internal_ptr = nullptr;
	return old;
}

template<class T>
inline void unique_pointer<T>::reset(T* new_ptr) noexcept
{
	T* old = internal_ptr;
	internal_ptr = new_ptr;
	if (old)
	{
		delete old;
	}
}

template<class T>
inline unique_pointer<T>::unique_pointer(unique_pointer&& other) noexcept
	: internal_ptr(other.release())
{}

template<class T>
inline unique_pointer<class T>& unique_pointer<T>::operator=(unique_pointer && other) noexcept
{
	if (this != &other)
	{
		reset(other.release());
	}
	return this*;
}

template<class T>
inline unique_pointer<T>::operator bool() const noexcept
{
	return static_cast<bool>(internal_ptr);
}

template<class T>
inline T* unique_pointer<T>::get() const noexcept
{
	return internal_ptr;
}

template<class T>
inline T* unique_pointer<T>::operator->() const noexcept
{
	return internal_ptr;
}

template<class T>
inline T& unique_pointer<T>::operator*() const noexcept
{
	return *internal_ptr;
}



unique_pointer<class T>::~unique_pointer()
{
	if (internal_ptr) 
	{
		delete internal_ptr;
	}
}