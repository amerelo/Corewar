.name "shiny_mushroom"
.comment "🍄🍄🔥🍄🍄"

start:
	zjmp	%-389
	ld		%0, r2
	zjmp	%:begin

def:
	live	%-42
	ld		%4264296448, r15
	st	    r15, -14

def2:
	st		r1, 6
	live	%-42
	fork	%:def2
	st		r1, 6
	live	%-42
	st		r1, 6
	live	%-42
	st		r1, 6
	live	%-42
	st		r1, 6
	live	%-42
	st		r1, 6
	live	%-42

begin:
	ld		%-506, r4
	ld		%-506, r6
	ld		%190055170, r8
	ld		%816280739653484033, r9
	st		r8, -510
	st		r9, -511
	ld		%-15, r8
	st		r1, 6
	live	%-42
	fork	%:def
	fork	%:p2

p1:
	st		r1, 6
	live	%-42
	ld		%0, r2
	ld		%190055682, r3
	ld		%190056194, r5
	ld		%190056194, r7
	ld		%0, r16
	zjmp	%:start

p2:
	st		r1, 6
	live	%-42
	ld		%4, r2
	ld		%101318145, r3
	ld		%134873068, r5
	ld		%134873068, r7
	ld		%0, r16
	zjmp	%:start
