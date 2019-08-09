#include <cstdio>
struct EmptyList {
};
template <int N, class T>
struct IntList {
	static const int Head = N;
	typedef T Tail;
};

#define LIST1(N1) IntList<N1, EmptyList>
#define LIST2(N1,N2) IntList<N1, LIST1(N2) >
#define LIST3(N1,N2,N3) IntList<N1, LIST2(N2,N3) >
#define LIST4(N1,N2,N3,N4) IntList<N1, LIST3(N2,N3,N4) >
#define LIST5(N1,N2,N3,N4,N5) IntList<N1, LIST4(N2,N3,N4,N5) >

#define NUM2(x,y) 10*(x) + (y)
#define NUM3(x,y,z) 100*(x) + 10*(y) + (z)
#define NUM4(w,x,y,z) 1000*(w) + 100*(x) + 10*(y) + (z)
#define NUM5(v,w,x,y,z) 10000*(v) + 1000*(w) + 100*(x) + 10*(y) + (z)

#define DIFFER3(x,y,z) ((x) != (y) && (x) != (z) && (y) != (z))
#define DIFFER4(x,y,z,w) ((x) != (y) && (x) != (z) && (x) != (w) && DIFFER3(y,z,w))
#define DIFFER5(x,y,z,w,v) ((x) != (y) && (x) != (z) && (x) != (w) && (x) != (v) && DIFFER4(y,z,w,v))

template <class T> struct LSolve {
	static const int Answer0 = LSolve<IntList<0, T> >::Answer;
	static const int Answer1 = LSolve<IntList<1, T> >::Answer;
	static const int Answer2 = LSolve<IntList<2, T> >::Answer;
	static const int Answer3 = LSolve<IntList<3, T> >::Answer;
	static const int Answer4 = LSolve<IntList<4, T> >::Answer;
	static const int Answer5 = LSolve<IntList<5, T> >::Answer;
	static const int Answer6 = LSolve<IntList<6, T> >::Answer;
	static const int Answer7 = LSolve<IntList<7, T> >::Answer;
	static const int Answer8 = LSolve<IntList<8, T> >::Answer;
	static const int Answer9 = LSolve<IntList<9, T> >::Answer;
	static const int Answer = Answer0 + Answer1 + Answer2 + Answer3 + Answer4 + Answer5 + Answer6 + Answer7 + Answer8 + Answer9;
};

template <int U, int D, int A, int R, int K> 
struct LSolve<LIST5(U, D, A, R, K) > {
	static const int Answer =
		NUM4(U, D, A, R) + NUM4(U, D, A, R) == NUM5(D, R, A, K, A) && (U != 0) && (D != 0) && DIFFER5(U, D, A, R, K) ?
		NUM5(D, U, R, A, K) : 0;
};

typedef LSolve<EmptyList> Solve;

int main(int argc, const char* argv[]) {
	printf("ÄÓÐÀÊ=%d\n", Solve::Answer);
}
