.name		"mandragore"
	.comment	"you can see me, you can't anymore, you can, you can't !"

entry:  		
	sti		r10, %:entry, %1
	sti		r1, %:entry, %1
	fork	%:entry
	sti		r1, %:entry, %1
	ld		%0, r2
