# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
	stack<T> st;
	stack<T> mins;
public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {

	return st.empty();
}

template <class T>
T& StackExt<T>::top() {
	return st.top();
}

template <class T>
void StackExt<T>::pop() {
	if(st.size() == 0)
		return;
	if(mins.top() == st.top())
		mins.pop();
	st.pop();
}

template <class T>
void StackExt<T>::push(const T& val) {
	if(mins.size() == 0)
	{
		mins.push(val);
;	}
	else if(mins.top() >= val)
	{
		mins.push(val);
	}
	st.push(val);
}

template <class T>
T& StackExt<T>::findMin() {
	return mins.top();
}
