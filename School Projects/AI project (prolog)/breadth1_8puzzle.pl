:- [adts].

/* 0 refers to the empty square
Pos1, Pos2, Pos3
Pos4, Pos5, Pos6
Pos7, Pos8, Pos9
*/

move([0,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9],[Pos2,0,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9]).
move([0,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9],[Pos4,Pos2,Pos3,0,Pos5,Pos6,Pos7,Pos8,Pos9]).

move([Pos1,0,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9],[0,Pos1,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9]).
move([Pos1,0,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9],[Pos1,Pos5,Pos3,Pos4,0,Pos6,Pos7,Pos8,Pos9]).
move([Pos1,0,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9],[Pos1,Pos3,0,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9]).

move([Pos1,Pos2,0,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9],[Pos1,0,Pos2,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9]).
move([Pos1,Pos2,0,Pos4,Pos5,Pos6,Pos7,Pos8,Pos9],[Pos1,Pos2,Pos6,Pos4,Pos5,0,Pos7,Pos8,Pos9]).

move([Pos1,Pos2,Pos3,0,Pos5,Pos6,Pos7,Pos8,Pos9],[0,Pos2,Pos3,Pos1,Pos5,Pos6,Pos7,Pos8,Pos9]).
move([Pos1,Pos2,Pos3,0,Pos5,Pos6,Pos7,Pos8,Pos9],[Pos1,Pos2,Pos3,Pos5,0,Pos6,Pos7,Pos8,Pos9]).
move([Pos1,Pos2,Pos3,0,Pos5,Pos6,Pos7,Pos8,Pos9],[Pos1,Pos2,Pos3,Pos7,Pos5,Pos6,0,Pos8,Pos9]).

move([Pos1,Pos2,Pos3,Pos4,0,Pos6,Pos7,Pos8,Pos9],[Pos1,0,Pos3,Pos4,Pos2,Pos6,Pos7,Pos8,Pos9]).
move([Pos1,Pos2,Pos3,Pos4,0,Pos6,Pos7,Pos8,Pos9],[Pos1,Pos2,Pos3,0,Pos4,Pos6,Pos7,Pos8,Pos9]).
move([Pos1,Pos2,Pos3,Pos4,0,Pos6,Pos7,Pos8,Pos9],[Pos1,Pos2,Pos3,Pos4,Pos6,0,Pos7,Pos8,Pos9]).
move([Pos1,Pos2,Pos3,Pos4,0,Pos6,Pos7,Pos8,Pos9],[Pos1,Pos2,Pos3,Pos4,Pos8,Pos6,Pos7,0,Pos9]).

move([Pos1,Pos2,Pos3,Pos4,Pos5,0,Pos7,Pos8,Pos9],[Pos1,Pos2,0,Pos4,Pos5,Pos3,Pos7,Pos8,Pos9]).
move([Pos1,Pos2,Pos3,Pos4,Pos5,0,Pos7,Pos8,Pos9],[Pos1,Pos2,Pos3,Pos4,0,Pos5,Pos7,Pos8,Pos9]).
move([Pos1,Pos2,Pos3,Pos4,Pos5,0,Pos7,Pos8,Pos9],[Pos1,Pos2,Pos3,Pos4,Pos5,Pos9,Pos7,Pos8,0]).

move([Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,0,Pos8,Pos9],[Pos1,Pos2,Pos3,0,Pos5,Pos6,Pos4,Pos8,Pos9]).
move([Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,0,Pos8,Pos9],[Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,Pos8,0,Pos9]).

move([Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,0,Pos9],[Pos1,Pos2,Pos3,Pos4,0,Pos6,Pos7,Pos5,Pos9]).
move([Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,0,Pos9],[Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,0,Pos7,Pos9]).
move([Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,0,Pos9],[Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,Pos9,0]).

move([Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,0],[Pos1,Pos2,Pos3,Pos4,Pos5,0,Pos7,Pos8,Pos6]).
move([Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,Pos8,0],[Pos1,Pos2,Pos3,Pos4,Pos5,Pos6,Pos7,0,Pos8]).
unsafe(0).

%%%%%%% Breadth first search algorithm%%%%%%%%
	
go(Start, Goal) :- 
	empty_queue(Empty_open_queue),
	enqueue([Start, nil], Empty_open_queue, Open_queue),
	empty_set(Closed_set),
	path(Open_queue, Closed_set, Goal).

path(Open_queue, _, _) :- empty_queue(Open_queue),
        write('graph searched, no solution found').
	
path(Open_queue, Closed_set, Goal) :- 
	dequeue([State, Parent], Open_queue, _),
	State = Goal,
	write('Solution path is: '), nl,
	printsolution([State, Parent], Closed_set).
	
path(Open_queue, Closed_set, Goal) :- 
	dequeue([State, Parent], Open_queue, Rest_of_open_queue),
        get_children(State, Rest_of_open_queue, Closed_set, Children),
	add_list_to_queue(Children, Rest_of_open_queue, New_open_queue), 
	union([[State, Parent]], Closed_set, New_closed_set),
	path(New_open_queue, New_closed_set, Goal),!.

get_children(State, Rest_of_open_queue, Closed_set, Children) :-
        bagof(Child, moves(State, Rest_of_open_queue, Closed_set, Child),
             Children); 
        empty_set(Children).
moves(State, Rest_of_open_queue, Closed_set, [Next, State]) :-
	move(State, Next),
        not(unsafe(Next)),
	not(member_queue([Next, _], Rest_of_open_queue)),
	not(member_set([Next, _], Closed_set)).

printsolution([State, nil], _):- 
	write(State), nl.
printsolution([State, Parent], Closed_set) :-
	member_set([Parent, Grandparent], Closed_set),
	printsolution([Parent, Grandparent], Closed_set),
	write(State), nl.
