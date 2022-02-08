package com.example.weaselprogram;


import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.input.MouseEvent;

import java.util.ArrayList;
import java.util.Random;


public class HelloController {

    @FXML
    private Label rnd;

    @FXML
    private void onStartAll(MouseEvent event){
        // TODO Auto-generated method stub
        // Gerar string aleat�ria 28 char
        System.out.println("RUNNING");

        String charRadom = "ABCDEFGHIJKLMNOPQRSTUVWXZ ";
        char[] charRandom = new char[charRadom.length()];
        charRandom = charRadom.toCharArray();
        String inital = new keyGen().value;
        char[] charKey = new char[28];
        charKey = inital.toCharArray();
        Random rand = new Random();
        int initalPoints = new checkKey(charKey).ponts;
        boolean finish = false;
        ObservableList<String> obsGen;
        ObservableList<String> obspoint;
        ObservableList<String> obsKey;




        if(initalPoints == 28) finish = true;
        int gen = 1;

        rnd.setText(inital);

        while(!finish) {

            for(int i =0; i<100; i++) {
                char[] copy = charKey;

                for (int j = 0; j < 28; j++) {

                    int prop = rand.nextInt(100);
                    if(prop < 5) {

                        if(copy[j] != new checkKey(copy).alvoChar[j]) {

                            copy[j] = charRandom[rand.nextInt(charRadom.length())];
                        }

                    }
                }

                if(new checkKey(copy).ponts > initalPoints) {
                    charKey = copy;
                    initalPoints = new checkKey(charKey).ponts;
                }
            }

            initalPoints = new checkKey(charKey).ponts;
            genList.add(Integer.toString(gen));
            resList.add(new String(charKey));
            pointList.add(Integer.toString(initalPoints));

            gen++;
            if(initalPoints == 28) {
                finish = true;
            }
        }

        obsGen = FXCollections.observableArrayList(genList);
        obsKey = FXCollections.observableArrayList(resList);
        obspoint = FXCollections.observableArrayList(pointList);


        listGen.setItems(obsGen);
        listStrings.setItems(obsKey);
        listPoints.setItems(obspoint);

        genList.removeAll(obsGen);
        resList.removeAll(obsKey);
        pointList.removeAll(obspoint);


    }

    @FXML
    private ListView<String> listGen;
    private ArrayList<String> genList = new ArrayList<String>();

    @FXML
    private ListView<String> listPoints;
    private ArrayList<String> pointList = new ArrayList<String>();


    @FXML
    private ListView<String> listStrings;
    private ArrayList<String> resList = new ArrayList<String>();



}