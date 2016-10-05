.name "z"
.comment ""

l2:		sti r1, %:live, %256
		and r3, %255, r4

live:	live %1
		zjmp %:live
