%  This Mini Expert System advises on what dog to get and is available.

% By saying top, the system begins.
%  It will ask for Skin, Body length, Tongue length and if it is bipedal or not.
% choose will bind a value to the variable Lizard.
%  You must press a period after your input.

top :- write('Skin type?'), read(Skin),
       write('Body length (inches)? '), read(Blength),
       write('Tongue length (inches)? '), read(Tlength),
       write('Two or four legs? (2 or 4) '), read(Bi),
       choose(Skin, Blength, Tlength, Bi , Lizard),
       write('You should get '), write(Lizard), nl.

% Confidence Factor of choose rules are all 60 percent.

% choose rules follow ...

choose(Skin, Blength, Tlength, Bi, 'a Green anole') :-
       smooth(Skin), small(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Viviparous Lizard') :-
       rough(Skin), small(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Leopard Gecko') :-
       bumpy(Skin), small(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a eastern fence lizard') :-
       smooth(Skin), medium(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Gila Monster') :-
       bumpy(Skin), medium(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Common Five-lined skink') :-
       rough(Skin), medium(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Marine iguana') :-
       smooth(Skin), large(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Komodo Dragon') :-
       bumpy(Skin), large(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Broadhead skink') :-
       rough(Skin), large(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Frilled-neck lizard') :-
       smooth(Skins), veryLarge(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'Godzilla') :-
       bumpy(Skin), veryLarge(Blength, Tlength).

choose(Skin, Blength, Tlength, Bi, 'a Agama agama') :-
       rough(Skin), veryLarge(Blength, Tlength), Bi = 2.

choose(Skin, Blength, Tlength, Bi, 'Geico Gecko, save 15% on car insurrence today!') :-
       smooth(Skin), small(Blength, Tlength), Bi = 2.

choose(Skin, Blength, Tlength, Bi, 'a Jesus Lizard') :-
       bumpy(Skin), medium(Blength, Tlength), Bi = 2.

choose(Skin, Blength, Tlength, Bi, 'a Mark Zuckerberg') :-
       smooth(Skin), veryLarge(Blength, Tlength), Bi = 2.

% The CF rule for these is 100
smooth(Skin) :- Skin = smooth.
bumpy(Skin) :- Skin = bumpy.
rough(Skin) :- Skin = rough.

smooth(Skin) :- Skin = slimey.
rough(Skin) :- Skin = scaly.

% the CF rule for these is 75
small(Blength, Tlength) :- (Blength + Tlength) < 8.
medium(Blength, Tlength) :- (Blength + Tlength) < 17, (Blength + Tlength) > 7.
large(Blength, Tlength) :- (Blength + Tlength) < 26, (Blength + Tlength) > 16.
veryLarge(Blength, Tlength) :- (Blength + Tlength) > 25.

