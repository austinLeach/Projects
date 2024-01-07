% This is identical to Luger's version except than an error on the 
% "get_children" definition is corrected, by adding the clause
% "empty_set(Children)".

:- [adts].

move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 - 2, Col2 >= 1, Row2 is Row1 + 1, Row2 =< 8, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 - 1, Col2 >= 1, Row2 is Row1 + 2, Row2 =< 8, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 + 1, Col2 =< 8, Row2 is Row1 + 2, Row2 =< 8, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 + 2, Col2 =< 8, Row2 is Row1 + 1, Row2 =< 8, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 + 2, Col2 =< 8, Row2 is Row1 - 1, Row2 >= 1, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 + 1, Col2 =< 8, Row2 is Row1 - 2, Row2 >= 1, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 - 1, Col2 >= 1, Row2 is Row1 - 2, Row2 >= 1, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 - 2, Col2 >= 1, Row2 is Row1 - 1, Row2 >= 1, Y is (Row2-1) * 8 + Col2, Y >= 0.	

%unsafe(0).

	%%%%% Depth first path "shell" algorithm as found in book %%%%%%%

go(Start, Goal) :-
	empty_stack(Empty_open),
	stack([Start,nil], Empty_open, Open_stack),
        empty_stack(Closed_set),
	path(Open_stack, Closed_set, Goal).
	
path(Open_stack,_,_) :-
	empty_stack(Open_stack),
        write('No solution found with these rules').
	
path(Open_stack, Closed_set, Goal) :-
        stack([State, Parent], _, Open_stack), State = Goal,
        write('A Solution is Found!'), nl,
        printsolution([State, Parent], Closed_set).

path(Open_stack, Closed_set, Goal) :-
        stack([State, Parent], Rest_open_stack, Open_stack), 
        get_children(State, Rest_open_stack, Closed_set, Children),
        add_list_to_stack(Children, Rest_open_stack, New_open_stack),
        union([[State,Parent]], Closed_set, New_closed_set),
        path(New_open_stack, New_closed_set, Goal), !.

get_children(State, Rest_open_stack, Closed_set, Children):-
        bagof(Child, moves(State, Rest_open_stack, 
            Closed_set, Child), Children);
	empty_set(Children).

moves(State, Rest_open_stack, Closed_set, [Next, State]) :-
        move(State, Next),
%        not(unsafe(Next)),
        not(member_stack([Next, _], Rest_open_stack)),
        not(member_set([Next, _], Closed_set)).

printsolution([State, nil], _) :-
        write(State), nl.

printsolution([State, Parent], Closed_set) :-
        member_set([Parent, Grandparent], Closed_set),
        printsolution([Parent, Grandparent], Closed_set),
        write(State), nl.
