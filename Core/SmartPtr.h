#pragma once
#include <type_traits>

template<typename BASE, typename CHILD>
class TypeCheck
{
private:
	static short Check(BASE*) {  };
	static char Check(...) {  };

	static CHILD* p;

public:
	// sizeof 트릭 -> sizeof는 연산자이기 때문에 이것을
	// 계산하기 위해서 Check라는 함수가 먼저 계산되어야함 -> 크기 계산
	// 인자값으로 판단하기 때문에(인자는 상속이 맞는지 아닌지)
	// 아니면 char를 반환하므로 거기에 -1을 하여 true false를 판단함
	static const bool Value = (bool)(sizeof(Check(p)) - 1);

private:
	TypeCheck() {};
	~TypeCheck() {};
};

class SmartPtr
{
public:
	// 템플릿 프랜드.
	template<typename T>
	friend class KPtr;

private:
	int m_Count;

public:
	SmartPtr();
	virtual ~SmartPtr() = 0;

private:
	void Add_Cnt();
	void Dec_Cnt();
};

template<typename T/*, std::enable_if<std::is_base_of<RefBase, T>::value, T>::type*/>
class KPtr
{
private:
	T* m_Ptr;

public:
	KPtr() : m_Ptr(nullptr) {}

	KPtr(T* _PTR) : m_Ptr(_PTR)
	{
		Ptr_Add();
	}
	KPtr(const KPtr& _PTR) : m_Ptr(_PTR.m_Ptr)
	{
		Ptr_Add();
	}
	KPtr(std::nullptr_t _PTR) : m_Ptr(_PTR)
	{
		// nullptr;
	}
	~KPtr()
	{
		Ptr_Dec();
	}

public:
	bool operator==(std::nullptr_t _PTR) const
	{
		return m_Ptr == _PTR;
	}

	bool operator==(T* _PTR) const
	{
		return m_Ptr == _PTR;
	}

	bool operator==(const KPtr& _PTR) const
	{
		return m_Ptr == _PTR.m_Ptr;
	}

	bool operator!=(std::nullptr_t _PTR) const
	{
		return m_Ptr != _PTR;
	}

	bool operator<(const KPtr& _Other) const
	{
		return m_Ptr < _Other.m_Ptr;
	}
	bool operator>(const KPtr& _Other) const
	{
		return m_Ptr > _Other.m_Ptr;
	}

	// 형변환
	operator T*()
	{
		return m_Ptr;
	}

	const T* operator ->() const
	{
		return m_Ptr;
	}


	T* operator->()
	{
		return m_Ptr;
	}

	T& operator *()
	{
		return *m_Ptr;
	}
	

	// static 일반 변수 캐스팅
	// reinterpret 강제 캐스팅
	// dynamic 상속관계 캐스팅 - C스타일이 아님 - virtual 상속간에만 가능
	// 런타임 때 연산 -> 문자열 비교
	// const const or volatile 해제 시

	template<typename InType>
	operator KPtr<InType>()
	{
		if (nullptr == m_Ptr)
		{
			return nullptr;
		}

		// 일반적으로 상속구조일때 사용하는 캐스팅입니다.
		// 상속이 아니면 nullptr 반환
		InType* P = dynamic_cast<InType*>(m_Ptr);
		if (true == TypeCheck<T, InType>::Value)
		{
			return (InType*)m_Ptr;
		}
		return nullptr;
	}

	KPtr<T>& operator = (T* _PTR)
	{
		if (m_Ptr == _PTR)
		{
			return *this;
		}

		// 내가 원래 가지고 있던 포인터는 감소
		Ptr_Dec();
		m_Ptr = _PTR;
		// 새롭게 받은 포인터는 증가.
		Ptr_Add();
		return *this;
	}

	KPtr<T>& operator = (const KPtr& _PTR)
	{
		if (m_Ptr == _PTR.m_Ptr)
		{
			return *this;
		}

		Ptr_Dec();
		m_Ptr = _PTR.m_Ptr;
		// 새롭게 받은 포인터는 증가.
		Ptr_Add();
		return *this;
	}


private:
	void Ptr_Add()
	{
		if (nullptr != m_Ptr)
		{
			m_Ptr->Add_Cnt();
		}
	}

	void Ptr_Dec()
	{
		if (nullptr != m_Ptr)
		{
			m_Ptr->Dec_Cnt();
		}
	}
};

template<typename T>
bool operator==(std::nullptr_t _PTR, const KPtr<T>& _KPtr) { return _KPtr == _PTR; }

template<typename T>
bool operator!=(std::nullptr_t _PTR, const KPtr<T>& _KPtr) { return _KPtr != _PTR; }
