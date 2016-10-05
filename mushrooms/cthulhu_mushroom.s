.name "cthulhu_mushroom"
.comment "🍄🍄🔥🐙🔥🍄🍄"

start:
st r1, 11
zjmp %:convert
ld %0, r2

live_loop:
live %0
zjmp %:live_loop

convert:
