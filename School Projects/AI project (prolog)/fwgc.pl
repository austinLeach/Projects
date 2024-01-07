/*
 * This is the code for the Farmer, Wolf, Goat and Cabbage Problem
 * using the ADT Stack.
 *
 * Run this code by giving PROLOG a "go" goal.
 * For example, to find a path from the west bank to the east bank,
 * give PROLOG the query:
 *
 *   go(state(w,w,w,w), state(e,e,e,e)).
 */

:- [adts]. /* consults (reconsults) file containing the
	      various ADTs (Stack, Queue, etc.) */

go(Start,Goal) :-
	empty_stack(Empty_been_stack),
	stack(Start,Empty_been_stack,Been_stack),
	path(Start,Goal,Been_stack).

/*
 * Path predicates
 */

path(Goal,Goal,Been_stack) :-
	write('Solution Path Is:' ), nl,
	reverse_print_stack(Been_stack).

path(State,Goal,Been_stack) :-
	move(State,Next_state),
	not(member_stack(Next_state,Been_stack)),
	stack(Next_state,Been_stack,New_been_stack),
	path(Next_state,Goal,New_been_stack),!.

/*
 * Move predicates
 */

move(state(X,X,G,C), state(Y,Y,G,C))
              :- opp(X,Y), not(unsafe(state(Y,Y,G,C))),
                 writelist(['try farmer takes wolf',Y,Y,G,C]).

move(state(X,W,X,C), state(Y,W,Y,C))
              :- opp(X,Y), not(unsafe(state(Y,W,Y,C))),
                 writelist(['try farmer takes goat',Y,W,Y,C]). 

move(state(X,W,G,X), state(Y,W,G,Y))
              :- opp(X,Y), not(unsafe(state(Y,W,G,Y))),
                 writelist(['try farmer takes cabbage',Y,W,G,Y]).

move(state(X,W,G,C), state(Y,W,G,C))
              :- opp(X,Y), not(unsafe(state(Y,W,G,C))),
                 writelist(['try farmer takes self',Y,W,G,C]).

move(state(F,W,G,C), state(F,W,G,C))
              :- writelist(['      BACKTRACK from:',F,W,G,C]), fail.

/*
 * Unsafe predicates
 */

unsafe(state(X,Y,Y,C)) :- opp(X,Y).
unsafe(state(X,W,Y,Y)) :- opp(X,Y).

/*
 * Definitions of writelist, and opp.
 */

writelist([]) :- nl.
writelist([H|T]):- print(H), tab(1),  /* "tab(n)" skips n spaces. */
                   writelist(T).

opp(e,w).
opp(w,e).

reverse_print_stack(S) :-
        empty_stack(S).
reverse_print_stack(S) :-
        stack(E, Rest, S),
        reverse_print_stack(Rest),
        write(E), nl.

/*
 * Do a run.
 */

test:-go(state(w,w,w,w),state(e,e,e,e)).
