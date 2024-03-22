; This example program checks if the input string is a binary palindrome.
; Input: a string of 0's and 1's, e.g. '1001001'

; the finite set of states
#Q = {cp,cmp,check,checka,checkb,write,writec,writecc,illegal,ill1,ill2,ill3,ill4,ill5,ill6,ill7,ill8,ill9,ill10,ill11,ill12,ill13,ill14,ill15}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {a,b,_,s,p,c,I,l,e,g,n,p,u,t}

; the start state
#q0 = check

; the blank symbol
#B = _

; the set of final states
#F = {write}

; the number of tapes
#N = 3

; the transition functions
check a__ **p r*r checka
check b_* _*p *** illegal
check __* **s *** illegal

checka a__ *** r*r checka
checka b__ **s r*l checkb
checka __* *** l** illegal

checkb b** *** r** checkb
checkb a_* **s *** illegal
checkb __* *** l** write

illegal a** _** l** illegal
illegal b** _** l** illegal
illegal _** *** r** ill1 
ill1 *** I** r** ill2
ill2 *** l** r** ill3
ill3 *** l** r** ill4
ill4 *** e** r** ill5
ill5 *** g** r** ill6
ill6 *** a** r** ill7
ill7 *** l** r** ill8
ill8 *** _** r** ill9
ill9 *** I** r** ill10
ill10 *** n** r** ill11
ill11 *** p** r** ill12
ill12 *** u** r** ill13
ill13 *** t** r** ill14
ill14 a** _** r** ill14
ill14 b** _** r** ill14
ill14 _** *** l** ill15

write b*_ *** **l write
write a** *** *l* cp
write **p *** *** writec

writec b_p *c* lrr writecc

writecc **_ *c* *rr writecc
writecc **s *** **l write 

cp a** _** l** cp
cp b** _** l** cp
cp _c* _** *l* cp
cp __* *** rr* cmp

cmp *c* c** rr* cmp
cmp a_* __* r** cmp
cmp b_* __* r** cmp



