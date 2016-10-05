.name "medium_mushroom"
.comment "🍄🍄"

start:
	zjmp	%-468
	ld		%0, r2
	zjmp	%:begin

reset:

begin:
	ld		%-506, r4
	ld		%-506, r6
	ld		%190055170, r8
	ld		%816280739653484033, r9
	st		r8, -509
	st		r9, -510
	ld		%-30, r8
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
	ld		%134873053, r5
	ld		%134873053, r7
	ld		%0, r16
	zjmp	%:start
