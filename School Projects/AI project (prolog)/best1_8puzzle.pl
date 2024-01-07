% This is identical to best1, except a nontrivial definition is given for
% the heuristic predicate.

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

%unsafe(0).

% In predicate heuristic(State,Goal,Value), Value is to be calculated as the
% estimated distance from the State to the Goal, e.g., in the 8-puzzle this
% might be the number of tiles out of place in State compared with Goal.  

heuristic([],[],0).
heuristic([Head1|Tail1],[Head2|Tail2],V1):-Head1=:=0,heuristic(Tail1,Tail2,V1).
heuristic([Head1|Tail1],[Head2|Tail2],V1):-Head1=:=Head2,heuristic(Tail1,Tail2,V1).
heuristic([Head1|Tail1],[Head2|Tail2],V2):-Head1=\=Head2,heuristic(Tail1,Tail2,V1),V2 is V1+1.

% The precedes predicate is needed for the priorty-queue code in the atds
% file.  The positions between the [ and ] represent State, Parent (of State),
% Depth (from of State from root), Heuristic (value for State),
% Depth+Heurstic (the value of the evaluation function f(n)=g(n)+h(n)).

precedes([_,_,_,_,F1], [_,_,_,_,F2]) :- F1 =< F2.

%%%%%%% Best first search algorithm%%%%%%%%%

	% go initializes Open and Closed and calls path	

go(Start, Goal) :- 
	empty_set(Closed_set),
	empty_pq(Open),
	heuristic(Start, Goal, H),
	insert_pq([Start, nil, 0, H, H], Open, Open_pq),
	path(Open_pq, Closed_set, Goal).


	% Path performs a best first search,
	% maintaining Open as a priority queue, and Closed as
	% a set.
	
	% Open is empty; no solution found

path(Open_pq, _, _) :- 
	empty_pq(Open_pq),
	write('graph searched, no solution found').

	% The next record is a goal
	% Print out the list of visited states

path(Open_pq, Closed_set, Goal) :- 
	dequeue_pq([State, Parent, _, _, _], Open_pq, _),
	State = Goal,
	write('Solution path is: '), nl,
	printsolution([State, Parent, _, _, _], Closed_set).
	
	% The next record is not equal to the goal
	% Generate its children, add to open and continue

path(Open_pq, Closed_set, Goal) :- 
	dequeue_pq([State, Parent, D, H, S], Open_pq, Rest_of_open_pq),
        get_children([State, Parent, D, H, S], Rest_of_open_pq, Closed_set,
             Children, Goal),
	insert_list_pq(Children, Rest_of_open_pq, New_open_pq),
	union([[State, Parent, D, H, S]], Closed_set, New_closed_set),
	path(New_open_pq, New_closed_set, Goal),!.

get_children([State, _, D, _, _], Rest_of_open_pq, Closed_set, Children, 
             Goal) :-
        bagof(Child, moves([State, _, D, _, _], Rest_of_open_pq,
             Closed_set, Child, Goal), Children);
        empty_set(Children).

	% moves generates all children of a state that are not already on
	% open or closed.  For each child, it adds 1 to the current depth D
	% calculates the heuristic H for the child, as well as the sum S of
	% these two values (i.e., calculation of f(n)=g(n)+h(n)).

	% Also, unsafe is commented out as we dont need it here.

moves([State, _, Depth, _, _], Rest_of_open_pq, Closed_set, 
             [Next, State, New_D, H, S], Goal) :-
	move(State, Next),
%	not(unsafe(Next)),
	not(member_pq([Next, _, _, _, _], Rest_of_open_pq)),
	not(member_set([Next, _, _, _, _], Closed_set)),
	New_D is Depth + 1,
	heuristic(Next, Goal, H),
	S is New_D + H.

	% Printsolution prints out the solution path by tracing
	% back through the states on closed using parent links.

printsolution([State, nil, _, _, _], _):-  
	write(State), nl.
printsolution([State, Parent, _, _, _], Closed_set) :-
	member_set([Parent, Grandparent, _, _, _], Closed_set),
	printsolution([Parent, Grandparent, _, _, _], Closed_set),
	write(State), nl.