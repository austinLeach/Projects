move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 - 2, Col2 >= 1, Row2 is Row1 + 1, Row2 =< 8, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 - 1, Col2 >= 1, Row2 is Row1 + 2, Row2 =< 8, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 + 1, Col2 =< 8, Row2 is Row1 + 2, Row2 =< 8, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 + 2, Col2 =< 8, Row2 is Row1 + 1, Row2 =< 8, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 + 2, Col2 =< 8, Row2 is Row1 - 1, Row2 >= 1, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 + 1, Col2 =< 8, Row2 is Row1 - 2, Row2 >= 1, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 - 1, Col2 >= 1, Row2 is Row1 - 2, Row2 >= 1, Y is (Row2-1) * 8 + Col2, Y >= 0.
move(X,Y) :- Col1 is (X-1) mod 8 + 1, Row1 is (X-1) // 8 + 1, Col2 is Col1 - 2, Col2 >= 1, Row2 is Row1 - 1, Row2 >= 1, Y is (Row2-1) * 8 + Col2, Y >= 0.	
		
path(Start, Goal) :- path(Start, Goal, 99999).
path(Empty,Empty,Length).
path(X,Y,L) :- move(X,Z),	not(member(Z,L)),	path(Z,Y,[Z|L]),
							format('~0f\n',[X]). 