.name "hola"
.comment "holasasaasasa"
#.name "zork zork zork zork zork zork zork zork zork zor50zork zork zork zork zork zork zork zork zork zo100zork zork zork zork zor25abc"

l2:		sti r1, %:live, %
		and r1, %0, r1

live:	live %1
		zjmp %:live
