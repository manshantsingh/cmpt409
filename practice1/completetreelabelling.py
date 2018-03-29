#CMPT 409
#Problem: Complete Tree Labelling
#Team Members: Heather Li, Ekjot Singh Billing, Manshant Singh Kohli
#Python3

from sys import stdin

#returns n!/(start-1)!
def factorial(n,start=1):
    ret=1
    for i in range(int(start),int(n+1)):
        ret*=i
    return ret

#returns n choose r
def ncr(n,r):
    return factorial(n,n-r+1)//factorial(r)

#returns the number of ways to divide n distinct objects into r-sized groups
def choosegroups(n,r):
    ret=1
    while (n!=r):
      ret*=ncr(n,r)
      n=n-r
    return ret

#solve
def rec(nodes,k,d):
    ret=0
    if nodes<=(k+1) or d<=1: #base case
        return factorial(k)
    nextnodes=(nodes-1)/k
    ktuples=choosegroups(nodes-1,nextnodes)
    ret+=ktuples*(rec(nextnodes,k,d-1)**k) #descend a level
    return ret

for line in stdin:
    k=int(line.split(' ')[0])
    d=int(line.split(' ')[1])
    #number of nodes in a complete k-ary tree of depth d
    if k!=1:
        nodes=(k**(d+1)-1)/(k-1)
    else:
        nodes=d+1
    print (rec(nodes,k,d))
