package com.example.weaselprogram;

public class checkKey {

	String alvo = "METHINKS IT IS LIKE A WEASEL";	
	char[] alvoChar = new char[28];
	int ponts;
	public checkKey(char[] check) {
		ponts  = 0;
		alvoChar = alvo.toCharArray();
		for(int i = 0; i<28;i++) {

			if(alvoChar[i] == check[i]) {
				ponts++;
				
			}
		}
	}
	
}
