.name "little_mushroom"
.comment "🍄"

l2:		sti r1, %:live, %1
	ld		%151125760, r3 ## zjmp
	ld		%57672449, r4 ## zjump copy start
	ld		%4278190080, r5 ## zjump copy end
	ld		%57673217 , r6 ## st copy start
	ld		%1, r7 ## st copy end
	and r2, %0, r2

live:	live %1
	st	r6, 511 ## start of write of copy of of write of copy
	st	r5, 510 ## end of write of copy of of write of copy
	st	r4, 506 ## start of write of copy of zjump
	st	r5, 505 ## end of write of copy of zjump
	st	r3, 501 ## copy zjump
	zjmp %485
