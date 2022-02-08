package com.example.weaselprogram;

import java.util.Random;

public class keyGen {
	String value;
	String charRadom = "ABCDEFGHIJKLMNOPQRSTUVWXZ ";
	String aleatoria = "";	

	
	public keyGen() {
		
		Random rand = new Random();
		for (int i = 0; i<28; i++) {
			int randomPos = rand.nextInt(charRadom.length());
			aleatoria += charRadom.charAt(randomPos);
		}
		this.value = aleatoria;
	}
	

}
