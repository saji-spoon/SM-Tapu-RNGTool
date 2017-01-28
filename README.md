SM-Tapu-RNGTool
====
Create and search the DB for estimating initial seed from first 8 clock hands. 
Output a list of IVs of pokemon generated from an initial seed.

This tool is usable in RNG for Tapu {Koko/Lele/Bulu/Fini}.
(Using SFMT)
It's not usable in Egg Hatching RNG.

## Requirement  (Other environments aren't tested)
gcc (Ubuntu 4.9.2-10ubuntu13) 4.9.2

## Usage
'''
$ make

#Create DB.
$ ./db-create

#Search the DB
#Input first 8 clock hands according to heptadecimal format (below)
#0->0, 1->1, ... 10->A, 11->B, ... 15->F, 16->G
$ ./db-search 0BEEFBAG
./db/0B.bin
読み込み終了:0.484509[s]
探索終了:2.412460[s]
Result[-2]... 0BEEFBAF:d7865bfd
Result[-1]... 0BEEFBAG:24b9a52e
Result[0]... 0BEEFBAG:b98ab4f3
Result[1]... 0BEEFBB1:25341f91
Result[2]... 0BEEFBB3:12942ccf
read:14864189
#\<clock hands\>:\<initial seed\>
#Initial seed of Result[0] or Result[n] that has same clock hands is result.
#In this case, Result[0]...b98ab4f3 or Result[-1]...24b9a52e is result.

#Output list of clock hands(First 15) from an initial seed
$ ./tickList b98ab4f3
0BEEFBAG773E77A
$ ./tickList 24b9a52e
0BEEFBAG168GA41
#If you check clock hands 2 more and get 77, the initial seed is b98ab4f3

#Output a list of IVs of pokemon generated from an initial seed.
$ ./list b98ab4f3
#/lists/indivList.csv and /lists/list.csv are generated.
#See indivList.csv for IVs of pokemons generated from the initial seed.
'''
