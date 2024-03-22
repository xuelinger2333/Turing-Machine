; This example program checks if the input string is a binary palindrome.
; Input: a string of 0's and 1's, e.g. '1001001'

; the finite set of states
#Q = {reset,check,true,false,checkc,illegal,ill1,ill2,ill3,ill4,ill5,ill6,t1,t2,t3,t4,t5}

; the finite set of input symbols
#S = {a,b,c}

; the complete set of tape symbols
#G = {a,b,c,_,t,r,u,e,f,l,s,e,p}

; the start state
#q0 = check

; the blank symbol
#B = _

; the set of final states
#F = {true}

; the number of tapes
#N = 2

; the transition functions
check a_ aa rr check
check b_ bb rr check
check c_ ** rl reset
check __ ** l* illegal

reset *a ** *l reset
reset *b ** *l reset
reset *_ ** *r checkc

checkc c* ** ** illegal
checkc aa ** rr checkc
checkc bb ** rr checkc
checkc ab ** ** illegal
checkc ba ** ** illegal
checkc _a ** l* illegal
checkc _b ** l* illegal
checkc a_ ** ** illegal
checkc b_ ** ** illegal
checkc __ ** l* true

illegal a* ** l* illegal
illegal b* ** l* illegal
illegal c* ** l* illegal
illegal _* ** r* ill1
ill1 ** f* r* ill2
ill2 ** a* r* ill3
ill3 ** l* r* ill4
ill4 ** s* r* ill5
ill5 ** e* r* ill6
ill6 a* __ r* ill6
ill6 b* __ r* ill6
ill6 c* __ r* ill6
ill6 _* __ ** false

true a* _* l* true
true b* _* l* true
true c* _* l* true
true _* _* r* t1
t1 ** t* r* t2
t2 ** r* r* t3
t3 ** u* r* t4
t4 ** e* r* t5



