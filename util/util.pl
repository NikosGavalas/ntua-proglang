appnd([], L, L).
appnd([H|L1], L2, [H|L3]) :-
    appnd(L1, L2, L3).

rvrse([], []).
rvrse([H|T], Rev) :-
    rvrse(T, RevT),
    appnd(RevT, [H], Rev).

last_elem(X, [X]).
last_elem(X, [_|T]) :-
    last_elem(X, T).

pre_last_elem(X, [X, _]).
pre_last_elem(X, [_, T|Ts]) :-
    pre_last_elem(X, [T|Ts]).

element_at(H, [H|_], 1).
element_at(X, [_|T], N) :-
    N > 1, N1 is N - 1,
    element_at(X, T, N1).

len([], 0).
len([_|T], X) :-
    len(T, X1),
    X is X1 + 1.

is_palindrome(L) :-
    rvrse(L, L).

my_flatten([], []).
my_flatten(X, [X]) :-
    \+ is_list(X).
my_flatten([H|T], X) :-
    my_flatten(T, X),
    append(H,[], X).


memb(X, [X|_]).
memb(X, [Y|T]) :-
    memb(X, T).


slct(A, [A|B], B).
slct(A, [B, C|D], [B|E]) :-
    slct(A, [C|D], E).


subset([], _).
subset([X|Xs], L) :-
    memb(X, L),
    subset(Xs, L).

subseq([], []).
subseq([X|L], [X|S]) :-
    subseq(L, S).
subseq(L, [_|S]) :-
    subseq(L, S).
