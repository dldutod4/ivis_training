// What are the basic rules and idioms for operator overloading?

// https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading/4421715#4421715

// The General Syntax of operator overloading in C++

// You cannot change the meaning of operators for built-in types in C++, 
// operators can only be overloaded for user-defined types. 
// That is, at least one of the operands has to be of a user-defined type. 
// As with other overloaded functions, operators can be overloaded for a certain set of parameters only once.

// 기본타입의 operator들은 변경할 수없다
// 유저정의 타입만 가능
// 피연산자 중하나는 유저정의 타입이어야함
// 특정 파라미터셋을 가진 오퍼레이터는 하나만 지정되어야 한다.

// 모든 연산자가 오버로딩 되는 것은 아니다.

// Arithmetic 	
//     + - * / % and += -= *= /= %= 	binary infix
// 	+ - 	unary prefix
// 	++ -- 	unary prefix and postfix
// Bitwise
//  	& | ^ << >> and &= |= ^= <<= >>= 	binary infix
// 	~ 	unary prefix
// Comparison
//  	== != < > <= >= <=> 	binary infix
// Logical
//  	|| && 	binary infix
// 	! 	unary prefix
// Allocation functions
//  	new new[] delete delete[] 	unary prefix
// User-defined conversions
//   	T 	unary
// Assignment
//  	= 	binary infix
// Member access
//  	-> ->* 	binary infix
// Indirection/Address-of
//  	* & 	unary prefix
// Function call
//  	() 	N-ary postfix
// Subscript
//  	[] 	N-ary2 postfix
// Coroutine await
//  	co_await 	unary prefix
// Comma
//  	, 	binary infix

// However, the fact that you can overload all of these does not mean you should do so. 
// See the next answer.

// In C++, operators are overloaded in the form of functions with special names. As with other functions, 
// overloaded operators can generally be implemented either as a member function of their left operand's type
//  or as non-member functions. 
//  Whether you are free to choose or bound to use either one depends on several criteria.
// A unary operator @, applied to an object x, is invoked either as operator@(x) or as x.operator@().
// A binary infix operator @, applied to the objects x and y, is called either as operator@(x,y) or as x.operator@(y).5

// Operators that are implemented as non-member functions are sometimes friend of their operand’s type.

// 모든 연산자를 다 정의 해야하는 것이 아니다
// 왼쪽 피연산자 타입의 멤버함수로 구현되거나
// 비 멤버 함수로 구현될 수 있다.

// x오브젝트에 적용된 @연산자의 경우
// operator@(x)나
// x.operator@() 로 정의 가능하고

// binary infix인 경우
// operator@(x,y)나
// x.operator@(y)로 적용될수 있다.

// 비멤버함수로 구현할때는 피연산자의 freind함수로 정의하기도 한다.