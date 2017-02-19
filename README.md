SM-Tapu-RNGTool
====
Creates and searchs the DB for specifying initial seed from first 8 clock hands.   
Outputs a list of IVs of pokemon generated from an initial seed.  

This tool is usable in RNG for Tapu {Koko/Lele/Bulu/Fini}.  
(Using SFMT)  
It's not usable in Egg Hatching RNG.  

## Requirement  (Other environments aren't tested)
Ubuntu 15.04  
gcc (Ubuntu 4.9.2-10ubuntu13) 4.9.2  

## Usage
```
#Build
$ make

#Create DB
$./db-create
0.01 %
0.02 %
0.03 %
.
.
.

#Sort DB
#Execute once. Executing twice or more breaks db files.  
$./db-sort
0.00 %
0.00 %
3.46 %
3.46 %
3.81 %
4.15 %
.
.
.

#Search the DB
#Input first 8 clock hands according to heptadecimal format (below).
#0->0, 1->1, ... 10->A, 11->B, ... 15->F, 16->G
$ ./db-search 0BEEFBAG
./db/0B.bin
readSize:14864189
read:0.038292[s]
search:0.000072[s]

0BEEFBAG16:24b9a52e
0BEEFBAG77:b98ab4f3
#<clock hands>:<initial seed>
#It shows 10 clockhands in result.
#In this case, if you check clock hands 2 more and get 77, the initial seed is b98ab4f3

#Output a list of IVs of pokemon generated from an initial seed
$ ./list b98ab4f3
#/lists/indivList.csv and /lists/list.csv are generated.
#See indivList.csv for IVs of pokemons generated from the initial seed.
#Synchro is not implemented now.
```

## Reference
How to look on clock hands as 0-16 expression.  
http://www.smogon.com/forums/threads/sfmt-rng-in-sun-moon.3591281/#post-7167880  
Checking the some clock hands in save selecting (when select "Continue") is enough to specify the initial seed.  
http://blastoise-x.hatenablog.com/entry/SM-RNG-abuse  
The Scheme for deciding pokemon status  
http://xxsakixx.com/archives/55579090.html  

Searching for the initial Seed from clock hands by API  
https://odanpoyo.github.io/2017/01/26/rng-api/  
by local DB   
https://odanpoyo.github.io/2017/01/25/SFMT-DB/  

Practical SM RNG Tool (for Egg, Tapu, Silvally, and more)  
https://github.com/Quandra/PokemonSunMoonRNGTool/tree/v2.00alpha  

#Other
- "tick" in source code or filename means "clock hand."  
