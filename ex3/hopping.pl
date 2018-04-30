nrev([], []).
nrev([H|T0], L) :-
	nrev(T0, T),
	append(T, [H], L).


l([],A,[]).
l([H|T],A,Y):-
	B is min(H,A),
	l(T,B,Z),
	append([B],Z,Y).

r([],A,[]).
r([H|T],A,Y):-
	B is max(H,A),
	r(T,B,Z),
	append([B],Z,Y).

aux(A,X,Y):-
	nrev(A,B),
	r(B,0,C),
	nrev(C,X),
	l(A,20000001,Y).

loop([],A,F,I,J,0).
loop(A,[],F,I,J,0).
loop([Hx|Tx],[Hy|Ty],DIST,I,J,RES):-
	\+ Hx>Hy,
	E is J+1,
	loop([Hx|Tx],Ty,DIST,I,E,Z),
	RES is Z.
loop([Hx|Tx],[Hy|Ty],DIST,I,J,RES):-
	Hx>Hy,
	C is I-J,
	D is max(C,DIST),
	E is I+1,
	loop(Tx,[Hy|Ty],D,E,J,Z),
	RES is max(D,Z).

main(A,W):-
	aux(A,X,Y),
	loop(X,Y,0,0,0,RES),
	W is RES.
