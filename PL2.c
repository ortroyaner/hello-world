#include <stdio.h>

enum { // A more civilized way to name integer values
	LG2_POOLSIZE = 14, // How many bits for index into pool
	KIND_SIZE = 2 // How many bits for storing  car/cdr kind
};

char atom[ 1 << LG2_POOLSIZE ]; // will be used for atoms
enum kind { NIL, ATOM, STRING, INTEGER };
struct Cons {
	enum kind carKind : KIND_SIZE;
	unsigned int car : LG2_POOLSIZE;
	enum kind cdrKind : KIND_SIZE;
	unsigned int cdr : LG2_POOLSIZE;
} pool[ 1 << LG2_POOLSIZE ]; // Pool of ``struct Cons'' nodes

//string handlers;
const char *handles[ 1 << LG2_POOLSIZE ];

//  New code

struct _cdr{
	enum kind cKind = KIND_SIZE;
	unsigned int cdr : LG2_POOLSIZE;
}

struct _car {
	enum kind cKind : KIND_SIZE;
	unsigned int car : LG2_POOLSIZE;
}

struct _car car(struct Cons cons){
	struct _car newCar;
	newCar.car = cons.car;
	newCar.cKind = cons.carKind; 
	return newCar;
}

struct _cdr cdr(struct Cons cons){
	struct _cdr newCdr;
	newCdr.cdr = cons.cdr;
	newCdr.cKind = cons.cdrKind; 
	return newCar;
}

struct Cons CONS(struct _cdr cdr,struct _car car){
	struct Cons newCons;
	newCons.cdr = cdr.cdr;
	newCons.cdrKind = cdr.cKind;
	newCons.car = car.car;
	newCons.carKind = car.cKind;
	return newCons;
}

s_expr eval(s_expr x){
	// now we implement mini-eval
	switch (car(x).car){
		case "car":
			s_expr e = eval(car(cdr(x)));
			return car(e);
			break;
		case "cdr":
			s_expr e = eval(car(cdr(x));
			return cdr(e);
			break;
		case "cons":
			s_expr e1 = eval(car(cdr(x))));
			s_expr e2 = eval(car(cdr(cdr(x))));
			return CONS(e1,e2);
		    break;
		defualt:
			return NIL;
	}
}
