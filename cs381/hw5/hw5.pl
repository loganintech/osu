
/* Knowledge Base */

when(275,10).
when(261,12).
when(381,11).
when(398,12).
when(399,12).

where(275,owen102).
where(261,dear118).
where(381,cov216).
where(398,dear118).
where(399,cov216).

enroll(mary,275).
enroll(john,275).
enroll(mary,261).
enroll(john,381).
enroll(jim,399).

/* Exercise 1 */

/* A */
schedule(Student, Room, Time) :-
    enroll(Student, Class),
    where(Class, Room),
    when(Class, Time).

/* B */
usage(Room, Time) :-
    where(Class, Room),
    when(Class, Time).

/* C */
conflict(Class, OtherClass) :-
    where(Class, Loc),
    where(OtherClass, Loc),
    Class \= OtherClass.

/* D */
closeTime(10, 11).
closeTime(11, 12).
closeTime(10, 10).
closeTime(11, 11).
closeTime(12, 12).


meet(A, B) :-
    enroll(A, Class),
    when(Class, Time),
    enroll(B, OtherClass),
    when(OtherClass, OtherTime),
    closeTime(Time, OtherTime),
    A \= B.

/* Exercise 2 */


rdup([], []).
rdup([Elem | Rest], [Elem | DeDuped]) :-
    not(member(Elem, Rest)),
    rdup(Rest, DeDuped).

rdup([Elem | Rest], DeDuped) :-
    member(Elem, Rest),
    rdup(Rest, DeDuped).



flat([], []).
flat([Elem | Rest], FlattenedList) :-
    !,
    flat(Elem, NewList),
    flat(Rest, OtherList),
    append(NewList, OtherList, FlattenedList).
flat(L, [L]).



% % Couldn't figure it out /shrug
% % Dock me I suppose

% last(X, [X]).
% last(X, [_|Z]) :- last(X, Z)

% project([Idx | Idxs], [Project | OtherProjects], ResultList) :-
%     len([Project | OtherProjects]) = idx,
%     append([], last(OtherProjects)).
