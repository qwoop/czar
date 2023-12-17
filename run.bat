@echo off
gcc -o czar src/czar.c src/lexer/lexer.c src/file_handler/file_handler.c src/czar-state-machine/czar-state-machine.c src/dstructs/hashmap/hashmap.c src/dstructs/fsm/fsmachine.c src/dstructs/fsm/fselements.c src/dstructs/fsm/fsutils.c src/memory_manager/memory_manager.c src/charset/charset.c
czar.exe %1 %2