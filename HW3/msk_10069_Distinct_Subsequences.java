//CMPT 409 Assignment 3
//Problem: Distinct Subsequences
//Team Members: Heather Li, Ekjot Singh Billing, Manshant Singh Kohli

import java.util.*;
import java.math.*;

class Main{
	public static void main(String[] args) {
		Scanner in=new Scanner(System.in);
		int n=Integer.parseInt(in.nextLine());
		while(n-->0){
			String s=in.nextLine();
			String z=in.nextLine();
			char cc=z.charAt(0);
			int aa=0;
			while(aa<s.length() && s.charAt(aa)!=cc) aa++;
			if(aa>=s.length()){
				System.out.println(0);
				continue;
			}
			s=s.substring(aa);
			HashMap<Character, ArrayList<Integer>> m = new HashMap<Character, ArrayList<Integer>>();
			for(int i=0;i<z.length();i++){
				ArrayList<Integer> list = m.get(z.charAt(i));
				if(list==null){
					list=new ArrayList<Integer>();
					m.put(z.charAt(i), list);
				}
				list.add(i);
			}

			BigInteger[] total = new BigInteger[z.length()];
			for(int i=0;i<total.length; i++){
				total[i]=BigInteger.ZERO;
			}

			total[0]=total[0].add(BigInteger.ONE);
			for(int i=1;i<s.length();i++){
				ArrayList<Integer> list = m.get(s.charAt(i));
				if(list==null) continue;
				for(int j=list.size()-1;j>=0;j--){
					int val=list.get(j);
					if(val==0) total[0]=total[0].add(BigInteger.ONE);
					else total[val]=total[val].add(total[val-1]);
				}
			}

			System.out.println(total[total.length-1]);
		}
	}
}
