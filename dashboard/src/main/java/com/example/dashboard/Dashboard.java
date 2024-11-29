package com.example.dashboard;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.util.Random;

public class Dashboard extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{

        CommChannel channel = new SerialCommChannel("COM3",9600);
        // CommChannel channel = new SerialCommChannel("/dev/cu.usbmodem1411",9600);

        /* Waiting Arduino rebooting */
        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        System.out.println("Ready.");

        double sceneWidth = 400;
        double sceneHeight = 260;
        double buttonWidth = 170;
        double buttonHeight = 120;
        double textFieldWidth = 170;
        double textWidthHeight = 40;
        String textFieldStyle = "-fx-background-color: #A8DADC; -fx-border-color: transparent;";
        String labelStyle = "-fx-font-size: 16px; -fx-font-weight: bold;";

        Button emptyButton = new Button("EMPTY");
        Button restoreButton = new Button("RESTORE");

        emptyButton.setStyle("-fx-background-color: #247BA0; -fx-text-fill: white; -fx-font-size: 14px; -fx-font-weight: bold; -fx-background-radius: 5;");
        restoreButton.setStyle("-fx-background-color: #FF1654; -fx-text-fill: white; -fx-font-size: 14px; -fx-font-weight: bold; -fx-background-radius: 5;");

        emptyButton.setPrefSize(buttonWidth, buttonHeight);
        restoreButton.setPrefSize(buttonWidth, buttonHeight);

        TextField percentTextField = new TextField();
        percentTextField.setPrefSize(textFieldWidth, textWidthHeight);
        percentTextField.setStyle(textFieldStyle);
        percentTextField.setEditable(false);
        percentTextField.setText("0%");
        percentTextField.setAlignment(Pos.CENTER);

        TextField tempTextField = new TextField();
        tempTextField.setPrefSize(textFieldWidth, textWidthHeight);
        tempTextField.setStyle(textFieldStyle);
        tempTextField.setEditable(false);
        tempTextField.setText("0°C");
        tempTextField.setAlignment(Pos.CENTER);

        Label tempLabel = new Label("Level of waste");
        tempLabel.setStyle(labelStyle);

        Label percentLabel = new Label("Temperature");
        percentLabel.setStyle(labelStyle);

        VBox tempVBox = new VBox(5);
        tempVBox.setAlignment(Pos.CENTER_LEFT);
        tempVBox.getChildren().addAll(tempLabel, percentTextField);
        VBox.setMargin(tempTextField, new javafx.geometry.Insets(0, 0, 20, 0));
        tempVBox.getChildren().add(emptyButton);

        VBox percentVBox = new VBox(5);
        percentVBox.setAlignment(Pos.CENTER_LEFT);
        percentVBox.getChildren().addAll(percentLabel, tempTextField);
        VBox.setMargin(percentTextField, new javafx.geometry.Insets(0, 0, 20, 0));
        percentVBox.getChildren().add(restoreButton);

        HBox buttonBox = new HBox(20);
        buttonBox.getChildren().addAll(tempVBox, percentVBox);
        buttonBox.setAlignment(Pos.CENTER);

        VBox vBox = new VBox();
        vBox.getChildren().addAll(buttonBox);
        vBox.setAlignment(Pos.BOTTOM_CENTER);
        VBox.setMargin(buttonBox, new javafx.geometry.Insets(0, 0, 20, 0));

        Scene scene = new Scene(vBox, sceneWidth, sceneHeight);
        primaryStage.setTitle("Dashboard");
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);

        emptyButton.setOnAction(event -> channel.sendMsg("empty"));
        restoreButton.setOnAction(event -> channel.sendMsg("restore"));


        new Thread(() -> {
            while (true) {
                try {

                    String newPercent = percentTextField.getText();
                    String newTemp = tempTextField.getText();
                    String msg = channel.receiveMsg();

                    if (msg.endsWith("%")) {
                        newPercent = msg;
                    }
                    if (msg.startsWith("°C")) {
                        newTemp = msg;
                    }

                    final String percentage = newPercent;
                    final String temperature = newTemp;

                    Platform.runLater(() -> {
                        percentTextField.setText(percentage);
                        tempTextField.setText(temperature);
                    });

                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();


        primaryStage.show();
        vBox.requestFocus();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
