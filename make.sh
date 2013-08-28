progname="tts"
spu-gcc -c -o "$progname"_spe.o "$progname"_spe.c
spu-gcc -o "$progname"_spe "$progname"_spe.o
ppu-embedspu "$progname"_spe "$progname"_spe "$progname"_embed.o
ppu-gcc -c -o "$progname"_ppe.o "$progname"_ppe.c
ppu-gcc -o "$progname" "$progname"_ppe.o "$progname"_embed.o -lspe2
./tts
