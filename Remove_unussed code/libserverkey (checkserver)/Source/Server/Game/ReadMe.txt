First time thank you @CiocoBoco ( https://metin2.dev/profile/1274-ciocoboco/ ) the ymir licens remove.

Delete check_server.cpp + check_server.h in game folder.

Open makefile and delete:

 -L../../libserverkey

search and delete:

 -lserverkey

search and delete:

check_server.cpp

You need recompilne source (and depend / gmake dep)